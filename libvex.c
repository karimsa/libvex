#ifdef __LIBVEX_H
#define __LIBVEX_H
/*
 * buttons.c -- libvex
 * Button state helpers.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * checks if a button is pressed
 * @param button the constant representing the button
 * @return 1=true, 0=false
 **/
int isButtonPressed(int button) {
    int joystick, channel, btn;
    
    switch (button) {
           default:
                   joystick = -1;
                   channel = -1;
                   btn = -1;
                   break;
    }
    
    return joystick == -1 ? 0 : getJSDigital(joystick, channel, btn);
}
/*
 * drive.c -- libvex
 * The driving related helper functions source. 
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

int /*!the pin of the front left wheel*/ LV_F1 = -1,
	/*!the pin of the front right wheel*/ LV_F2 = -1,
	/*!the pin of the back left wheel*/ LV_B1 = -1,
	/*!the pin of the back right wheel*/ LV_B2 = -1,
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
    return (LV_F1 > 0 && LV_F1 < 11 && LV_F2 > 0 && LV_F2 < 11 && LV_B1 > 0 && LV_B1 < 11 && LV_B2 > 0 && LV_B2 < 11);
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
     LV_F1 = F1;
     LV_F2 = F2;
     LV_B1 = B1;
     LV_B2 = B2;

     // reset wheels if invalid pins are given
     if (!isWheelsSet()) {
         LV_F1 = -1;
         LV_F2 = -1;
         LV_B1 = -1;
         LV_B2 = -1;
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

         // handle turning
         if (LV_TURN_ENABLED) {
             tVal = getJSAnalog(LV_TURN_JOYSTICK, LV_TURN_CHANNEL);

             if (tVal > 10) {
                 SetMotor(WHEEL_F1, (LV_DRIVE_ENABLED == 2 ? 127 : dVal) * -1);
                 SetMotor(WHEEL_B1, (LV_DRIVE_ENABLED == 2 ? 127 : dVal) * -1);
                 SetMotor(WHEEL_F2, (LV_DRIVE_ENABLED == 2 ? 127 : dVal) / 2);
                 SetMotor(WHEEL_B2, (LV_DRIVE_ENABLED == 2 ? 127 : dVal) / 2);
             } else {
                 SetMotor(WHEEL_F1, ((LV_DRIVE_ENABLED == 2 ? 127 : dVal) / 2) * -1);
                 SetMotor(WHEEL_B1, ((LV_DRIVE_ENABLED == 2 ? 127 : dVal) / 2) * -1);
                 SetMotor(WHEEL_F2, (LV_DRIVE_ENABLED == 2 ? 127 : dVal));
                 SetMotor(WHEEL_B2, (LV_DRIVE_ENABLED == 2 ? 127 : dVal));
             }
         } else {
             SetMotor(WHEEL_F1, (LV_DRIVE_ENABLED == 2 ? 127 : dVal) * -1);
             SetMotor(WHEEL_B1, (LV_DRIVE_ENABLED == 2 ? 127 : dVal) * -1);
             SetMotor(WHEEL_F2, (LV_DRIVE_ENABLED == 2 ? 127 : dVal));
             SetMotor(WHEEL_B2, (LV_DRIVE_ENABLED == 2 ? 127 : dVal));
         }
     }
}
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
void getJSAnalog(int joystick, int channel) {
     int tmp = GetJoystickAnalog(joystick, channel);
     
     // based on the joystick sample code by easyC
     return (tmp > 10 || tmp < -10) ? tmp : 0;
}
/*
 * main.c -- libvex
 * The continous code that does the stuff.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * the continous code that does the stuff
 **/
void LV_DoStuff() {
     LV_DoDrive();
}
#endif __LIBVEX_H
