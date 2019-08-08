#include <p33FJ128MC802.h>
#include "initIO.h"

/*
      Motor control PWM module initialisation

 */
unsigned int pwmMaxDutyCycle;

void setPWMDutyCycle(unsigned int dutyCycle) {
    if (dutyCycle > pwmMaxDutyCycle) {
        PDC1 = pwmMaxDutyCycle;
    } else {
        PDC1 = dutyCycle;
    }

    P1SECMPbits.SEVTCMP=(PDC1>>2) +80 ; //sample ADC at 50% of the on time (counter counts only half to PDC)
                                          //therefore we devide by 4 (right shift 2)
                                 // and adjust for propagation delay in H-Bridge pre-drivers
                                 // a PDC value of 2000 corresponds to 50us. (40 ticks /us)
                                 // consequently, a propagation delay of 2 us is equivalent to 80
 }

void initPWM(int period) {
    pwmMaxDutyCycle = (period + 1) << 1; //store max DutyCycle in file global variable
    PTCONbits.PTEN = 1; // PWM timebase is off
    PTCONbits.PTSIDL = 1; // PWM timebase halts in CPU idle mode
    PTCONbits.PTOPS = 0x0000; // 1:1 post scale
    PTCONbits.PTCKPS = 0x00; // 1:1 clock pre-scale (i.e. Tcy per increment)
    PTCONbits.PTMOD = 0x00; // PWM time base operates in free-running mode
    PTPER = period; // load time period buffer with pwm time period
    PWM1CON1bits.PMOD3 = 1; // }
    PWM1CON1bits.PMOD2 = 1; // }	Independent operation
    PWM1CON1bits.PMOD1 = 1; // }
    PWM1CON1bits.PEN3H = 0;
    PWM1CON1bits.PEN2H = 0;
    PWM1CON1bits.PEN1H = 0;
    PWM1CON1bits.PEN3L = 0;
    PWM1CON1bits.PEN2L = 0;
    PWM1CON1bits.PEN1L = 1; //	enable PWM1Low output

    PWM2CON1bits.PEN1H = 0; //disable PWM outputs of PWM 2
    PWM2CON1bits.PEN1L = 0; //disable PWM outputs of PWM 2

    PWM1CON2bits.IUE = 0; // updates to active PDC registers are synched to pwm timebase
    PWM1CON2bits.OSYNC = 0; // output overide synced to next Tcy boundry
    PWM1CON2bits.UDIS = 0; // enable updates to duty cycle and pwm period registers

    PDC1 = 000; // set initial duty period to zero
    PTCONbits.PTEN = 1; // PWM timebase is on


    //special event to trigger ADC conversion in synchrony with PWM
    P1SECMPbits.SEVTDIR = 0;  //special event when counting upwards
    P1SECMPbits.SEVTCMP = period>>1; //trigger at 50%



    MOTOR_BRAKE = LOCKED; //either LOCKED or OPEN
    MOTOR_DIRECTION=CLOCKWISE; //either CLOCKWISE or ATNICLOCKWISE
    //LED1=1;
}

void __attribute__((__interrupt__, auto_psv)) _MPWM1Interrupt(void) {
    _PWM1IF = 0; // Reset interupt flag
}
