#include <Adafruit_CircuitPlayground.h>
#include "motor.h"

#define N_STEPS 8

static const int stepperSteps[N_STEPS] = {
    0b00010000,
    0b00011000,
    0b00001000,
    0b00001100,
    0b00000100,
    0b00000110,
    0b00010010};
static int stepperIndex = 0;

void motorOpenBlinds(struct Motor motor);
void motorCloseBlinds(struct Motor motor);
void stepperShift(struct Motor motor, int offset);

void motorOpenBlinds(struct Motor motor)
{
    for (int i = 0; i < motor.stepsCw; i++)
        stepperShift(motor, 1);
}

void motorCloseBlinds(struct Motor motor)
{
    for (int i = 0; i < motor.stepsCcw; i++)
        stepperShift(motor, -1);
}

void stepperShift(struct Motor motor, int offset)
{
    //find stepper index in steps
    stepperIndex -= offset;
    while (stepperIndex < 0)
    {
        stepperIndex += N_STEPS;
    }

    //signal stepper motor
    digitalWrite(motor.latchPin, HIGH);
    shiftOut(motor.dataPin, motor.clockPin, MSBFIRST, stepperSteps[stepperIndex]);
    digitalWrite(motor.latchPin, LOW);
}