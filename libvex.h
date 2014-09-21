#ifndef __LIBVEX_H
#define __LIBVEX_H
/*
 * buttons.h -- libvex
 * Button state helpers.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

#define LV_BTN_R1 0x01
#define LV_BTN_R2 0x02

#define LV_BTN_L1 0x03
#define LV_BTN_L2 0x04

#define LV_BTN_RUP 0x05
#define LV_BTN_RRIGHT 0x06
#define LV_BTN_RDOWN 0x07
#define LV_BTN_RLEFT 0x08

#define LV_BTN_LUP 0x09
#define LV_BTN_LRIGHT 0x10
#define LV_BTN_LDOWN 0x11
#define LV_BTN_LLEFT 0x12

int isButtonPressed(int button);
/*
 * drive.h -- libvex
 * The driving related helper functions source. 
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

void setMotors(int F1, int F2, int B1, int B2);
void enableDrive(int js, int channel);
void enableTurn(int js, int channel);
/*
 * joystick.h -- libvex
 * Joystick helper functions.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

void getJSAnalog(int joystick, int channel);
void getJSDigital(int joystick, int channel, int btn);
/*
 * main.h -- libvex
 * The continous code that does the stuff.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */
 
void LV_DoStuff();
#endif __LIBVEX_H