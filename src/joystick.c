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
int getJSDigital(int joystick, LV_BUTTON *button) {
    return GetJoystickDigital(joystick, button->channel, button->number);
}
