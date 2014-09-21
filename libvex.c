#ifdef __LIBVEX_H
#define __LIBVEX_H
/*
 * drive.c -- libvex
 * The driving related helper functions source. 
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

int     /*!the pin of the front left wheel*/ LV_F1,
	/*!the pin of the front right wheel*/ LV_F2,
	/*!the pin of the back left wheel*/ LV_B1,
	/*!the pin of the back right wheel*/ LV_B2,
	/*!whether or not libvex should handle driving*/ LV_DRIVE_ENABLED = 0,
	/*!the joystick which should handle driving*/ LV_DRIVE_JOYSTICK = 0,
	/*!the channel on the joystick handling driving*/ LV_DRIVE_CHANNEL = 0,
	/*!whether or not libvex should handle turning*/ LV_TURN_ENABLED = 0,
	/*!the joystick which should handle turning*/ LV_TURN_JOYSTICK = 0,
	/*!the channel on the joystick handling turning*/ LV_TURN_CHANNEL = 0;

/**
 * configuration of the wheel motor pins.
 * @param F1 the pin of the front left wheel
 * @param F2 the pin of the front right wheel
 * @param B1 the pin of the back left wheel
 * @param B2 the pin of the back right wheel
 **/
void setMotors(int F1, int F2, int B1, int B2) {
	LV_F1 = F1;
	LV_F2 = F2;
	LV_B1 = B1;
	LV_B2 = B2;
}

/**
 * enables libvex to handle driving using given config
 * @param js the joystick number (1=Right, 2=Left)
 * @param channel the joystick axis number (on controller)
 **/
void enableDrive(int js, int channel) {
	LV_DRIVE_ENABLED = 1;
	LV_DRIVE_JOYSTICK = js;
	LV_DRIVE_CHANNEL = channel;
}

/**
 * enables libvex to handle turning using given config
 * @param js the joystick number (1=Right, 2=Left)
 * @param channel the joystick axis number (on controller)
 **/
void enableTurn(int js, int channel) {
	LV_TURN_ENABLED = 1;
	LV_TURN_JOYSTICK = js;
	LV_TURN_CHANNEL = channel;
}
#endif __LIBVEX_H
