/**
 * motors.c
 * some motor-related tools.
 *
 * Copyright (C) 2014 Karim Alibhai.
 **/

void initIME() {
     InitIntegratedMotorEncoders();
}

void resetIME(int motor) {
     PresetIntegratedMotorEncoder(motor, 0);
}

void initSIME(int motor, int withPID, int tol) {
     resetIME(motor);
     
     if (withPID == 1) {
        DefineIntegratedMotorEncoderPID(motor, 0.5, 0, 0.3, tol);
        StartIntegratedMotorEncoderPID(motor, 0);
     }
}
