#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"
#include "blinds.h"

void setup()
{
    CircuitPlayground.begin();
    Serial.begin(9600);
}

void loop()
{
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

    checkSerialInputs(&state);

    //run every second
    delay(1000);
}

void checkSerialInputs(struct BlindsState *state)
{
    char input = Serial.read();
    if (input == 'o')
        overrideBlinds(state);
}