/*****************************************************
 * easyC - Copyright (C) VEX Robotics                *
 *              NOT PART OF LIBVEX                   *
 ****************************************************/
#ifndef __API_H
#define __API_H

#include <stdio.h>
#include <stdlib.h>

// NOT NEEDED FOR TESTING
// #include <globaldata.h>

void IO_Initialization(void);
void DefineControllerIO(unsigned char ucP1, unsigned char ucP2, unsigned char ucP3, unsigned char ucP4,
            unsigned char ucP5, unsigned char ucP6, unsigned char ucP7, unsigned char ucP8,
            unsigned char ucP9, unsigned char ucP10, unsigned char ucP11, unsigned char ucP12);
void DefineImeTable(unsigned char ucMotor1I2C, unsigned char ucucIme2I2C, unsigned char ucMotor3I2C, unsigned char ucMotor4I2C, unsigned char ucMotor5I2C, 
                    unsigned char ucMotor6I2C, unsigned char ucMotor7I2C, unsigned char ucMotor8I2C, unsigned char ucMotor9I2C, unsigned char ucMotor10I2C);
void DefineMotorTypes(unsigned char ucMotorType1, unsigned char ucMotorType2, unsigned char ucMotorType3, unsigned char ucMotorType4, unsigned char ucMotorType5, 
                      unsigned char ucMotorType6, unsigned char ucMotorType7, unsigned char ucMotorType8, unsigned char ucMotorType9, unsigned char ucMotorType10);

void SetTeamInfo(const char *sz);

void SetCompetitionMode(int nCompTime, int nOperTime);
void SetAutonomousMode(unsigned char ucMode);

unsigned char GetDigitalInput(unsigned char ucPort);
void SetDigitalOutput(unsigned char ucPort, unsigned char ucValue);
unsigned int GetAnalogInput(unsigned char ucPort);
unsigned int GetAnalogInputHR(unsigned char ucPort);

void StartEncoder(unsigned char ucPort);
void StopEncoder(unsigned char ucPort);
long GetEncoder(unsigned char ucPort);
void PresetEncoder(unsigned char ucPort, long lPresetValue);

void StartQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB, unsigned char ucInvert);
void StopQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB);
long GetQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB);
void PresetQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB, long lPresetValue);

void StartInterruptWatcher(unsigned char port, unsigned char direction);
void StopInterruptWatcher(unsigned char port);
unsigned char GetInterruptWatcher(unsigned char port);

void SetMotor(unsigned char ucMotor, int iSpeed);
void SetServo(unsigned char ucMotor, int iSpeed);

void Arcade2(unsigned char ucJoystick,
                unsigned char ucMoveChannel, unsigned char ucRotateChannel,
                unsigned char ucLeftMotor, unsigned char ucRightMotor,
                unsigned char ucLeftInvert, unsigned char ucRightInvert);              
void Arcade4(unsigned char ucJoystick,
            unsigned char ucMoveChannel, unsigned char ucRotateChannel,
            unsigned char ucLeftfrontMotor, unsigned char ucRightfrontMotor,
            unsigned char ucLeftrearMotor, unsigned char ucRightrearMotor,
            unsigned char ucLeftfrontInvert, unsigned char ucRightfrontInvert,
            unsigned char ucLeftrearInvert, unsigned char ucRightrearInvert);
void Tank2(unsigned char ucJoystick,
            unsigned char ucLeftChannel, unsigned char ucRightChannel,
            unsigned char ucLeftMotor, unsigned char ucRightMotor,
            unsigned char ucLeftInvert, unsigned char ucRightInvert);
void Tank4(unsigned char ucJoystick,
            unsigned char ucLeftChannel, unsigned char ucRightChannel,
            unsigned char ucLeftfrontMotor, unsigned char ucRightfrontMotor,
            unsigned char ucLeftrearMotor, unsigned char ucRightrearMotor,
            unsigned char ucLeftfrontInvert, unsigned char ucRightfrontInvert,
            unsigned char ucLeftrearInvert, unsigned char ucRightrearInvert);                  
void Holonomic(unsigned char ucJoystick, 
        unsigned char ucMoveChannel1, unsigned char ucMoveChannel2, unsigned char ucRotateChannel, 
            unsigned char ucLeftfrontMotor, unsigned char ucRightfrontMotor,
            unsigned char ucLeftrearMotor, unsigned char ucRightrearMotor,
            unsigned char ucLeftfrontInvert, unsigned char ucRightfrontInvert,
            unsigned char ucLeftrearInvert, unsigned char ucRightrearInvert);           
