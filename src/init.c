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
