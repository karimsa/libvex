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

// structure of button group
typedef struct
{
        LV_BUTTON btns[1];
        int size;
} LV_BUTTON_GROUP;

// function definitions
LV_BUTTON* defineBtn(int channel, int number);
int isButtonPressed(int joystick, LV_BUTTON* button);
void initButtons();

// BUTTON DEFINITIONS
LV_BUTTON *LV_BTN_L1;
LV_BUTTON *LV_BTN_L2;
LV_BUTTON *LV_BTN_R1;
LV_BUTTON *LV_BTN_R2;
LV_BUTTON *LV_BTN_LUP;
LV_BUTTON *LV_BTN_LRIGHT;
LV_BUTTON *LV_BTN_LDOWN;
LV_BUTTON *LV_BTN_LLEFT;
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
 * joystick.h -- libvex
 * Joystick helper functions.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

int getJSAnalog(int joystick, int channel);
int getJSDigital(int joystick, LV_BUTTON *button);
void JSToMotor(int joystick, int channel, int motor, int inverse);
void JSToMotorIME(int joystick, int channel, int motor, int inverse, long min, long max);
/*
 * main.h -- libvex
 * The continous code that does the stuff.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */
 
void LV_DoStuff();
void LVInit();
/**
 * motors.h
 * some motor-related tools.
 *
 * Copyright (C) 2014 Karim Alibhai.
 **/

void initIME();
void resetIME(int motor);
void initSIME(int motor, int withPID, int tol);
#endif
