/* 
 * File:   qei.h
 * Author: Alexander Lenz
 *
 * Created on 06 September 2012, 10:18
 */

#ifndef QEI_H
#define	QEI_H
#include <p33FJ128MC802.h>

extern long encoderPos_0;
extern long encoderPos_1;

void initQEI1( unsigned int  startPos);
void initQEI2( unsigned int  startPos);
float getPositionInRad();
float getVelocityInRadPerSecond();

#endif	/* QEI_H */

