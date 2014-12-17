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
 * @param power the relative power (from 0 to 100, or from 0 to 1)
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
LV_MOTOR_GROUP* initMotorGroup(int howMany) {
	LV_MOTOR_GROUP* tmp = malloc(sizeof(LV_MOTOR_GROUP) + (howMany * 2));

	tmp->motors = realloc(tmp->motors, howMany);
	tmp->inverse = realloc(tmp->inverse, howMany);

	tmp->length = howMany;
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
 * @param power the amount of power (between -127 to 127)
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
