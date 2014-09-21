/*
 * drive.h -- libvex
 * The driving related helper functions source. 
 *
 * Copyright (C) 2014 Karim Alibhai.
 */

void setMotors(int F1, int F2, int B1, int B2);
void enableDrive(int js, int channel);
void enableSpeedDrive(int js, int channel);
void enableTurn(int js, int channel);
