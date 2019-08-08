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


/*** special registers setup using macros located in p33FJ128GP802.h ***/
// bootloader settings
 int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0x3 ;
//_FOSCSEL(
//    FNOSC_PRIPLL &       // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
//    IESO_OFF             // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)
//);
 int FOSC __attribute__((space(prog), address(0xF80008))) = 0xC0 ;
//_FOSC(
//    POSCMD_EC &          // Primary Oscillator Source (EC Oscillator Mode)
//    OSCIOFNC_ON &        // OSC2 Pin Function (OSC2 pin has digital I/O function)
//    IOL1WAY_OFF &        // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
//    FCKSM_CSDCMD         // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)
//);
_FWDT(FWDTEN_OFF); // Turn off Watchdog Timer
_FGS(GSS_OFF); // Set General code protect off
_FPOR(PWMPIN_OFF & HPOL_OFF & LPOL_OFF & FPWRT_PWR128);  //PWMPIN_OFF means that PWM pins are controlled by PWM unit at reset
 int FICD __attribute__((space(prog), address(0xF8000E))) = 0xFFDD ;
//_FICD(
//    ICS_PGD3 &           // Comm Channel Select (Communicate on PGC3/EMUC3 and PGD3/EMUD3)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG is Disabled)
//);

/*
_FBS( RBS_NO_RAM & BSS_NO_FLASH & BWRP_WRPROTECT_OFF );
_FSS( RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF );
_FGS( GSS_OFF & GCP_OFF  & GWRP_OFF );
_FOSCSEL( FNOSC_PRIPLL & IESO_OFF );
//_FOSC( FCKSM_CSDCMD & OSCIOFNC_ON & POSCMD_EC );
_FOSC( FCKSM_CSDCMD & POSCMD_XT & IOL1WAY_OFF);
_FWDT( FWDTEN_OFF );
_FPOR(PWMPIN_OFF & HPOL_OFF & LPOL_OFF & FPWRT_PWR128);
 */
// DMA RAM space for ECAN messages (currently used only by bootloader)
//unsigned int message_buffer[2][8] __attribute__((space(dma)));
//unsigned int node_id;

//_FOSCSEL(FNOSC_FRC);	
//_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_XT);	// Clock Switching is enabled and Fail Safe Clock Monitor is disabled
//													// OSC2 Pin Function: OSC2 is Clock Output
//													// Primary Oscillator Mode: XT Crystal
//_FWDT(FWDTEN_OFF); 			            			// Watchdog Timer Enabled/disabled by user software
//_FPOR(PWMPIN_OFF & HPOL_OFF & LPOL_OFF & FPWRT_PWR128);

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
//        setMotorDrive(500);
    } // end while(1)
} // end main