void JoystickToMotor(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucMotor, unsigned char ucInv);
void JoystickToMotorAndLimit(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucMotor, unsigned char ucInv, unsigned char ucPositiveLimitSwitch, unsigned char ucNegativeLimitSwitch);
void JoystickToServo(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucMotor, unsigned char ucInv);
void JoystickDigitalToMotor(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucFirstButton, int nFirstButtonValue, unsigned char ucSecondButton, int nSecondButtonValue, unsigned char ucMotor);
void JoystickDigitalToServo(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucFirstButton, int nFirstButtonValue, unsigned char ucSecondButton, int nSecondButtonValue, unsigned char ucMotor);
void JoystickDigitalToMotorAndLimit(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucFirstButton, int nFirstButtonValue, unsigned char ucFirstLimitSwitch, unsigned char ucSecondButton, int nSecondButtonValue, unsigned char ucSecondLimitSwitch, unsigned char ucMotor);
void JoystickToDigitalOutput(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucButton, unsigned char ucDout);
void JoystickToDigitalLatch(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucButton, unsigned char ucDout);
int GetJoystickAnalog(unsigned char ucJoystick, unsigned char ucChannel);
unsigned char GetJoystickDigital(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucButton);
int GetJoystickAccelerometer(unsigned char ucJoystick, unsigned char ucAxis);
void GetJoystickAccelerometerEx(unsigned char ucJoystick, int *pnAxisX, int *pnAxisY);
void SetJoystickAnalogDeadband(unsigned char ucPort, unsigned char ucChannel, unsigned char ucPosValue, unsigned char ucNegValue);
void SetJoystickAccelDeadband(unsigned char ucPort, unsigned char ucAxis, unsigned char ucPosValue, unsigned char ucNegValue);

void PrintToScreen(const char *fmt, ...);

void Wait(long lTime);
unsigned long GetMsClock(void);

void StartTimer(unsigned char ucTimerNumber);
void StopTimer(unsigned char ucTimerNumber);
void PresetTimer(unsigned char ucTimerNumber, unsigned long ulValue);
unsigned long GetTimer(unsigned char ucTimerNumber);

unsigned int GetUltrasonic(unsigned char ucEcho, unsigned char ucPing);
unsigned int GetUltrasonicCm(unsigned char ucEcho, unsigned char ucPing);
void StartUltrasonic(unsigned char ucEcho, unsigned char ucPing);
void StopUltrasonic(unsigned char ucEcho, unsigned char ucPing);

void ResetGD(void);
void ClearGD(unsigned char ucRow1, unsigned char ucCol1, unsigned char ucRow2, unsigned char ucCol2, unsigned char ucFrame);
void PrintTextToGD(unsigned char ucRow, unsigned char ucCol, unsigned long ulColor, const char *szText, ...);
void PrintFrameToGD(unsigned char ucRow1, unsigned char ucCol1, unsigned char ucRow2, unsigned char ucCol2, unsigned long ulColor);

float GetMainBattery();
float GetBackupBattery();

unsigned int GetRandomNumber(int nMin, int nMax);

void InitLCD(unsigned char ucPort);
unsigned char SetLCDText(unsigned char ucPort, unsigned char nLine, const char *szMsg, ...);
unsigned char SetLCDLight(unsigned char ucPort, unsigned char nLight);
void StartLCDButtonsWatcher(unsigned char ucPort);
void StopLCDButtonsWatcher(unsigned char ucPort);
void GetLCDButtonsWatcher(unsigned char ucPort, unsigned char *b1, unsigned char *b2, unsigned char *b3);

void InitAccelerometer(unsigned char ucPort);
void StartAccelerometer(unsigned char ucPort);
int GetAcceleration(unsigned char ucPort);
void StopAccelerometer(unsigned char ucPort);

void InitGyro(unsigned char ucPort);
void StartGyro(unsigned char ucPort);
void StopGyro(unsigned char ucPort);
int GetGyroAngle(unsigned char ucPort);
void SetGyroType(unsigned char ucPort, unsigned int nType);
void SetGyroDeadband(unsigned char ucPort, char cDeadband);
long GetGyroReal(unsigned char port);

