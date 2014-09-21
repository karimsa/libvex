/*
 * externs.h -- libvex
 * definitions of all the easyC API functions used by libvex
 * 
 * Copyright (C) 2014 Karim Alibhai.
 */

extern void SetMotors(int motor, int speed);
extern int GetJoystickAnalog(int joystick, int channel);
extern int GetJoystickDigital(int joystick, int channel, int button);
