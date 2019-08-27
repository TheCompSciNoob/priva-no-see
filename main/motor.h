#ifndef MOTOR_H
#define MOTOR_H

struct Motor
{
    int pinCw1;
    int pinCw2;
    int pinCcw1;
    int pinCcw2;
};

void
motorOpenBlinds(struct Motor motor);

void motorCloseBlinds(struct Motor motor);

#endif