//---- INTEGRATED MOTOR ENCODERS -----------------------------------------------------
#define MAX_IME 10
typedef volatile struct   
{    
  long counter;            
  unsigned short speed;
} ImeData;
unsigned char InitIntegratedMotorEncoders(void);
void PresetIntegratedMotorEncoder(unsigned char ucMotor, long lPresetValue);
long GetIntegratedMotorEncoder(unsigned char ucMotor);
float GetIntegratedMotorEncoderSpeed(unsigned char ucMotor);
void GetIntegratedMotorEncodersData(ImeData ime[MAX_IME]);
void SetSaveCompetitionIme(unsigned char ucSave);
long GetSavedCompetitionIme(unsigned char ucMotor);
//---- PID ------------------------------------------------------------------------------
void DefineIntegratedMotorEncoderPID(unsigned char ucMotor, float fKc, float fTi  , float fTd, long lTolerance);
void StartIntegratedMotorEncoderPID(unsigned char ucMotor, long lSetpoint);
void UpdateSetpointIntegratedMotorEncoderPID(unsigned char ucMotor, long lSetpoint);
unsigned char OnTargetIntegratedMotorEncoderPID(unsigned char ucMotor);
void StopIntegratedMotorEncoderPID(unsigned char ucMotor);
void IME_GetPIDControlData(unsigned char ucMotor, unsigned char *pucEnabled, long *plSetPoint, int *pnPower, long *plError, long *plChangeError, long *plAccumError);

//---- SMART TASKS / WAIT UNTIL ----------------------------------------------------------
void WaitUntilDigitalInput(unsigned char ucPort, unsigned char ucValue);
void WaitUntilAnalogInput(unsigned char ucPort, unsigned int uiMin, unsigned int uiMax, unsigned char ucConditionType);
void WaitUntilAnalogInputHR(unsigned char ucPort, unsigned int uiMin, unsigned int uiMax, unsigned char ucConditionType);
void WaitUntilEncoder(unsigned char ucPort, long lPresetValue, long lMin, long lMax, unsigned char ucConditionType);
void WaitUntilQuadEncoder(unsigned char channelA, unsigned char channelB, long lPresetValue, long lMin, long lMax, unsigned char ucConditionType);
void WaitUntilUltrasonic(unsigned char ucEcho, unsigned char ucPing, unsigned char ucMin, unsigned char ucMax, unsigned char ucConditionType);
void WaitUntilAccelerometer(unsigned char ucPort, int nMin, int nMax, unsigned char ucConditionType);
void WaitUntilGyro(unsigned char ucPort, unsigned int uiType, char cDeadband, int nMin, int nMax, unsigned char ucConditionType);
void WaitUntilIntegratedMotorEncoder(unsigned char ucMotor, long lPresetValue, long lMin, long lMax, unsigned char ucConditionType);
void WaitUntilIntegratedMotorEncoderSpeed(unsigned char ucMotor, float fMin, float fMax, unsigned char ucConditionType);

//---- SMART TASKS / MOTOR MODULE ----------------------------------------------------------
void MotorTimeControl(unsigned char ucMotor, int nPower, long lTime);
void MultiMotorTimeControl(unsigned char ucNumMotors, unsigned char ucMotor1, unsigned char ucMotor2, unsigned char ucMotor3, unsigned char ucMotor4, unsigned char ucInvert1, unsigned char ucInvert2 , unsigned char ucInvert3 , unsigned char ucInvert4 , int nPower, long lTime);
void SmartMotorDegrees(unsigned char ucMotor, int nPower,  int nDegrees);
void SmartMotorRotations(unsigned char ucMotor, int nPower,  float fRotations);
void SmartMultiMotorDegrees(unsigned char ucNumMotors , unsigned char ucMasterMotor , unsigned char ucMotor1, unsigned char ucMotor2, unsigned char ucMotor3, unsigned char ucMotor4, unsigned char ucInvert1, unsigned char ucInvert2 , unsigned char ucInvert3 , unsigned char ucInvert4 , int nPower, int nDegrees);
void SmartMultiMotorRotations(unsigned char ucNumMotors , unsigned char ucMasterMotor , unsigned char ucMotor1, unsigned char ucMotor2, unsigned char ucMotor3, unsigned char ucMotor4, unsigned char ucInvert1, unsigned char ucInvert2 , unsigned char ucInvert3 , unsigned char ucInvert4 , int nPower, float fRotations);
//---- SMART TASKS / ROBOT DRIVING  --------------------------------------------------------
void DefineRobotMotors(unsigned char ucGearing, unsigned char ucMasterMotor,
            unsigned char ucLeftfrontMotor, unsigned char ucRightfrontMotor,
            unsigned char ucLeftrearMotor, unsigned char ucRightrearMotor,
            unsigned char ucLeftfrontInvert, unsigned char ucRightfrontInvert,
            unsigned char ucLeftrearInvert, unsigned char ucRightrearInvert);
void DriveRobot(int nPower);
void TurnRobotCenter(int nPower);
void TurnRobotSwing(int nPower);
void StopRobot();
void DriveRobotTimeControl(int nPower, long lTime);
void TurnRobotCenterTimeControl(int nPower, long lTime);
void TurnRobotSwingTimeControl(int nPower, long lTime);
void DriveSmartMotorsDegrees(int nPower, int nDegrees);
void DriveSmartMotorsRotations(int nPower,  float fRotations);
void TurnSmartMotorsCenterDegrees(int nPower, int nDegrees);
void TurnSmartMotorsCenterRotations(int nPower,  float fRotations);
void DriveRobotCurve(int nPower, float fCurve);
void DriveRobotCurveTimeControl(int nPower, float fCurve, long lTime);
void DriveCurveSmartMotorsDegrees(int nPower, float fCurve, int nDegrees);
void DriveCurveSmartMotorsRotations(int nPower, float fCurve, float fRotations);

