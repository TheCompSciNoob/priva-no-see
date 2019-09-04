#include <Adafruit_CircuitPlayground.h>
#include "motor.h"

#define N_STEPS 8

void setupMotor(struct Motor *motor);
void motorOpenBlinds(struct Motor *motor);
void motorCloseBlinds(struct Motor *motor);
void stepperShift(struct Motor *motor, int offset);
void writeStep(struct Motor *motor, int s1, int s2, int s3, int s4);

static int stepperIndex = 0;

void setupMotor(struct Motor *motor)
{
    pinMode(motor->pin1, OUTPUT);
    pinMode(motor->pin2, OUTPUT);
    pinMode(motor->pin3, OUTPUT);
    pinMode(motor->pin4, OUTPUT);
}

void motorOpenBlinds(struct Motor *motor)
{
    for (int i = 0; i < motor->stepsCw; i++)
        stepperShift(motor, 1);
    writeStep(motor, LOW, LOW, LOW, LOW);
}

void motorCloseBlinds(struct Motor *motor)
{
    for (int i = 0; i < motor->stepsCcw; i++)
        stepperShift(motor, -1);
    writeStep(motor, LOW, LOW, LOW, LOW);
}

void stepperShift(struct Motor *motor, int offset)
{
    //find stepper index in steps
    stepperIndex += offset;
    while (stepperIndex < 0) //handle negatives with loop (modulus is inconsistent)
        stepperIndex += N_STEPS;
    stepperIndex %= N_STEPS;
    //translate step to pins to write to
    switch (stepperIndex)
    {
    case 0:
        writeStep(motor, HIGH, LOW, LOW, LOW);
        break;
    case 1:
        writeStep(motor, HIGH, HIGH, LOW, LOW);
        break;
    case 2:
        writeStep(motor, LOW, HIGH, LOW, LOW);
        break;
    case 3:
        writeStep(motor, LOW, HIGH, HIGH, LOW);
        break;
    case 4:
        writeStep(motor, LOW, LOW, HIGH, LOW);
        break;
    case 5:
        writeStep(motor, LOW, LOW, HIGH, HIGH);
        break;
    case 6:
        writeStep(motor, LOW, LOW, LOW, HIGH);
        break;
    case 7:
        writeStep(motor, HIGH, LOW, LOW, HIGH);
        break;
    default:
        writeStep(motor, LOW, LOW, LOW, LOW);
        break;
    }
    delay(motor->delay);
}

void writeStep(struct Motor *motor, int s1, int s2, int s3, int s4)
{
    digitalWrite(motor->pin1, s1);
    digitalWrite(motor->pin2, s2);
    digitalWrite(motor->pin3, s3);
    digitalWrite(motor->pin4, s4);
}