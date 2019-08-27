#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"
#include "blinds.h"

#define MOTOR_CW A10
#define MOTOR_CCW A9

void setup()
{
    CircuitPlayground.begin();
    Serial.begin(9600);

    //set up motor pins
    pinMode(MOTOR_CW, OUTPUT);
    pinMode(MOTOR_CCW, OUTPUT);
}

void loop()
{
    //spin CW for 5 seconds
    digitalWrite(MOTOR_CW, HIGH);
    digitalWrite(MOTOR_CCW, LOW);
    delay(5000);
    //spin CCW for 5 seconds
    digitalWrite(MOTOR_CCW, HIGH);
    digitalWrite(MOTOR_CW, LOW);
    delay(5000);
    //reset
    digitalWrite(MOTOR_CCW, LOW);

    //log light sensor
    Serial.print("Brightness: "); //log sensor
    Serial.println(CircuitPlayground.lightSensor());

    //create blinds state
    static struct BlindsState state = {
        .isTimerOn = false,
        .lastOverrideMillis = 0L,
        .timerMillis = 0L,
        .isContinuousOverrideOn = false,
        .lastLightState = true,
        .isClosed = false,
        .lightThreshold = MAX_BRIGHT,
        .darkThreshold = MIN_BRIGHT};

    //calibrates blinds state properties
    calibrate(&state);

    //controller
    operateBlinds(&state);

    //check computer inputs for debugging
    processSerialInputs(&state);

    //run every second
    delay(1000);
}

//send inputs from computer
void processSerialInputs(struct BlindsState *state)
{
    char input = Serial.read();
    if (input == 'o')
        overrideBlinds(state);
}