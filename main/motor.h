#ifndef MOTOR_H
#define MOTOR_H

struct Motor
{
    int pin1;
    int pin2;
    int pin3;
    int pin4;
    long delay;
    int stepsCw;
    int stepsCcw;
};

void setupMotor(struct Motor *motor);

void motorOpenBlinds(struct Motor *motor);

void motorCloseBlinds(struct Motor *motor);

#endif