/*
 * buttons.c -- libvex
 * Button state helpers.
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

/**
 * checks if a button is pressed (mirror of getJSDigital())
 * @param button the constant representing the button
 * @return 1=true, 0=false
 **/
int isButtonPressed(int button) {
    return getJSDigital(button);
}
