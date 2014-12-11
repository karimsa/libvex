/*
 * joystick.c -- libvex
 * Joystick helper functions.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * get analog value for joystick on channel axis
 * @param joystick the joystick number
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

/**
 * forward a joystick axis to a motor
 * @param joystick the joystick number
 * @param channel the axis channel
 * @param motor the motor pin
 * @param inverse whether to invert the direction (1=Yes, 0=No)
 **/
void JSToMotor(int joystick, int channel, int motor, int inverse) {
     SetMotor(motor, getJSAnalog(joystick, channel) * (inverse == 0 ? 1 : -1));
}

/**
 * forward a joystick axis to a motor and restrict by position
 * @param joystick the joystick number
 * @param channel the axis channel
 * @param motor the motor pin
 * @param inverse whether to invert the direction (1=Yes, 0=No)
 * @param min the minimum encoding value
 * @param max the maximum encoding value
 **/
void JSToMotorIME(int joystick, int channel, int motor, int inverse, long min, long max) {
     long enc = GetIntegratedMotorEncoder(motor);
     int tmp = getJSAnalog(joystick, channel) * (inverse == 0 ? 1 : -1);
     
     if (enc < min) {
             tmp = tmp > 0 ? 0 : tmp;
     } else if (enc > max) {
             tmp = tmp < 0 ? 0 : tmp;
     }
     
     SetMotor(motor, tmp);
}
