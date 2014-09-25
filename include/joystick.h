/*
 * joystick.h -- libvex
 * Joystick helper functions.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

int getJSAnalog(int joystick, int channel);
int getJSDigital(int joystick, LV_BUTTON *button);
