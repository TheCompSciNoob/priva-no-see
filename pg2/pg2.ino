#include <Adafruit_CircuitPlayground.h>

#define TAP_THRESHOLD 5

void onSingleTap();

void setup()
{
    Serial.begin(9600);
    CircuitPlayground.begin();

    //tap detection
    CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
    CircuitPlayground.setAccelTap(1, TAP_THRESHOLD);
    attachInterrupt(digitalPinToInterrupt(7), onSingleTap, RISING);
}

void loop()
{
}

void onSingleTap()
{
    static int timesClicked = 0;
    timesClicked++;
    static bool isRedLedOn = false;
    Serial.print("onSingleTap: ");
    Serial.println(timesClicked);

    isRedLedOn = !isRedLedOn;
    CircuitPlayground.redLED(isRedLedOn);
}