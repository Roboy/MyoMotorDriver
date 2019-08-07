
#include <p33FJ128MC802.h>
#include "timers.h"
#include "initIO.h"
#include "pwm.h"
#include "motorControl.h"
#include "qei.h"
#include "can.h"
/*! \brief  genererates the main control loop
 */
void initTimer1(unsigned int period) {
    T1CON = 0; // ensure Timer 1 is in reset state
    T1CONbits.TGATE = 0; // gated time accumulation disabled
    T1CONbits.TCKPS = 0b10; // FCY divide by 64: tick = 1.6us
    T1CONbits.TCS = 0; // select internal FCY clock source
    TMR1 = 0;
    PR1 = period; // set Timer 1 period register ()
    IFS0bits.T1IF = 0; // reset Timer 1 interrupt flag
    IPC0bits.T1IP = 4; // set Timer1 interrupt priority level to 4
    IEC0bits.T1IE = 1; // enable Timer 1 interrupt
    T1CONbits.TON = 0; // leave timer disabled initially
}

void startTimer1(void) {
    T1CONbits.TON = 1; //
}


/*
void init_timer2(unsigned int period)
{
        T2CON 			= 0; 		// clear the T32 bit, reset timer
        T2CONbits.TGATE = 0; 		// gated time accumulation disabled
        T2CONbits.TCKPS = 0b10; 	// timer prescaler 1:64 tick = 1.6us
        T2CONbits.TCS 	= 0; 		// clock mode: internal clock (Fosc/2)
        T2CONbits.T32 	= 0; 		// use 16 bit clock
        TMR2 			= 0;
        PR2 			= period; 	// set timer period  (PR2 =2000 gives 20KHz)
        IFS0bits.T2IF 	= 0;    	// reset Timer 2 interrupt flag
        IPC1bits.T2IP 	= 5;    	// set Timer 2 interrupt priority level
        IEC0bits.T2IE 	= 1;    	// enable Timer 2 interrupt
        T2CONbits.TON 	= 0; 		// leave timer disabled initially
}
        timer 3 used for regulating odometry readings


void init_timer3(unsigned int period)
{
        T3CON 			= 0; 		//clear the T32 bit, reset timer
        T3CONbits.TGATE = 0; 		//gated time accumulation disabled
        T3CONbits.TCKPS = 0; 		//timer prescaler 1:64 tick = 1.6us
        T3CONbits.TCS 	= 0; 		//clock mode: internal clock (Fosc/2)
        TMR3 			= 0;
        PR3				= period;
        IFS0bits.T3IF   = 0;		// reset Timer 3 interrupt flag
        IPC2bits.T3IP	= 6;		// maximum priority
        IEC0bits.T3IE	= 1;		// enable Timer 3 interrupt
        T3CONbits.TON 	= 1; 		//enable timer
}
 */

//////////////////////////////////
// Generate internal 0.1ms period
//////////////////////////////////

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
    static int count = 0;
    _T1IF = 0; // reset Timer 1 interrupt flag
    unsigned int canTxData[4];
    //LED1=1;
    if (count < 499)
    {
        count++;
    } else
    {
        count = 0;
        canTxData[0]=0x8899;
        canTxData[1]=0xAABB;
        canTxData[2]=0xCCDD;
        canTxData[3]=0xEEFF;
        //CANTransmit(0x555, canTxData, 4);
    }
    //LED1=~LED1;
    {
       // LED1=~LED1; //toggle LED1
        motorControlLoop();
    }
    //LED1=0;
}



