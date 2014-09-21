/*
 * joystick.c -- libvex
 * Joystick helper functions.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * get analog value for joystick on channel axis
 * @param joystick the joystick number (1=Right, 2=Left)
 * @param channel the axis number (on controller)
 * @return integer value between 127 to -127
 **/
int getJSAnalog(int joystick, int channel) {
     int tmp = GetJoystickAnalog(joystick, channel);
     
     // based on the joystick sample code by easyC
     return (tmp > 10 || tmp < -10) ? tmp : 0;
}

/**
 * get pressed state of the button
 * @param button the constant representing the button
 * @return 1=Pressed, 0=Idle
 **/
int getJSDigital(int button) {
    int joystick, channel, btn;
    
    switch (button) {
           case LV_BTN_R1:
                joystick = 1;
                channel = 6;
                btn = 2;
                break;
           
           case LV_BTN_R2:
                joystick = 1;
                channel = 6;
                btn = 1;
                break;
           
           case LV_BTN_L1:
                joystick = 1;
                channel = 5;
                btn = 2;
                break;
           
           case LV_BTN_L2:
                joystick = 1;
                channel = 5;
                btn = 1;
                break;
           
           default:
                joystick = -1;
                channel = -1;
                btn = -1;
                break;
    }
    
    return joystick == -1 ? 0 : GetJoystickDigital(joystick, channel, btn);
}
