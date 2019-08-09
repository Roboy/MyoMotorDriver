/*! \file spiFunctions.h
    \brief SPI configuration and communication

*/



#ifndef SPIFUNCTIONS_H
#define	SPIFUNCTIONS_H
#include <p33FJ128MC802.h>
#include "can.h"

#define NUMBER_OF_CONTROL_INPUT_WORDS 3
#define START_OF_FRAME_MASK 0x8000
#define START_OF_CONTROL_MESSAGE 0x8000
#define START_OF_DIAGNOSIC_MESSAGE 0x8001


/*! \brief configures the SPI hardware and resets spi protocol
 */
void SPI1Setup(void);

/*! \brief extracts the control flags from the SPI data stream
 * extracts control flags from SPI data
 * \return  1 if data is valid, otherwise data is not valid
 * \param * controlFlags will be filled with control flags from SPI data
 */
int getSPIControlFlags(unsigned int * controlFlags);


/*! /brief resets SPI module after watchdog event
 *
 */
void resetSPI();


/*! /brief enables SPI interrupt
 *
 */
void enableSPIInterrupt();
#endif	/* SPIFUNCTIONS_H */


