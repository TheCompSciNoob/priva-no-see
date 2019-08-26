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
    Serial.print("Brightness: "); //log sensor
    Serial.println(CircuitPlayground.lightSensor());

    operateBlinds();

    calibrate();

    checkSerialInputs();

    //run every second
    delay(1000);
}

void checkSerialInputs()
{
    char input = Serial.read();
    if (input == 'o')
        overrideBlinds();
}