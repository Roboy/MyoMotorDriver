/* ! \file:   can.c
 * Author: Alexander Lenz
 *
 * Created on 21 September 2012, 09:32
 *
 * Initialises CAN 1 module and provides high-level functions for the reception and the transmission of message
 * 
 */


#include <p33FJ128MC802.h>
#include "can.h"
#include <string.h>
#include "dma.h"
#include "motorControl.h"
#include "initIO.h"
//****************************************************************INITIALISE CAN************************

void waitForCanMessageTransmitted()
{
    C1INTF;
    //U2TXREG= (C1INTF>>8)&0x00FF; //_RERRCNT;//_TERRCNT; //transmitt the error count on the UART
    while ((C1TR01CONbits.TXREQ1)&&(C1INTFbits.TXBP==0)&&(C1INTFbits.TXBO==0)&&(C1INTFbits.RXBP==0))
    {
        //U2TXREG= (C1INTF>>8)&0x00FF; //_TERRCNT; //transmitt the error count on the UART
    }
}

void initCAN(void)
{

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Set CAN module into configuration mode
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  C1CTRL = 0x0C00; //0000 1100 0000 0000
    C1CTRL1bits.REQOP = 0b100; // Set Configuration mode
    while (C1CTRL1bits.OPMODE != 0b100)
    {
    }; // wait for module to switch to config mode
    C1CTRL1bits.CSIDL = 1; // Discontinue CAN operation in Idle mode
    C1CTRL1bits.ABAT = 1; // signal all transmit buffers to abort transmission
    C1CTRL1bits.CANCAP = 0; // disable CAN capture
    C1CTRL1bits.CANCKS = 1; // Fcan clock is set to Fcy (i.e. 40MHz)
    C1CTRL2 = 0; // used by device $net^{TM}$ not here

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Setup Tq for CAN module
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  C1CFG1 = 0x0003;  //0000 0000 0000 0011
    C1CFG1bits.SJW = 0b00; // synchronised jump width time is 1 x Tq
    C1CFG1bits.BRP = 0b000001; // Baud rate prescaler Tq set to 2*2*(1/Fcan) (i.e. 100ns)
                               //which achieves 1Mbit/s with the settings below

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Setup bit Timing for CAN module  (Bit time = 1 + 5 + 3 + 1 Tq) hence set Baud rate = 1Mbit/s
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  C1CFG2 = 0x42D0;  					// 0100 0010 1110 0000
    C1CFG2bits.WAKFIL = 1; // Use CAN bus line filter for wake-up
    C1CFG2bits.SEG2PHTS = 1; // Phase segment 2 time select is freely programmable
    C1CFG2bits.PRSEG = 0b000; // Propagation time segment 0 = 1 x Tq
    C1CFG2bits.SEG1PH = 0b100; // Phase buffer segment 4 = 5 x Tq
    C1CFG2bits.SEG2PH = 0b010; // Phase Buffer segment 2 = 3 x Tq
    C1CFG2bits.SAM = 1; // Bus is sampled 3 times at sample point


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Setup FIFO control register
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // C1FCTRL = 0x0;
    C1FCTRLbits.FSA = 0b00000; // FIFO area starts with buffer TRB0
    C1FCTRLbits.DMABS = 0b010; // DMA buffer Size of 8

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Setup message acceptance filter mask registers
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    C1CTRL1bits.WIN = 1; // Use filter window
    C1FEN1 = 0x0002; // enable Filter 1 to accept messages

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Setup message acceptance filter 1
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    C1RXF1SIDbits.SID = 0x001; // messages must match these bits, but mask needs to be considered (below)!!
    C1RXF1SIDbits.EXIDE = 0; // accept only standard SID message identifiers

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Setup message acceptance mask 1
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    C1RXM1SIDbits.SID = 0x000; //'0' Don't care, accept all messages
    C1FMSKSEL1bits.F1MSK = 0b01; // Apply acceptance mask 1 to filter 1
    C1RXM1SIDbits.MIDE = 0; // Match messaegs (std or ext) if filters match

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Select Rx buffer
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    C1BUFPNT1 = 1; // Filter 0 hits received in RX buffer 1 (shouldn't this be 0x10 i.e.filter 1 or F1BP = 1??)
    C1CTRL1bits.WIN = 0; // Use buffer window		!! what is this

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Set interrupts
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // C1INTE = 0x0002;
    C1INTFbits.RBIF = 0; // clear Rx interrupt flag bit if set

    C1INTEbits.RBIE = 0; // Rx buffer interrupt disabled

    IFS2bits.C1RXIF = 0; // clear global Rx interrupt flag
    IFS4bits.C1TXIF = 0; // clear global Tx interrupt flag
    IFS2bits.C1IF = 0; // clear global overall interrupt flag
    IEC2bits.C1RXIE = 0; // disable CAN Rx interrupts
    IEC2bits.C1IE = 0; // disable CAN interrupts (all?)
    //IPC8bits.C1RXIP			= 7;				// set priority of CAN rx interrupt
    //IPC8bits.C1IP				= 6;				// set overall CAN interrupt priority ??

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Set CAN module into normal operation mode
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    C1CTRL1bits.REQOP = 0b000; // Set normal mode

    while (C1CTRL1bits.OPMODE != 0b000)
    {
    }; // wait for module to switch to normal mode

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Set receive buffers
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  C1RX0CON = 0x0004;
    C1RXFUL1 = 0; // clear all rx buffer full flags
    C1RXOVF1 = 0; // clear all rx buffer overflow flags
    C1TR01CONbits.TXEN0 = 0; // ECAN1, buffer 0 is a receive buffer
    C1TR01CONbits.TXEN1 = 1; // ECAN1, buffer 1 is a transmit buffer
    C1TR01CONbits.TX0PRI = 0b11; // Message buffer 0 highest priority
    C1TR01CONbits.TX1PRI = 0b11; // Message buffer 1 highest priority
}

