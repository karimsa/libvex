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
