#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"

#define MAX_BRIGHT 1023
#define MIN_BRIGHT 0

//control blinds
static bool isClosed = false;
static int lightThreshold = MAX_BRIGHT;
static int darkThreshold = MIN_BRIGHT;

//manual override with clapping
static long baseTime = 0;
static long manualOverrideMillis = 0;

_Bool isLongPressLeft();
_Bool isLongPressRight();

void setup()
{
    CircuitPlayground.begin();
    Serial.begin(9600);
}

void loop()
{
    //open or close blinds based on brightness
    int brightness = CircuitPlayground.lightSensor();
    Serial.print("Brightness: "); //log sensor
    Serial.println(brightness);
    if (brightness > (lightThreshold + darkThreshold) / 2) //theshold is average brightness
    {
        CircuitPlayground.redLED(true);
        openBlinds();
    }
    else
    {
        CircuitPlayground.redLED(false);
        closeBlinds();
    }

    //check for calibration inputs
    calibrate(&darkThreshold, &lightThreshold, &manualOverrideMillis);

    //run every second
    delay(1000);
}

void openBlinds()
{
    if (!isClosed)
    {
        return;
    }
    isClosed = false;
    //TODO
}

void closeBlinds()
{
    if (isClosed)
    {
        return;
    }
    isClosed = true;
    //TODO
}

void toggleBlinds()
{
    if (isClosed)
    {
        openBlinds();
    }
    else
    {
        closeBlinds();
    }
}