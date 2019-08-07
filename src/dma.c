/* ! \file:  dma.c
 * Author: Alexander Lenz
 *
 * Created on 21 September 2012, 09:32
 */


#include <p33FJ128MC802.h>
#include "initIO.h"
#include "can.h"
#include "motorControl.h"

/*! \brief message buffer for DMA transfer of CAN Rx and Tx Messages
 *  This buffer has the maximum possible CAN buffer size (32)
 *  Each CAN message requires 8 16-bit words.
 *
 *  CanMessageBuffer[0][] is mapped to receive data that comes throug filter 2
 *  CanMessageBuffer[1][] is configured as Tx buffer
 *
 * Consequently, there are currently 30 message buffers that are not used
 */
unsigned int CanMessageBuffer[32][8] __attribute__((space(dma)));
/*! \brief message buffer for DMA transfer of ADC1 data
 *
 */
unsigned int adcData[32]__attribute__((space(dma)));


unsigned int adcDataReady;

/*! \brief initialises DMA channel 2 for CAN Rx message transfer
 *
 */
void initDmaChannel2(void)
{

	//DMA2CON		= 0x0020;	// 0000 0000 0010 0000
	DMACS0 = 0;                      				// clear all DMA controller status bits
	DMACS1 = 0;                						// clear all DMA controller status bits
	DMA0CONbits.CHEN = 0;            				// ensure that DMA channel 0 is disabled

	DMA2CONbits.CHEN	= 0;						// disable channel
	DMA2CONbits.SIZE	= 0;						// data transfer size set to word
	DMA2CONbits.DIR		= 0;						// Read from peripheral, write to RAM
	DMA2CONbits.HALF	= 0;						// Interrupt at end of block transfer
	DMA2CONbits.NULLW	= 0;						// Normal operation
//	DMA2CONbits.AMODE	= 0b10;						// Peripheral indirect addressing mode
	DMA2CONbits.AMODE	= 0b00;						// Register indirect addressing mode (as recommended by errata workaround pdf)//
	DMA2CONbits.MODE	= 0;						// Continuos, (ping-pong disabled)
	DMA2PAD				= (unsigned)&C1RXD;					// Address of ECAN Rx module (loaded into Peripheral Address register)
	DMA2CNT				= 0x7;						// Number of DMA transfers in a block (+1) i.e. 8
	DMA2REQ				= 34;						// Source of interrupt request to initiate transfer set to ECAN1 reception
	DMA2STA				= __builtin_dmaoffset(CanMessageBuffer);

	IFS1bits.DMA2IF = 0;       						// clear DMA interrupt flag
	IEC1bits.DMA2IE = 1;       						// enable DMA1 interrupts
	IPC6bits.DMA2IP = 5;		//TODO: check interference with timer!!!					// set priority of interrupt

	DMA2CONbits.CHEN	= 1;						// enable channel	
}
/*! \brief initialises DMA channel 3 for CAN 1 Tx data transfer
 */
void initDmaChannel3(void)
{
	
	//DMA3CON		= 0x2020;	// 0010 0000 0010 0000
	DMA3CONbits.CHEN	= 0;						// disable channel
	DMA3CONbits.SIZE	= 0;						// data transfer size set to word
	DMA3CONbits.DIR		= 1;						// Read from RAM, write to peripheral
	DMA3CONbits.HALF	= 0;						// Interrupt at end of block transfer
	DMA3CONbits.NULLW	= 0;						// Normal operation
	DMA3CONbits.AMODE	= 0b10;						// Peripheral indirect addressing mode
	//DMA0CONbits.AMODE	= 0b00;						// Register indirect addressing mode (as recommended by errata workaround pdf)
	DMA3CONbits.MODE	= 0;						// Continuos, (ping-pong disabled)
	DMA3PAD 			= (unsigned) &C1TXD;					// Address of ECAN Tx module (loaded into Peripheral Address register)
	DMA3CNT				= 0x7;						// Number of DMA transfers in a block (+1) i.e. 8
	DMA3REQ				= 70;						// Source of interrupt request to initiate transfer set to ECAN1 transmission
	DMA3STA				= __builtin_dmaoffset(CanMessageBuffer);
	DMA3CONbits.CHEN	= 1;						// enable channel	
}

/*! \brief is the DMA (complete) interrupt for CAN Rx events.
 */
