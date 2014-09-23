/*
 * drive.c -- libvex
 * The driving related helper functions source. 
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

int /*!the pin of the front left wheel*/ LV_WHEEL_F1 = -1,
	/*!the pin of the front right wheel*/ LV_WHEEL_F2 = -1,
	/*!the pin of the back left wheel*/ LV_WHEEL_B1 = -1,
	/*!the pin of the back right wheel*/ LV_WHEEL_B2 = -1,
	/*!whether or not libvex should handle driving*/ LV_DRIVE_ENABLED = 0,
	/*!the joystick which should handle driving*/ LV_DRIVE_JOYSTICK = 0,
	/*!the channel on the joystick handling driving*/ LV_DRIVE_CHANNEL = 0,
	/*!whether or not libvex should handle turning*/ LV_TURN_ENABLED = 0,
	/*!the joystick which should handle turning*/ LV_TURN_JOYSTICK = 0,
	/*!the channel on the joystick handling turning*/ LV_TURN_CHANNEL = 0;

/**
 * check if wheels are correctly set
 * @return 1=true, 0=false
 **/
int isWheelsSet() {
    return (LV_WHEEL_F1 > 0 && LV_WHEEL_F1 < 11 && LV_WHEEL_F2 > 0 && LV_WHEEL_F2 < 11 && LV_WHEEL_B1 > 0 && LV_WHEEL_B1 < 11 && LV_WHEEL_B2 > 0 && LV_WHEEL_B2 < 11);
}

/**
 * configuration of the wheel motor pins.
 * @param F1 the pin of the front left wheel
 * @param F2 the pin of the front right wheel
 * @param B1 the pin of the back left wheel
 * @param B2 the pin of the back right wheel
 **/
void setWheels(int F1, int F2, int B1, int B2) {
     // set pin numbers, globally
     LV_WHEEL_F1 = F1;
     LV_WHEEL_F2 = F2;
     LV_WHEEL_B1 = B1;
     LV_WHEEL_B2 = B2;

     // reset wheels if invalid pins are given
     if (!isWheelsSet()) {
         LV_WHEEL_F1 = -1;
         LV_WHEEL_F2 = -1;
         LV_WHEEL_B1 = -1;
         LV_WHEEL_B2 = -1;
     }
}

/**
 * enables libvex to handle driving using given config
 * @param js the joystick number (1=Right, 2=Left)
 * @param channel the joystick axis number (on controller)
 **/
void enableDrive(int js, int channel) {
     // only enable driving if the motors are set
     if (isWheelsSet()) {
         LV_DRIVE_ENABLED = 1;
         LV_DRIVE_JOYSTICK = js;
         LV_DRIVE_CHANNEL = channel;
     }
}

/**
 * enables libvex to handle speed driving using given config
 * @param js the joystick number (1=Right, 2=Left)
 * @param channel the joystick axis number (on controller)
 **/
void enableSpeedDrive(int js, int channel) {
     // only enable driving if the motors are set
     if (isWheelsSet()) {
         LV_DRIVE_ENABLED = 2;
         LV_DRIVE_JOYSTICK = js;
         LV_DRIVE_CHANNEL = channel;
     }
}

/**
 * enables libvex to handle turning using given config
 * @param js the joystick number (1=Right, 2=Left)
 * @param channel the joystick axis number (on controller)
 **/
void enableTurn(int js, int channel) {
     // only enable driving if the motors are set
     if (isWheelsSet() && LV_DRIVE_ENABLED == 1) {
         LV_TURN_ENABLED = 1;
         LV_TURN_JOYSTICK = js;
         LV_TURN_CHANNEL = channel;
     }
}

/**
 * continous code for driving and turning
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
                     SetMotor(LV_WHEEL_F1, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal) * -1);
                     SetMotor(LV_WHEEL_B1, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal) * -1);
                     SetMotor(LV_WHEEL_F2, 32 * (dVal > 0 ? 1 : -1));
                     SetMotor(LV_WHEEL_B2, 32 * (dVal > 0 ? 1 : -1));
                 } else if (tVal != 0) {
                     SetMotor(LV_WHEEL_F1, 32 * (dVal > 0 ? -1 : 1));
                     SetMotor(LV_WHEEL_B1, 32 * (dVal > 0 ? -1 : 1));
                     SetMotor(LV_WHEEL_F2, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal));
                     SetMotor(LV_WHEEL_B2, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal));
                }
             } else {
                 SetMotor(LV_WHEEL_F1, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal) * -1);
                 SetMotor(LV_WHEEL_B1, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal) * -1);
                 SetMotor(LV_WHEEL_F2, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal));
                 SetMotor(LV_WHEEL_B2, (LV_DRIVE_ENABLED == 2 ? (127 * (dVal > 0 ? 1 : -1)) : dVal));
             }
         } else {
             SetMotor(LV_WHEEL_F1, 0);
             SetMotor(LV_WHEEL_B1, 0);
             SetMotor(LV_WHEEL_F2, 0);
             SetMotor(LV_WHEEL_B2, 0);
         }
     }
}
