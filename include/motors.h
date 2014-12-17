/**
 * motors.h
 * some motor-related tools.
 *
 * Copyright (C) 2014 Karim Alibhai.
 **/

typedef struct
{
        int *motors;
        int *inverse;
        int length;
        int _last;
} LV_MOTOR_GROUP;

void initIME();
void resetIME(int motor);
void initIMEProc(int motor, int withPID, int tol);

int setRMotor(int motor, int rpower, int inverse);

LV_MOTOR_GROUP* initMotorGroup(int howMany);
int addMotor(LV_MOTOR_GROUP *group, int pin, int inverse);
void setMotors(LV_MOTOR_GROUP *group, int power);
int setRMotors(LV_MOTOR_GROUP *group, int rpower, int inverse);
void setSMotors(int motors[], int size, LV_MOTOR_GROUP *group, int power);
int setSRMotors(int motors[], int size, LV_MOTOR_GROUP *group, int rpower, int inverse);
void invertMotors(LV_MOTOR_GROUP *group);