//---- MATH -------------------------------------------------------------------------
double LogBase(double dX, double dBase);
double Log(double dX);
double Log10(double dX);
double Exp(double dX);
double Frexp(double dX, int *pExp);
double Ldexp(double dX, int nExp);
double Pow(double dX, double dY);
double Sqrt(double dX);
double Rad2Deg(double dRad);
double Deg2Rad(double dDeg);
double Sin(double dAngle, unsigned char ucUnits);
double Cos(double dAngle, unsigned char ucUnits);
double Tan(double dAngle, unsigned char ucUnits);
double Asin(double dX, unsigned char ucUnits);
double Acos(double dX, unsigned char ucUnits);
double Atan(double dX, unsigned char ucUnits);
unsigned int GetRandomNumber(int nMin, int nMax);
int Abs(int nX);
double Fabs(double dX);
double Floor(double dX);
double Ceil(double dX);
double Modf(double dX, double *pInt);
double Fmod(double dX, double dY);

//---- SPEAKER ------------------------------------------------------------------
unsigned char PlayAudioFile(const char *szFileName, unsigned char  ucRepeat, unsigned char ucPlayAndWait);
void PlayAudioTone(int nFrequency, long lDuration, unsigned char ucPlayAndWait);
void StopAudioPlayer();
void MuteSpeakerOutput(unsigned char ucMute);

//---- USER MEMORY --------------------------------------------------------------
unsigned char UserMemoryDiagnostics();
int OpenMemoryFile(const char *szFileName);
unsigned char CloseMemoryFile(unsigned int nHandler);
int GetMemoryFileLinesNumber(unsigned int nHandler);
unsigned char GetMemoryFileLine(unsigned int nHandler, char* szLine, int nSize);

//---- SERIAL PORT ---------------------------------------------------------------
#define USART_WORD_LENGTH_8B                ((unsigned short)0x0000)
#define USART_WORD_LENGTH_9B                ((unsigned short)0x1000)

#define USART_STOP_BITS_1                   ((unsigned short)0x0000)
#define USART_STOP_BITS_0_5                 ((unsigned short)0x1000)
#define USART_STOP_BITS_2                   ((unsigned short)0x2000)
#define USART_STOP_BITS_1_5                 ((unsigned short)0x3000)

#define USART_PARITY_NO                     ((unsigned short)0x0000)
#define USART_PARITY_EVEN                   ((unsigned short)0x0400)
#define USART_PARITY_ODD                    ((unsigned short)0x0600)

#define USART_HARDWARE_FLOW_CONTROL_NONE    ((unsigned short)0x0000)
#define USART_HARDWARE_FLOW_CONTROL_RTS     ((unsigned short)0x0100)
#define USART_HARDWARE_FLOW_CONTROL_CTS     ((unsigned short)0x0200)
#define USART_HARDWARE_FLOW_CONTROL_RTS_CTS ((unsigned short)0x0300)

#define USART_MODE_RX                       ((unsigned short)0x0004)
#define USART_MODE_TX                       ((unsigned short)0x0008)

#define RX_QUEUE_SIZE 64
#define TX_QUEUE_SIZE 64

void OpenSerialPort(unsigned char ucPort, unsigned long ulBaudRate);
void OpenSerialPortEx(unsigned char ucPort, unsigned long ulBaudRate,
                                            unsigned short usWordLength,
                                            unsigned short usStopBits,
                                            unsigned short usParity,
                                            unsigned short usHardwareFlowControl,
                                            unsigned short usMode);
unsigned char ReadSerialPort(unsigned char ucPort);
void WriteSerialPort(unsigned char ucPort, char cData);
unsigned char GetSerialPortByteCount(unsigned char ucPort);

//-------------------------------------------------------------------------------------
void RegisterRepeatingTimer(unsigned long ulTime, void (*handler)(void));
void CancelTimer(void (*handler)(void));
void RegisterImeInterruptServiceRoutine(void (*handler)(void));
void UnRegisterImeInterruptServiceRoutine(void (*handler)(void));

void SetDebugInfo(unsigned char ucIsOn);

unsigned char IsAutonomous(void);
unsigned char IsEnabled(void);

#define MAX_GLOBAL_DATA 20
#define GlobalData(C) (easyCGlobalData(C))

#endif
