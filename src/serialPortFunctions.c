/*
serialPortFunctions.c
Project: motorDriver3, Myoroboticc
Device/Target: dsPIC33FJ128MC802 on motorDriverBoard V3
Author(s): A. LENZ
Functionality: see serialPortFunctions.h
Change History:
				2014-07-28	: Initial Release
*/

#include <p33FJ128MC802.h>
#include "initIO.h"
#include "motorControl.h"

/*
*	set-up the serial port
*   here we aim to achieve a data transfer rate of 57.6 kbit/s,
*   based on Fcycle=40Mhz (40MIPS with 80MHz clock)
*   BaudRate=Fcycle/(16*(BRG+1))
*   ==> BRG=Fcy/(16*BaudRate) - 1 = 40Mhz/(16*57600) - 1 = 42.40
*   ==> choose 42 ==> BaudRate= 58.139  kbit/s, which is ~ 1% off.
*/
void setupUART2(void)
{
	U2MODEbits.UARTEN=0; //switch the uart off during set-up
	U2BRG=42; // baud rate register
	U2MODEbits.LPBACK=0; // in loopback mode for test! TODO: set to no loop-back after test
	
	U2MODEbits.WAKE=0; //do not wake up on serial port activity

	U2MODEbits.ABAUD=0; //no auto baud rate detection
	U2MODEbits.PDSEL=0; //select 8 bits date, no parity
	U2MODEbits.STSEL=0; //one stop bit



	IFS1bits.U2RXIF=0; //reset the receive interrupt flag
	IFS1bits.U2TXIF=0; //reset the transmission interrupt flag
	_U2RXIP=5; //set the RX interrupt priority
	_U2TXIP=0; //set the TX interrupt priority

	U2STAbits.URXISEL=0; //generate a receive interrupt as soon as a character has arrived
	U2STAbits.UTXEN=1; //enable the transmission of data

	_U2RXIE=1; //enable the receive interrupt
	_U2TXIE=0; //disable the transmit interrupt

	//FINALLY, 
	U2MODEbits.UARTEN=1; //switch the uart on

        U2STAbits.UTXEN=1; //enable transmission
	
	
	
}


void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{	
	/**_LATB1=~_LATB1;*/
	/**Set the UART2 receiving interrupt flag to zero*/
	IFS1bits.U2RXIF=0;

	
	unsigned int rxData; // a local buffer to copy the data into
	
	//toggle an LED when a byte arrives
	//LED3=~LED3;

	
	//we should now read out the data
	rxData=U2RXREG;

	//we should also clear the overflow bit if it has been set (i.e. if we were to slow to read out the fifo)
	U2STAbits.OERR=0; //we reset it all the time
	//some notes on this from the data sheet
	/*
	If the FIFO is full (four characters) and a fifth character is fully received into the UxRSR register,
	the overrun error bit, OERR (UxSTA<1>), will be set. The word in UxRSR will be kept, but further
	transfers to the receive FIFO are inhibited as long as the OERR bit is set. The user must clear
	the OERR bit in software to allow further data to be received.
	If it is desired to keep the data received prior to the overrun, the user should first read all five
	characters, then clear the OERR bit. If the five characters can be discarded, the user can simply
	clear the OERR bit. This effectively resets the receive FIFO and all prior received data is lost.

	The data in the receive FIFO should be read prior to clearing the OERR bit. The
	FIFO is reset when OERR is cleared, which causes all data in the buffer to be lost.
	*/


        //
       // LED1=~LED1;

   

        if ((motorControlState==CONFIG_LOADING)||(motorControlState==MOTOR_RESET))
        {
            setSerialConfigurationData(rxData);
                 //echo data back for test
              U2TXREG=rxData;
        }



}


/**---------------------------------------------------------------------
* Function Name: _U2TXInterrupt
*  Description:   UART 2 Transmission Interrupt Handler
* Inputs:        None
*  Returns:       None
*-----------------------------------------------------------------------
*/

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
{

	/**Set the UART2 transmission interrupt flag to zero*/
	IFS1bits.U2TXIF=0;
	
}
