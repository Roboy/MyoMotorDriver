/* ! \file dma.h
 *
 * Author: Alexander Lenz
 *
 * Created on 21 September 2012, 13:30
 */

#ifndef DMA_H
#define	DMA_H

extern unsigned int CanMessageBuffer[32][8] __attribute__((space(dma)));
extern unsigned int adcData[32]__attribute__((space(dma)));
void initDmaChannel2(void);
void initDmaChannel3(void);
void initDmaChannel4(void);

void invalidateADCData();
void waitUnitlAdcDataIsReady();

#endif	/* DMA_H */

