#include "libvex.h"
#ifdef _LIBVEX_H
/*
 * buttons.c -- libvex
 * Button state helpers.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * checks if a button is pressed (mirror of getJSDigital())
 * @param joystick the number of the joystick to read from
 * @param button the constant representing the button
 * @return integer 1=true, 0=false
 **/
int isBtnPressed(int joystick, LV_BUTTON* button) {
    return getJSDigital(joystick, button);
}

/**
 * define the properties of a joystick button
 * @param channel the channel number (on joystick)
 * @param number the button number (on joystick)
 * @return LV_BUTTON pointer to a new button struct
 **/
LV_BUTTON* defineBtn(int channel, int number) {
    LV_BUTTON* tmp = malloc(sizeof(LV_BUTTON));
    tmp->number = number;
    return tmp;
}

/**
 * defines buttons at runtime
 **/
void initButtons() {
    LV_BTN_L1 = defineBtn(5, 1);
    LV_BTN_L2 = defineBtn(5, 2);

	LV_BTN_R1 = defineBtn(6, 1);
	LV_BTN_R2 = defineBtn(6, 2);

	LV_BTN_LUP = defineBtn(7, 1);
	LV_BTN_LRIGHT = defineBtn(7, 2);
	LV_BTN_LRIGHT = defineBtn(7, 3);
	LV_BTN_LLEFT = defineBtn(7, 4);

	LV_BTN_RDOWN = defineBtn(7, 1);
	LV_BTN_RUP = defineBtn(7, 2);
	LV_BTN_RRIGHT = defineBtn(7, 3);
	LV_BTN_RLEFT = defineBtn(7, 4);
}
/*
 * drive.c -- libvex
 * driving related helper functions
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

int /*!whether or not libvex should handle driving*/ LV_DRIVE_ENABLED = 0,
	/*!the joystick which should handle driving*/ LV_DRIVE_JOYSTICK = 0,
	/*!the channel on the joystick handling driving*/ LV_DRIVE_CHANNEL = 0,
	/*!whether or not libvex should handle turning*/ LV_TURN_ENABLED = 0,
	/*!the joystick which should handle turning*/ LV_TURN_JOYSTICK = 0,
	/*!the channel on the joystick handling turning*/ LV_TURN_CHANNEL = 0;

/*!holds onto the left and right wheels IDs for turning*/
int LV_DRIVE_LW[2];
int LV_DRIVE_RW[2];

/*!the motor group for the driving motors*/
LV_MOTOR_GROUP* LV_DRIVE_MOTORS;

/**
 * global toggle for if wheels are set
 **/
int isWheelsSet = 0;

/**
 * configuration of the wheel motor pins.
 * @param F1 the pin of the front left wheel
 * @param F2 the pin of the front right wheel
 * @param B1 the pin of the back left wheel
 * @param B2 the pin of the back right wheel
 **/
void setWheels(int F1, int F2, int B1, int B2) {
    if (F1 > 0 && F1 < 11 && F2 > 0 && F2 < 11 && B1 > 0 && B1 < 11 && B2 > 0 && B2 < 11) {
        // create a motor group for the wheels
        LV_DRIVE_MOTORS = initMotorGroup(4);

        // add the motors into the group
        LV_DRIVE_LW[0] = addMotor(LV_DRIVE_MOTORS, F1, 1);
        LV_DRIVE_LW[1] = addMotor(LV_DRIVE_MOTORS, F2, 0);
        LV_DRIVE_RW[0] = addMotor(LV_DRIVE_MOTORS, B1, 1);
        LV_DRIVE_RW[1] = addMotor(LV_DRIVE_MOTORS, B2, 0);

        // globally set wheel confirmation
	isWheelsSet = 1;
    }
}

/**
 * inverts the driving wheels' powers
 **/
void invertDrive() {
    invertMotors(LV_DRIVE_MOTORS);
}

/**
 * enables libvex to handle driving using given config
 * @param joystick the joystick number
 * @param channel the joystick axis number (on controller)
 **/
void enableDrive(int joystick, int channel) {
    // only enable driving if the motors are set
    if (isWheelsSet) {
        LV_DRIVE_ENABLED = 1;
        LV_DRIVE_JOYSTICK = joystick;
        LV_DRIVE_CHANNEL = channel;
    }
}

/**
 * enables libvex to handle speed driving using given config
 * @param joystick the joystick number
 * @param channel the joystick axis number (on controller)
 **/
void enableSpeedDrive(int joystick, int channel) {
    // only enable driving if the motors are set
    if (isWheelsSet) {
        LV_DRIVE_ENABLED = 2;
        LV_DRIVE_JOYSTICK = joystick;
        LV_DRIVE_CHANNEL = channel;
    }
}

/**
 * enables libvex to handle turning using given config
 * @param joystick the joystick number
 * @param channel the joystick axis number (on controller)
 **/
void enableTurn(int joystick, int channel) {
    // only enable driving if the motors are set
    if (isWheelsSet && LV_DRIVE_ENABLED == 1) {
        LV_TURN_ENABLED = 1;
        LV_TURN_JOYSTICK = joystick;
        LV_TURN_CHANNEL = channel;
    }
}

/**
 * continous code for driving and turning
 * call this inside of a while(1) loop.
 **/
