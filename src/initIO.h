/* 
 * File:   initIO.h
 * Author: Alexander Lenz
 *
 * Created on 112 September 2013, 14:41
 */

#ifndef INITIO_H
#define	INITIO_H
#include <p33FJ128MC802.h>
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
 **   8           RP4        RB4          IN                              SCK
 **   9           RA4        RA4          OUT                             LED1
 **  10           VDD
 **   1          PGD1       RB5          IN                              ProgrammingData
 **   2          PDG1       RB6          IN                              ProgrammingClock
 **  13           RP7        RB7          IN                              SS
 **  14           RP8        RB8          IN                              QEA
 **  15           RP9        RB9          IN                              QEB
 **   5           GND
 **  17           VDDCore
 **  18           RP10       RB10         IN                              DIS_QEB
 **   2           RP1        RB1          IN                              DIS_QEA (shared with PGC1)
 **  19           RP11       RB11         IN                              MOSI
 **  20           RP12       RB12         OUT                             MISO
 **  21           RP13       RB13         OUT                             BRAKE
 **  22           RP14       RB14         OUT                             DIRECTION
 **  23           PWM1L1     RB15         OUT                             ENABLE / PWM
 **  11           RP5        RB5          IN                              CAN_RX
 **  12           RP6        RB6          OUT                             CAN_TX
 **  24           GND(AVSS)
 **  25           AVDD

 */


void initIO(void);

#define LED1 _LATA4
#define MOTOR_BRAKE _LATB13
#define MOTOR_DIRECTION _LATB14
#define CLOCKWISE 0
#define ANTICLOCKWISE 1
#define OPEN 1
#define LOCKED 0
#endif	/* INITIO_H */

