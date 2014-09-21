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
