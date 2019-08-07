/* ! \file:   can.h
 * Author: Alexander Lenz
 *
 * Created on 21 September 2012, 09:32
 */

#ifndef CAN_H
#define	CAN_H

/*! \brief defines the RX  message ID that triggers EEPROM configuration during the reset/start-up phase
 * 
 *
 */

//base ID of test message, added to eePromData.nodeID
#define TEST_MESSAGE_01 0x300

//base ID of string message, added to eePromData.nodeID
#define STRING_MESSAGE 0x600

//fixed message Ids, independent of node ID
#define WAKE_UP_MSG_BASE_ID 0x500
#define CONFIGURATION_MSG_BASE_ID 0x700
#define CONFIGURATION_REPLY_ID 0x11

void initCAN(void);
void CANTransmit(unsigned int u16SID, unsigned int* pu16Data, unsigned int u16Datalen);
int CANReceive(unsigned int* canData, unsigned int * messageID);
void CANTransmitString(unsigned int u16SID, char * cString);
void CANTransmitActualControlValue(float actualValue, long encoderPosition);
void CANTransmitAdditionalInternalStates(int motorCurrent, int springDisplacement, int sensor1, int sensor2);
#endif	/* CAN_H */

