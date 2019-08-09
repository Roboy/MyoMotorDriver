/*! \file main.c
 *
 * Project Name: motorDriver.X
 * Author:        Alexander Lenz
 * Last Modified: 07/07/2014
 * Revision:      3.0, hardware version 3 with USB/Serial port
 * Description:   main.c file initialises the controller
 *
 * Interrupt priorities of the peripherals:
 * SPI:     6
 * QEC:     5
 * Timer1:  4
 * CANRx:   3
---------------------------------------------------------------------***/

//#include "main_head.h"
#include "p33FJ128MC802.h"
#include "initIO.h"
#include "timers.h"
#include "pwm.h"
#include "motorControl.h"
#include "spiFunctions.h"
#include "qei.h"
#include "can.h"
#include "dma.h"
#include "adc.h"
#include "DEEEmulation.h"
#include "serialPortFunctions.h"

#define DEBUG

#ifndef DEBUG
    /*** special registers setup using macros located in p33FJ128GP802.h ***/
    // bootloader settings
     int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0x3 ;
     int FOSC __attribute__((space(prog), address(0xF80008))) = 0xC0 ;
    _FWDT(FWDTEN_OFF); // Turn off Watchdog Timer
    _FGS(GSS_OFF); // Set General code protect off
    _FPOR(PWMPIN_OFF & HPOL_OFF & LPOL_OFF & FPWRT_PWR128);  //PWMPIN_OFF means that PWM pins are controlled by PWM unit at reset
     int FICD __attribute__((space(prog), address(0xF8000E))) = 0xFFDD ;
#else

    _FOSCSEL(FNOSC_FRC);	
    _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_XT);	// Clock Switching is enabled and Fail Safe Clock Monitor is disabled
                                                        // OSC2 Pin Function: OSC2 is Clock Output
                                                        // Primary Oscillator Mode: XT Crystal
    _FWDT(FWDTEN_OFF); 			            			// Watchdog Timer Enabled/disabled by user software
    _FPOR(PWMPIN_OFF & HPOL_OFF & LPOL_OFF & FPWRT_PWR128);
#endif
 
int main(void) {

    /*** oscillator setup --------------------------------------------------
    Here we are using PPL for 8MHz to generate 80MHz clock.
    FCY = 0.5 * (8MHz*40/2*2) = 40 MIPS
    ---------------------------------------------------------------------***/
    PLLFBD = 38; //set PPL to M=40
    CLKDIVbits.PLLPRE = 0; //N1 = input/2
    CLKDIVbits.PLLPOST = 0; //N2 = output/2
    
    // Disable Watch Dog Timer
	RCONbits.SWDTEN=0;

// Clock switching to incorporate PLL
	__builtin_write_OSCCONH(0x03);		// Initiate Clock Switch to Primary
													// Oscillator with PLL (NOSC=0b011)
	__builtin_write_OSCCONL(0x01);		// Start clock switching
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur	
    while (OSCCONbits.LOCK != 1); //Wait for PPL to lock
    
    DataEEInit();
    dataEEFlags.val=0;
    initIO();
    initPWM(1999); //20kHz PWM signal (Tper=50us based on 25ps Tcycle (=40MIPS)
    releaseMotor();
    resetMotorController();
    setupUART2();

    getConfigDataFromEEProm();
    prepareMotorCurrentConversion(); //takes EEPROM data and exctracts conversion factors
    
    //default time base for external SPI driven timer interrupts
    //the SPI setup functions does not enable interrupt, this happens in the
    //motor control state machine
    SPI1Setup();//we only need to set up the spi system if we use external control
    enableSPIInterrupt();
    initTimer1(63); //0.1008ms timer interrupt, based on a 1.6 us base = 40MIPS with 64 prescaler

    initQEI1(0x0000); //motor position
    initQEI2(0x0000); //joint displacement sensor

    setupADC1();
    initDmaChannel4(); //ADC DMA
    startADC1();

    resetMotorController();
    startTimer1();
    
    LED1=0;

    while (1){
        
    } // end while(1)
} // end main
