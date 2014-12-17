#ifndef _LIBVEX_H
#define _LIBVEX_H
/*
 * buttons.h -- libvex
 * Button state helpers.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

// the structure of a button
typedef struct
{
        int channel;
        int number;
} LV_BUTTON;

// function definitions
LV_BUTTON* defineBtn(int channel, int number);
int isButtonPressed(int joystick, LV_BUTTON* button);
void initButtons();

// BUTTON CONSTANT DEFINITIONS
LV_BUTTON *LV_BTN_L1;
LV_BUTTON *LV_BTN_L2;

LV_BUTTON *LV_BTN_R1;
LV_BUTTON *LV_BTN_R2;

LV_BUTTON *LV_BTN_LUP;
LV_BUTTON *LV_BTN_LDOWN;
LV_BUTTON *LV_BTN_LRIGHT;
LV_BUTTON *LV_BTN_LLEFT;

LV_BUTTON *LV_BTN_RUP;
LV_BUTTON *LV_BTN_RDOWN;
LV_BUTTON *LV_BTN_RRIGHT;
LV_BUTTON *LV_BTN_RLEFT;
/*
 * drive.h -- libvex
 * The driving related helper functions source. 
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

void setWheels(int F1, int F2, int B1, int B2);
void enableDrive(int js, int channel);
void enableSpeedDrive(int js, int channel);
void enableTurn(int js, int channel);
/*
 * init.h -- libvex
 * code that does the stuff.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

void LV_DoStuff();
void LVInit();
/*
 * joystick.h -- libvex
 * Joystick helper functions.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

int LV_JOYSTICK_TOLERANCE = 10;

int getJSAnalog(int joystick, int channel);
int getJSDigital(int joystick, LV_BUTTON *button);
void JSToMotor(int joystick, int channel, int motor, int inverse);
void JSToMotorIME(int joystick, int channel, int motor, int inverse, long min, long max);
/**
 * motors.h
 * some motor-related tools.
 *
 * Copyright (C) 2014 Karim Alibhai.
 **/

typedef struct
{
        int *motors;
        int *inverse;
        int length;
        int _last;
} LV_MOTOR_GROUP;

void initIME();
void resetIME(int motor);
void initIMEProc(int motor, int withPID, int tol);

int setRMotor(int motor, int rpower, int inverse);

LV_MOTOR_GROUP* initMotorGroup(int howMany);
int addMotor(LV_MOTOR_GROUP *group, int pin, int inverse);
void setMotors(LV_MOTOR_GROUP *group, int power);
int setRMotors(LV_MOTOR_GROUP *group, int rpower, int inverse);
void setSMotors(int motors[], int size, LV_MOTOR_GROUP *group, int power);
int setSRMotors(int motors[], int size, LV_MOTOR_GROUP *group, int rpower, int inverse);
void invertMotors(LV_MOTOR_GROUP *group);
#endif
