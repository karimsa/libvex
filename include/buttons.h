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
