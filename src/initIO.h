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
 * Using 28 pin out, see initio.c for pin-out and connectivity
 */


void initIO(void);

#define LED1 _LATA4
#define MOTOR_BRAKE _LATA3
#define MOTOR_DIRECTION _LATB14
#define CLOCKWISE 0
#define ANTICLOCKWISE 1
#define OPEN 1
#define LOCKED 0
#endif	/* INITIO_H */