void LV_DoDrive() {
    int dVal = 0, tVal = -1;

    // handle driving
    if (LV_DRIVE_ENABLED != 0) {
        dVal = getJSAnalog(LV_DRIVE_JOYSTICK, LV_DRIVE_CHANNEL);

        if (dVal != 0) {
            // handle turning
            if (LV_TURN_ENABLED) {
                tVal = getJSAnalog(LV_TURN_JOYSTICK, LV_TURN_CHANNEL);

                if (tVal > 10) {
                    setMotors(LV_DRIVE_MOTORS, LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal);
                } else if (tVal != 0) {
                    setSMotors(LV_DRIVE_LW, 2, LV_DRIVE_MOTORS, 32 * (dVal > 0 ? -1 : 1));
                    setSMotors(LV_DRIVE_RW, 2, LV_DRIVE_MOTORS, LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal);
                }
            } else {
                setMotors(LV_DRIVE_MOTORS, LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal);
            }
        } else {
            setMotors(LV_DRIVE_MOTORS, 0);
        }
     }
}
/*
 * init.c -- libvex
 * code that does stuff.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * initializes important stuff
 **/
void LVInit() {
     initButtons();
     initIME();
}

/**
 * the continous code that does the stuff
 **/
void LV_DoStuff() {
     LV_DoDrive();
}
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
/**
 * motors.c
 * some motor-related tools.
 *
 * Copyright (C) 2014 Karim Alibhai.
 **/

/**
 * initialize the integrated motor encoders
 **/
void initIME() {
     InitIntegratedMotorEncoders();
}

/**
 * preset the motor's encoder to 0
 **/
void resetIME(int motor) {
     PresetIntegratedMotorEncoder(motor, 0);
}

/**
 * initialize an IME process (call after initIME())
 **/
void initIMEProc(int motor, int withPID, int tol) {
     resetIME(motor);

     if (withPID == 1) {
        DefineIntegratedMotorEncoderPID(motor, 0.5, 0, 0.3, tol);
        StartIntegratedMotorEncoderPID(motor, 0);
     }
}

/**
 * write a relative power value to a motor
 * @param motor the pin of the motor
 * @param rpower the relative power (from 0 to 100, or from 0 to 1)
 * @param inverse whether to invert the power (1=Yes,0=No)
 * @return integer the absolute power used
 **/
int setRMotor(int motor, int rpower, int inverse) {
	// from percent to decimal
	if (rpower > 1)
		rpower /= 100;

	// from relative to absolute
	int power = rpower * 127 * (inverse == 1 ? -1 : 1);

	// write to pin
	SetMotor(motor, power);

	// return absolute value
	return power;
}

/**
 * create a new group of motors
 * @param number the number of motors which will be in this group
 * @return LV_MOTOR_GROUP a group created from the motor group structure
 **/
LV_MOTOR_GROUP* initMotorGroup(int number) {
	LV_MOTOR_GROUP* tmp = malloc(sizeof(LV_MOTOR_GROUP) + (number * 2));

	tmp->motors = realloc(tmp->motors, number);
	tmp->inverse = realloc(tmp->inverse, number);

	tmp->length = number;
	tmp->_last = -1;

	return tmp;
}

/**
 * add a motor to a motor group
 * @param group the initialized motor group
 * @param pin the pin of the motor
 * @param inverse whether or not to inverse the power (1=Yes,0=No)
 * @return integer the index of the new motor
 **/
int addMotor(LV_MOTOR_GROUP *group, int pin, int inverse) {
	group->_last += 1;

	if (group->_last < group->length) {
		group->motors[group->_last] = pin;
		group->inverse[group->_last] = inverse == 1 ? -1 : 1;
		return group->_last;
	}

	return -1;
}

/**
 * set power of all the motors in the group
 * @param group the initialized motor group
 * @param power the amount of power to give (from 127 to -127)
 **/
void setMotors(LV_MOTOR_GROUP *group, int power) {
	int i;

	for (i = 0; i <= group->_last && i < group->length; i += 1) {
		SetMotor(group->motors[i], group->inverse[i] * power);
	}
}

/**
 * power a group of specific motors inside of a larger group
 * @param motors an int-array of motor indexes
 * @param size the size of the int-array
 * @param group the initialized motor group
 * @param power the amount of power (between -127 to 127)
 **/
void setSMotors(int motors[], int size, LV_MOTOR_GROUP *group, int power) {
    int i, j;

    for (i = 0; i < size; i += 1) {
	j = motors[i];
        SetMotor(group->motors[j], power);
    }
}

/**
 * relatively power a group of specific motors inside of a larger group
 * @param motors an int-array of motor indexes
 * @param size the size of the int-array
 * @param group the initialized motor group
 * @param rpower the amount of power (between -127 to 127)
 * @param inverse whether to invert the power (1=Yes,0=No)
 * @return integer the absolute power value
 **/
int setSRMotors(int motors[], int size, LV_MOTOR_GROUP *group, int rpower, int inverse) {
    // from relative to absolute
    int power = 127 * (rpower > 1 ? (rpower / 100) : rpower) * (inverse == 1 ? -1 : 1);

    // power the group
    setSMotors(motors, size, group, power);

    // return absolute value to user
    return power;
}

/**
 * set relative power of all motors in a group
 * @param group the initialized motor group
 * @param rpower the relative power to write (from 0 to 100, or from 0 to 1)
 * @param inverse whether or not to invert the power (1=Yes,0=No)
 * @return integer the absolute value of the relative power
 **/
int setRMotors(LV_MOTOR_GROUP *group, int rpower, int inverse) {
	// from relative to absolute
	int power = 127 * (rpower > 1 ? (rpower / 100) : rpower) * (inverse == 1 ? -1 : 1);

	// write absolute value
	setMotors(group, power);

	// return the used power
	return power;
}

/**
 * inverts all motors in a given motor group
 * @param group the initialized motor group
 **/
void invertMotors(LV_MOTOR_GROUP *group) {
    int i;

    for (i = 0; i <= group->_last && i < group->length; i += 1) {
        group->inverse[i] = group->inverse[i] == 1 ? -1 : 1;
    }
}
#endif
