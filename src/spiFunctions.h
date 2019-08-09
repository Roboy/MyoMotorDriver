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



typedef enum enum_PROTOCOLSTATE {
    reset = 0,
    startOfControlFrame,
    startOfDiagnosticFrame,
    startOfControlTxData,
    startOfDiagnosticTxData,
    endOfFrame,


} PROTOCOLSTATE;


/*! \brief SPI control stream
 *
 *
 *  This structure is data that is exchanged between the MyoGanglion and the DCMotorDriver during the control
 *  phase.
 */
typedef struct struct_SPICOMMUNICATIONSTREAM_CONTROL {

    union {

        struct {
            unsigned startOfFrame : 16; //input
            int   pwmRef : 16; //in
            unsigned controlFlags1 : 16; //in
            long actualPosition : 32; //out
            int actualVelocity : 16; //out
            int actualCurrent : 16; //out
            long springDisplacement : 32; //out
            int sensor1 : 16; //out
        };


        unsigned int dataStream[10];



    }; //end union

} SPICOMMUNICATIONSTREAM_CONTROL;


/*! \brief configures the SPI hardware and resets spi protocol
 */
void SPI1Setup(void);


 /*! \brief extracts reference value from SPI data
 * \return  1 if data is valid, otherwise data is not valid
 * \param parameter 1: * referenceValue will be filled with PWM duty cycle reference
 */
int getSPIReference(int * referenceValue);


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


