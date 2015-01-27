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
