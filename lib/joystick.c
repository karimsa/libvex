/*
 * joystick.c -- libvex
 * Joystick helper functions.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * sets the minimum value that must be read off a joystick channel
 * @param value the minimum value to be used
 **/
void setJSTolerance(int value) {
	LV_JOYSTICK_TOLERANCE = value < 0 ? -value : value;
}

/**
 * get analog value for joystick on channel axis
 * @param joystick the joystick number
 * @param channel the axis number (on controller)
 * @return integer value between 127 to -127
 **/
int getJSAnalog(int joystick, int channel) {
     int tmp = GetJoystickAnalog(joystick, channel);
     return (tmp > LV_JOYSTICK_TOLERANCE || tmp < -LV_JOYSTICK_TOLERANCE) ? tmp : 0;
}

/**
 * get pressed state of the button
 * @param joystick the joystick number
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
 * forward a joystick axis to a motor and restrict by encoding
 * @param joystick the joystick number
 * @param channel the axis channel
 * @param motor the motor pin
 * @param inverse whether to invert the direction (1=Yes, 0=No)
 * @param min the minimum encoding value
 * @param max the maximum encoding value
 **/
void JSToMotorIME(int joystick, int channel, int motor, int inverse, long min, long max) {
     long enc = GetIntegratedMotorEncoder(motor);
     SetMotor(motor, enc > min && enc < max ? (getJSAnalog(joystick, channel) * (inverse == 1 ? -1 : 1)) : 0);
}

/**
 * forward a joystick axis to a motor group
 * @param joystick the joystick number
 * @param channel the axis channel
 * @param group the initialized motor group
 **/
void JSToMotorGroup(int joystick, int channel, LV_MOTOR_GROUP *group) {
    setMotors(group, getJSAnalog(joystick, channel));
}

/**
 * forward a joystick axis to a motor group  and restrict by encoding
 * @param joystick the joystick number
 * @param channel the axis channel
 * @param group the initialized motor group
 * @param IME the pin of the motor with an IME
 * @param min the minimum encoding
 * @param max the maximum encoding
 **/
void JSToMotorGroupIME(int joystick, int channel, LV_MOTOR_GROUP *group, int IME, long min, long max) {
    long enc = GetIntegratedMotorEncoder(IME);
    setMotors(group, enc > min && enc < max ? getJSAnalog(joystick, channel) : 0);
}
