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
int isButtonPressed(int joystick, LV_BUTTON* button) {
    return getJSDigital(joystick, button);
}

/**
 * define the properties of a joystick button
 * @param channel the channel number (on joystick)
 * @param number the button number (on joystick)
 * @return pointer to a new button struct
 */
LV_BUTTON* defineBtn(int channel, int number) {
           LV_BUTTON* tmp = malloc(sizeof(LV_BUTTON));
           tmp->number = number;
           return tmp;
}
/*
LV_BUTTON_GROUP* defineGroup() {
    LV_BUTTON_GROUP* tmp = malloc(sizeof(LV_BUTTON_GROUP));
    tmp->btns = new LV_BUTTON[1];
    tmp->size = 0;
    return tmp;
}

void addButton2Gp(LV_BUTTON *btn, LV_BUTTON_GROUP *btnGroup) {
     LV_BUTTON tmp[btnGroup->size];
     int i;
     
     for (i = 0; i < btnGroup->size; i += 1) {
         tmp[i] = btnGroup->btns[i];
     }
     
     tmp[btnGroup->size - 1] = btn;
     
     btnGroup->size += 1;
     btnGroup->btns = tmp;
}*/

/**
 * defines buttons at runtime
 */
void initButtons() {     
     LV_BTN_L1 = defineBtn(5, 1);
     LV_BTN_L2 = defineBtn(5, 2);
     
     LV_BTN_R1 = defineBtn(6, 1);
     LV_BTN_R2 = defineBtn(6, 2);
     
     LV_BTN_LUP = defineBtn(7, 1);
     LV_BTN_LRIGHT = defineBtn(7, 2);
     LV_BTN_LDOWN = defineBtn(7, 3);
     LV_BTN_LLEFT = defineBtn(7, 4);
}
