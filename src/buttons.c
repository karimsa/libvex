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