void __attribute__((__interrupt__, auto_psv)) _C1RxRdyInterrupt(void)
{
    IFS2bits.C1RXIF = 0; // clear global Rx interrupt flag
    IFS2bits.C1IF = 0; // clear global overall interrupt flag
    //LED1=~LED1;
   
}

/*
void __attribute__((__interrupt__, auto_psv)) _C1TxRdyInterrupt(void)
{
    IFS4bits.C1TXIF = 0; // clear global Tx interrupt flag
    IFS2bits.C1IF = 0; // clear global overall interrupt flag
    //LED1=~LED1;

}
 * */


/*
 * transmits additional internal states, independent of the control mode
 * the message ID is the configured transmit message id + 1
 */

void CANTransmitAdditionalInternalStates(int motorCurrent, int springDisplacement, int sensor1, int sensor2)
{
    unsigned dataArray[4];


    memcpy(dataArray+0, &motorCurrent,2); //copy bytes into transmit array
    memcpy(dataArray+1, &springDisplacement,2); //copy bytes into transmit array
    memcpy(dataArray+2, &sensor1,2); //copy bytes into transmit array
    memcpy(dataArray+3, &sensor2,2); //copy bytes into transmit array

    CANTransmit(eePromData.actualValueMessageId + 1, dataArray, 4);
}
/*! brief transmits the actual value of the PID control loop, value depends on control mode 
 *  (i.e. either position, velocity or current)
 */
void CANTransmitActualControlValue(float actualValue, long encoderPosition)
{
    unsigned dataArray[4];
    float currentValue;

    currentValue=actualValue;
    memcpy(dataArray,&currentValue,4); //copy bytes into transmit array
    memcpy(dataArray+2, &encoderPosition,4); //copy bytes into transmit array
    
    CANTransmit(eePromData.actualValueMessageId, dataArray, 4);
}

/*! brief transmits a string using CAN message, including the \0 character.
 */
void CANTransmitString(unsigned int u16SID, char * cString)
{
    unsigned dataArray[4];
    unsigned int wordCounter=0;
    unsigned int messageCounter=0;
    unsigned int low=1;
    unsigned int charHighByte;
          
        wordCounter=1; //because we use word 0 for the indedx
        do
        {
            if (low==1) //write low byte in bus order
            {
                dataArray[wordCounter]= (unsigned char) *cString;  //this is the low byte
                //dataArray[wordCounter]=dataArray[wordCounter]<<8; //makes this high
                cString++;
                low=0;
            }
            else  //write high byte in bus order
            {
                charHighByte=(unsigned char)*cString;
                charHighByte=charHighByte<<8;
                dataArray[wordCounter]=dataArray[wordCounter] | charHighByte;
                low=1;
                cString++;
                wordCounter++;
            }
             if ((low==1)&&(wordCounter>=4))
             {
                 dataArray[0]=messageCounter;
                 messageCounter=messageCounter+6; //
                //one message is full, transit it
                CANTransmit(u16SID, dataArray, 4);
                //wait until message has left
                waitForCanMessageTransmitted();
                wordCounter=1; //start with the first word again.
             }

             else if ( *(cString-1) == 0x00) //special case to treat non-complete can message
            {
               // we have reached the end of string, this is a special case and we have to send the message out
                 dataArray[0]=messageCounter;
                 messageCounter=messageCounter+6; //
                //one message is full, transit it
                CANTransmit(u16SID, dataArray, 4);
                waitForCanMessageTransmitted();
            }

  
        }while ( *(cString-1) != 0x00);



    

}

/*! brief transmits a CAN message, specifiying messageID, data and data length (in 16 bit words)
 */
void CANTransmit(unsigned int u16SID, unsigned int* pu16Data, unsigned int u16Datalen)
{
    unsigned int i;
    // Load message ID , Data into transmit buffer and set transmit request bit
    CanMessageBuffer[1][0] = ((u16SID & 0x7FF) << 2); //SID
    CanMessageBuffer[1][1] = 0; //EID
    CanMessageBuffer[1][2] = u16Datalen * 2; //DLC (convert to chars)

    for (i = 0; i < u16Datalen; i++)
    {
        CanMessageBuffer[1][3 + i] = pu16Data[i]; // load data into appropriate registers in DMA RAM space
    }

    C1TR01CONbits.TXREQ1 = 1;
    //set the transmit bit and leave, we don't wait for the transmission to complete!
}

/*! /brief returns message from CAN Rx buffer
 *
 * @param canData must be a pointer to a unsigned int array with a depth of 4 words
 * @param messageID is the message ID of the received message
 * @return the data length of the received message
 */
int CANReceive(unsigned int* canData, unsigned int * messageID)
{
    unsigned int i;
    // Wait till receive buffer contain valid message

    //TODO, make sure this is ok? 
    while(!C1RXFUL1bits.RXFUL0);

    * messageID = CanMessageBuffer[0][0] >> 2;			// return SID from message in DMA RAM

    for(i=0;i<4;i++)
    {
	canData[i] = CanMessageBuffer[0][3+i];		// return contents of DMA RAM space
    }

    // Clear the flag to indicate that receive buffer is open to receive a new message
   // C1RXFUL1bits.RXFUL0 		= 0;
	C1RXFUL1					= 0;				// clear all rx receive buffer flags
   	C1RXOVF1					= 0;				// clear all rx buffer overflow flags
	C1INTFbits.RBIF				= 0;				// clear Rx interrupt flag bit if set

    return (CanMessageBuffer[0][2] & 0x0F);			// return the DLC (number of bytes)
}
