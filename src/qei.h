/* 
 * File:   qei.h
 * Author: Alexander Lenz
 *
 * Created on 06 September 2012, 10:18
 */

#ifndef QEI_H
#define	QEI_H
#include <p33FJ128MC802.h>


void initQEI1( unsigned int  startPos);
void initQEI2( unsigned int  startPos);
float getPositionInRad();
float getVelocityInRadPerSecond();

extern long rotationCount;

#define GET_ENCODER(ENCODER_POSITION_VALUE) (ENCODER_POSITION_VALUE=rotationCount+POSCNT)

//todo: implement this second enccoder for spring displacement
#define GET_SPRING(SPRING_DISPLACEMENT) (SPRING_DISPLACEMENT = POS2CNT)

#endif	/* QEI_H */

