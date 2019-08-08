/*
SPIFunctions.c
Project:
Device/Target: dsPIC30F4011
Author(s): A. LENZ
Functionality: this sets up all spi configuration bits and handles the SPI
 *             communication protocol
Change History:
                                2012-09-04	: Initial Release
 */
#include <p33FJ128MC802.h>
#include "initIO.h"
#include "spiFunctions.h"
#include "motorControl.h"
#include "qei.h"
#include "can.h"

SPICOMMUNICATIONSTREAM_CONTROL spiControlStreamInput;
SPICOMMUNICATIONSTREAM_CONTROL spiControlStreamOutput;



unsigned int spiControlMessageLength; //=sizeof(spiControlStreamInput)/2;
unsigned int spiMessageCounter; //counts datastream in words (16 bit)
unsigned int spiTxWordCounter;
unsigned int spiRxDataReady;
long oldEncoderValue;
PROTOCOLSTATE SPIControlProtocolState;

/*! \brief resets the SPI protocol but not the SPI hardware.
 *
 */
void resetSPIProtocol(void)
{
    spiMessageCounter = 0;
    spiTxWordCounter = 0;
    spiRxDataReady = 0;
    SPIControlProtocolState = reset;
    
    
}


/*! \brief resets SPI communcation hardware and protocol 
 */
void resetSPI()
{
    resetSPIProtocol();
    GET_ENCODER(oldEncoderValue); //store the current encoder value as the old encoder value;
    _SPI1IF = 0; //clear spi interrupts
    _SPIROV = 0; //clear the overflow bit, ignore it if it is set
}

/*! \brief configures SPI1 on dspPIC33F as a slave
 *
 *
 */
void SPI1Setup(void)
{



    _SPIEN = 0; //first switch off spi
    SPI1CON1bits.MSTEN = 0; //master mode disable, this is the SLAVE! So master is in charge of data rate
    SPI1CON2bits.FRMEN = 0; //disable frame support
    SPI1CON2bits.SPIFSD = 1; // frame synch pulse is an input (because we are slave) (N.A.)
    SPI1CON1bits.DISSDO = 0; //we do not disable SDO, we might use it to communicate data out
    SPI1CON1bits.MODE16 = 1; //we communicate with 16bit frames
    SPI1CON1bits.SMP = 0; //this bit is always cleared in slave mode, otherwise it determines the sample point
    SPI1CON1bits.CKE = 0; //is the clock edge select bit, determines that data changes on edge from idle to active
    SPI1CON1bits.CKP = 0; // idle is low, active is high
    SPI1CON1bits.SSEN = 1; //slave select pin is used (enabled)

    _FRMPOL = 0; //slave frame polarity, i.e. negative SS pulse
    _SPIFSD = 1;
    _FRMDLY = 0; //frame sync precedes first clock edge


    _SPI1IE = 0; //first, disable spi1 interrupt
    _SPI1IF = 0; //clear spi interrupts
    _SPI1IP = 6; //select spi1 interrupt priority
//    _SPI1IE = 1; //enable spi1 interrupt enable only when controller ready
    _SPIEN = 1; //SPI GO!

    spiControlMessageLength = sizeof (spiControlStreamInput) / 2;
    resetSPIProtocol(); //does what it says

}

void enableSPIInterrupt()
{
        _SPI1IF = 0; //clear spi interrupts
        _SPI1IE = 1; //enable spi1 interrupt
}

void __attribute__((__interrupt__, auto_psv)) _SPI1Interrupt(void)
{

    unsigned int spiInput;
    long tempPosition;
    int tempSpring;
    int dutyCycle;
    //static long positionBuffer;
    //read the input buffer
    spiInput = SPI1BUF;
    _SPI1IF = 0; //clear spi interrupts
    _SPIROV = 0; //clear the overflow bit, ignore it if it is set
    LED1=1;

    //LED1 = ~LED1;

    //check if this is a start of frame, and if so reset the protocol
    //this allows the immediate restart of a stream, even during the
    //broadcast of a stream. It makes the communcation robust and avoids
    //situation where the protocol receiver waits for a word
    //This means we can always restart

    if ((spiInput & START_OF_FRAME_MASK) != 0)
    {
        resetSPIProtocol();
        SPIControlProtocolState = reset;
        //get the motor current now already
        //this operation takes quite long so we peform
        //it separately from the other data gathering to spread
        //out the computational load between spi frames
        spiControlStreamOutput.actualCurrent=getFilteredMotorCurrentLong();//getFilteredMotorCurrent();
        LED1=1;
    }

    switch (SPIControlProtocolState)
    {
        case reset:
            if (spiInput == START_OF_CONTROL_MESSAGE)
            {
                //prepare Tx Data for sending
                //collect Rx Data
                //LED1=~LED1;
                spiControlStreamInput.dataStream[spiMessageCounter] = spiInput;
                //CANTransmitAdditionalInternalStates(spiInput,spiMessageCounter,spiControlStreamInput.dataStream[0],spiControlStreamInput.startOfFrame);

                spiMessageCounter++;
                SPIControlProtocolState = startOfControlFrame;
            }
            break;
        case startOfControlFrame:
            //copy received data
            spiControlStreamInput.dataStream[spiMessageCounter] = spiInput;
            spiMessageCounter++;

            //change to TxMode when all Rx Data has been received
            if (spiMessageCounter == (NUMBER_OF_CONTROL_INPUT_WORDS - 1)) 
            {
                
                SPIControlProtocolState = startOfControlTxData;

                //and provide output data
                //position
                GET_ENCODER(spiControlStreamOutput.actualPosition);

                spiControlStreamOutput.actualVelocity=spiControlStreamOutput.actualPosition-oldEncoderValue;
                //store old value
                oldEncoderValue=spiControlStreamOutput.actualPosition;

                GET_SPRING(spiControlStreamOutput.springDisplacement);
            }
            break;
        case startOfControlTxData:
            //copy received data
            spiControlStreamInput.dataStream[spiMessageCounter] = spiInput;
            spiMessageCounter++;

            //and provide output data
            SPI1BUF = spiControlStreamOutput.dataStream[spiMessageCounter];

            if (spiMessageCounter >= 9) //TODO, make message length dynamic(spiControlMessageLength-1))
            {
                SPIControlProtocolState = endOfFrame;
                RESET_WATCHDOG;
                //LED1 = ~LED1;

            }
            break;
        case endOfFrame:
            //LED1=~LED1;
            //signal that data is ready
            spiMessageCounter++;
            spiRxDataReady = 1;

            //drive the motor directly after SPI frame was
            if(spiControlStreamOutput.pwmRef>4000){
                spiControlStreamOutput.pwmRef = 4000;
            }
            if(spiControlStreamOutput.pwmRef<-4000){
                spiControlStreamOutput.pwmRef = -4000;
            }
//            setMotorDrive(spiControlStreamOutput.pwmRef);
            LED1=0;
           break;

    }
}

int getSPIReference(int * referenceValue)
{

    if (spiRxDataReady == 1)
    {
        if ((spiControlStreamInput.pwmRef & 0x4000) != 0)
        {
            //this means we have received a negative reference value
            //i.e. the MSB-1 is 1,
            //we set the MSB so the number looks like a normal, signed integer again
            spiControlStreamInput.pwmRef = (spiControlStreamInput.pwmRef | 0x8000);
        }

        *referenceValue = spiControlStreamInput.pwmRef;
        return 1;

    } 
    else
    {
        return 0;
    }

}

int getSPIControlFlags(unsigned int * controlFlags)
{
    return 0;

}