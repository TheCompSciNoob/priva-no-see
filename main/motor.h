#ifndef MOTOR_H
#define MOTOR_H

struct Motor
{
    int dataPin;  //DS
    int clockPin; //SH_CP
    int latchPin; //ST_CP
    int stepsCw;
    int stepsCcw;
};

void motorOpenBlinds(struct Motor motor);

void motorCloseBlinds(struct Motor motor);

#endif