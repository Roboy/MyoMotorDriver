/*
 * DEVICE LAYOUT
 * Using 28 pin 
 * Pin No   |    Name    | Port     | Direction     | Peripheral    |Comment
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 **  26           MCLR
 **  27           AN0                     IN                              Vsupply
 **  28           AN1                     IN                              Displacement sensor field strengh
 **   3           AN4                     IN                              IPhaseA
 **   4           AN5                     IN                              IPhaseB
 **  16           VSS                     IN
 **   6           OSC1                    IN
 **   7           RA3        RA3          OUT                             BRAKE
 **   8           RP4        RB4          IN                              SCK
 **   9           RA4        RA4          OUT                             LED1
 **  10           VDD
 **   1          PGD1       RB5          OUT                             ProgrammingData/UART tX
 **   2          PGC1       RB6          IN                              ProgrammingClock/UART rX
 **  13           RP7        RB7          IN                              SS
 **  14           RP8        RB8          IN                              QEA
 **  15           RP9        RB9          IN                              QEB
 **   5           GND
 **  17           VDDCore
 **  18           RP10       RB10         IN                              DIS_QEB
 **   2           RP1        RB1          IN                              DIS_QEA (shared with PGC1)
 **  20           RP12       RB12         OUT                             MISO
 *  *19           RP13       RB13         IN                              MOSI
 **  22           RP14       RB14         OUT                             DIRECTION
 **  23           PWM1L1     RB15         OUT                             ENABLE / PWM
 **  11           RP5        RB5          IN                              CAN_RX
 **  12           RP6        RB6          OUT                             CAN_TX
 **  24           GND(AVSS)
 **  25           AVDD

 */


#include <p33FJ128MC802.h>

void initIO() {
    int i;

    // set up analogue pins
    AD1CON1bits.ADON = 0; // disable ADC1 module
    AD1PCFGL = 0xffCf; //0b1111 1111 1100 1111; 		//  AN4 and AN5 are analog inputs

    // set digital port direction
    // inputs
    //all pins are inputs by default

    //outputs
    _TRISA3 = 0; // brake
    _TRISB14 = 0; // dir
    _TRISB15 = 0; // enable
    _TRISA4  = 0; // LED1
    _TRISB12 = 0; // SPI_miso
    _TRISB6  = 0; // CANTX
    _TRISB0 = 0; //UART TX

    //specifically define some inputs

    _TRISB8=1; //QEI1 A on RB8 is input
    _TRISB9=1; //QEI1 B on RB9 is input

    // set up remappable pins
    __builtin_write_OSCCONL(OSCCON & 0xbf); // clear bit 6
    // inputs
    RPINR14bits.QEA1R = 8; // QEI1 A to pin RB8
    RPINR14bits.QEB1R = 9; // QEI1 B to pin RB9
    RPINR16bits.QEB2R = 10; // QEB2 RB10 (changed)
    RPINR16bits.QEA2R = 11; //  QEA1 RB11
    RPINR26bits.C1RXR = 5; // ECAN1 received tied to RP05
    RPINR19bits.U2RXR = 1; // UART 2 RX is tied to RP1



    RPINR21bits.SS1R = 7; //    SlaveSelect to RP7
    RPINR20bits.SDI1R = 13; //   MOSI to RP13
    RPINR20bits.SCK1R = 4; //    SPI CLK to RP4
    // outputs

    RPOR3bits.RP6R = 0b10000; // RP06 tied to ECAN1 transmit
    RPOR6bits.RP12R = 0b00111; // pin RB12 to SPI1 miso    (configured as output but can be set as an input??)
    RPOR0bits.RP0R = 0b00101; // pin RP1/RB1 to UART2 TX
    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS registers


    for (i = 0; i < 30000; i++); // short delay


}

