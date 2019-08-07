/* 
 * File:   motorControl.h
 * Author: Alexander Lenz
 *
 * Created on 02 September 2012, 19:57
 */

#ifndef MOTORCONTROL_H
#define	MOTORCONTROL_H
#define CONTROL_WATCHDOG_MAX    50
#define INCREMENT_WATCHDOG      (watchDogCounter = watchDogCounter < CONTROL_WATCHDOG_MAX ? watchDogCounter+1 : CONTROL_WATCHDOG_MAX)
#define RESET_WATCHDOG          (watchDogCounter=0)

extern int maxCanWatchDogTimeCounter;


#define CAN_WATCHDOG_TIME_IN_SECONDS 0.8
#define INCREMENT_CAN_WATCHDOG      (canWatchDogCounter = canWatchDogCounter < maxCanWatchDogTimeCounter ? canWatchDogCounter+1 : maxCanWatchDogTimeCounter)
#define RESET_CAN_WATCHDOG          (canWatchDogCounter=0)


#define MYO_PI 3.141593


extern int actualMotorCurrent;



/*! \brief defines the number of control cycles before motor control is enabled.
 * This periode is reserved for the configuration of the motor driver via the CAN network
 */
#define START_UP_TIME 20000

/*! \brief Encodes the status of the motor controller
 */
typedef enum MOTOR_CONTROL_STATE_TYPE
{
            MOTOR_RESET=0,
            CONFIG_LOADING,
            CONFIG_STORED,
            MOTOR_RUNNING,
            MOTOR_WATCHDOG_EVENT,
            MOTOR_STOP


}MOTOR_CONTROL_STATE;


typedef struct struct_EEPROMDATA {

    union {

        struct {
            unsigned ControlMode; //input 0xFFFF: extern (SPI driven),default
                                  //       1: local position
                                  //       2: local velocity
                                  //       3: local current
            unsigned cycleTimeIn100usIncrements; //only valid when local control
                                                 // has been selected
            float PGain;
            float IGain;
            float DGain;
            float positiveSaturation;
            float negativeSaturation;
            float integratorSaturation;
            float currentConversionFactor;

            int EncoderCountsPerRevolution;
            unsigned referenceValueMessageId;
                    //message Format: 4byte float int position, velocity or current
            unsigned actualValueMessageId;
                    //message Format: 4byte float int position, velocity or current
            unsigned pidGainsMessageId;
                    //message Format: 2byte index:   0=no gain config
                    //                               1=Kp
                    //                               2=kd
                    //                               3=ki
                                                     
                    //                4byte float Kd,Kd or Ki, depending on index (or don't care)
                    //                2byte output on (0) or off (1)
            unsigned nodeID;
        };


        unsigned int dataStream[21];



    }; //end union

} EEPROM_DATA;

extern MOTOR_CONTROL_STATE motorControlState;
extern int watchDogCounter;
extern int maxCanWatchDogTimeCounter;
extern int canWatchDogCounter;
extern EEPROM_DATA eePromData;
int getFilteredMotorCurrent(void);
void getConfigDataFromEEProm(void);
void setMotorDrive(int driveValue);
void brakeMotor();
void motorControlLoop();
void setConfigurationData(unsigned * canData,unsigned dataLength);
void setReferenceData(unsigned * canData,unsigned dataLength);
void setPidGains(unsigned * canData,unsigned dataLength);
void printConfigData();
float getDeltaTime();
float getOneOverDeltaTime();
void filterDCCurrentMeasurements();
void resetMotorController();
#endif	/* MOTORCONTROL_H */

