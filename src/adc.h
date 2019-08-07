/*! \file   adc.h
 * Author: Alexander Lenz
 *
 * Created on 10 September 2012, 10:53
 */

#ifndef ADC_H
#define	ADC_H


//12bit ADC, mid-value is defined as 0, TODO: build calibration system,
#define ADCZEROOFFSET 512 //mathematically 512 is the middle (10 bit ADC)


//length of array to average the zero offset current for phase A and B, also adjust division below
#define OFFSET_SAMPLE_SIZE 256
#define OFFSET_ROUNDING OFFSET_SAMPLE_SIZE/2 
#define OFFSET_DIVISION_SHIFT 8 //because 2^8=256


//define all values below 16 as noise
#define NOISE_FLOOR 0x00F

extern int IphaseAOffset;
extern int IphaseBOffset;

/*! \brief configures the 12bit analog-to-digital converter (ADC1).
 * 
 */
void setupADC1(void);
void startADC1(void);
void calculateOffset(int phaseACurrent, int phaseBCurrent);



#endif	/* ADC_H */

