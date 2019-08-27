#include <Adafruit_CircuitPlayground.h>
#include "motor.h"

void motorOpenBlinds(struct Motor motor);
void motorCloseBlinds(struct Motor motor);
void reset(struct Motor motor);

void motorOpenBlinds(struct Motor motor)
{
    Serial.println("Motor open blinds.");
    digitalWrite(motor.pinCw1, LOW);
    digitalWrite(motor.pinCw2, LOW);
    digitalWrite(motor.pinCcw1, HIGH);
    digitalWrite(motor.pinCcw2, HIGH);
    delay(5000);
    reset(motor);
}

void motorCloseBlinds(struct Motor motor)
{
    Serial.println("Motor close blinds");
    digitalWrite(motor.pinCcw1, LOW);
    digitalWrite(motor.pinCcw2, LOW);
    digitalWrite(motor.pinCw1, HIGH);
    digitalWrite(motor.pinCw2, HIGH);
    delay(5000);
    reset(motor);
}

void reset(struct Motor motor)
{
    Serial.println("Motor reset.");
    digitalWrite(motor.pinCw1, LOW);
    digitalWrite(motor.pinCw2, LOW);
    digitalWrite(motor.pinCcw1, LOW);
    digitalWrite(motor.pinCcw2, LOW);
}