void __attribute__((interrupt, auto_psv)) _DMA2Interrupt(void)
{
    unsigned int msgID = 0;                         // used to locally contain the ID of received CAN messages
    unsigned int canData[4];			// used to store the data from received CAN message
    unsigned int dataLength;
    IFS1bits.DMA2IF	= 0; 	// reset interrupt flag

   // LED1=1;

    //TODO: check relevance of interrupt disabling here!
    //_NSTDIS=1;
    dataLength=CANReceive(canData, &msgID);
   // _NSTDIS=0;
    if (dataLength>0)
    {
        if (msgID==CONFIGURATION_MSG_BASE_ID+eePromData.nodeID)
        {
            if ((motorControlState==MOTOR_RESET )||
                (motorControlState==CONFIG_LOADING)
               )
            {
                setConfigurationData(canData,dataLength);
                 //LED1=~LED1;
            }
        }
        else if (msgID==eePromData.referenceValueMessageId)
        {
            setReferenceData(canData,dataLength);
            RESET_CAN_WATCHDOG;
        }
        else if (msgID==eePromData.pidGainsMessageId)
        {
            setPidGains(canData,dataLength);
        }
    }
   // LED1=0;
   

}
/*
 *
 * 			switch (u16Cmd)
				{
					case BOOTLOAD_COMMAND:
						u16Data[0] &= 0xff;
						if(u16Data[0] == node_id)		// if correct node id reset
							{
								__asm__("disi #200");
				    			__asm__ volatile("reset");
							}
					break;
		
					case TRIGGER:
						state = STEP;
					break;
		
					case DES_NODE:
						desired_angle = (int)u16Data[0];			// swap desired neck angle into local buffer
						request_frame[1] = (int)u16Data[0];			// desired Kp
						request_frame[2] = (int)u16Data[1];			// desired Kd
						request_frame[3] = (int)u16Data[2];			// desired Kc
						
					break;
		
					case REQ_NODE:
						request_frame[0] = actual_angle;			// neck angle at this time
						request_frame[1] = (int)u16Data[0];			// desired Kp
						request_frame[2] = (int)u16Data[1];			// desired Kd
						request_frame[3] = (int)u16Data[2];			// desired Kc
						
						Kp = (float)request_frame[1]/256;			// }  								
						Kd = (float)request_frame[2]/256;			// } swap new gains into controller 
						Kc = (float)request_frame[3]/256;			// } 								

						CANTransmit(NODE_OK, &request_frame[0], 4);	// respond to status request	
					break;
				
					default:
						__asm__("nop");		// otherwise do nowt
					break;
				}	// close switch
		
}
 */

/*! \brief is the DMA (complete) interrupt for CAN Tx events.
 */
void __attribute__((interrupt, auto_psv)) _DMA3Interrupt(void)
{
	IFS2bits.DMA3IF	= 0; 	// reset interrupt flag		
}

/*! \brief Initialise DMA channel 4 for transfer of ADC data.
 * 
 */

void initDmaChannel4(void)
{

	//DMA4CON		= 0x;
	DMA4CONbits.CHEN 	= 0;	// Disable channel
	DMA4CONbits.SIZE 	= 0;	// Data transfer size (1=byte,0=word)
	DMA4CONbits.DIR		= 0;	// Transfer direction (1=read RAM,write to Periph. 0= read from periph, write to RAM)
	DMA4CONbits.HALF	= 0;	// Early block transfer complete interrupt (1=interrupt on half block transfer,0=int on full block transfer)
	DMA4CONbits.NULLW	= 1;	// Null Data write to peripheral mode (Null data write to peripheral as well as write ro RAM, 0=normal)
	DMA4CONbits.AMODE 	= 0b10;	// DMA channel operating mode	2,3=Peripheral Indirect Addressing mode, 1=Register Indirect without Post-Increment mode, 0=Register Indirect with Post-Increment mode
	DMA4CONbits.MODE	= 0;	// DMA channel opering mode select 0=Continuous, Ping-Pong modes disabled, 2=continuous, ping-pong

	DMA4REQbits.FORCE	= 0;	// Force DMA Transfer (1=single DMA transfer,0=automatic initiated by DMA request)
	DMA4REQbits.IRQSEL	= 13;	// DMA Peripheral IRQ number select (ADC1)

	DMA4STA 	        = (__builtin_dmaoffset(&(adcData[0]))); // start address of DMA RAM
	DMA4PAD 		= (volatile unsigned int) &ADC1BUF0;			// address of peripheral sfr (0x0300)
	DMA4CNT			 = 3;	// we have 4 a2d  s/h channels for  measurement

	IFS2bits.DMA4IF 	= 0;	// Clear DMA interrupt
	IEC2bits.DMA4IE 	= 1;	// enable interrupt
	IPC11bits.DMA4IP 	= 6;	// set priority of interrupt

	DMA4CONbits.CHEN 	= 1;	// enable channel
        adcDataReady=0; //
}

void __attribute__((interrupt, auto_psv)) _DMA4Interrupt(void)
{
	IFS2bits.DMA4IF 		= 0;	// Clear DMA interrupt
	//AD1CON1bits.ASAM		= 0;	// switch off auto sampling sequence
       // LED1=1;                          //switch off LED1 to
        adcDataReady=1;
        filterDCCurrentMeasurements();


        //LED1=0;
	//flags.conversion1_done  = 1;	// set flag
};

void waitUnitlAdcDataIsReady()
{
    while (adcDataReady!=1)
    {
       // LED1=~LED1; //toggle during wait
        AD1CON1bits.ASAM		= 1;	// switchon auto sampling sequence, for debugging purposes only
    };
    //adcDataReady is set to 1 in the DMA4 ISR


}

void invalidateADCData()
{
     adcDataReady=0; //invalidate data, so that only the next interrupt will set data ready flag
}