#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"

#define MAX_BRIGHT 1023
#define MIN_BRIGHT 0

//control blinds
static bool isClosed = false;
static int lightThreshold = MAX_BRIGHT;
static int darkThreshold = MIN_BRIGHT;

//manual override with clapping
static bool isTimerOn = false;
static long lastOverrideMillis = 0;
static long timerMillis = 0;
static int continuousOverrideState = OVERRIDE_NONE;

_Bool isLongPressLeft();
_Bool isLongPressRight();

void setup()
{
    CircuitPlayground.begin();
    Serial.begin(9600);
    lastOverrideMillis = millis();
}

void loop()
{
    int brightness = CircuitPlayground.lightSensor();
    Serial.print("Brightness: "); //log sensor
    Serial.println(brightness);

    if (isTimerOn)
    {
        if (millis() - lastOverrideMillis > timerMillis)
        {
            defaultToggleBlinds();
        }
    }
    else
    {
        //reset override when light state changes
        if (continuousOverrideState == OVERRIDE_DARK && isBright())
        {
            continuousOverrideState = OVERRIDE_NONE;
        }
        else if (continuousOverrideState == OVERRIDE_LIGHT && !isBright())
        {
            continuousOverrideState = OVERRIDE_NONE;
        }

        //open or close blinds when manual override is off
        if (continuousOverrideState == OVERRIDE_NONE)
        {
            defaultToggleBlinds();
        }
    }

    //check for calibration inputs
    calibrate(
        &darkThreshold,
        &lightThreshold,
        isBright,
        &isTimerOn,
        &continuousOverrideState,
        &timerMillis);

    //check for serial inputs
    checkSerialInputs();

    //run every second
    delay(1000);
}

bool isBright()
{
    return CircuitPlayground.lightSensor() > (lightThreshold + darkThreshold) / 2;
}

void openBlinds()
{
    CircuitPlayground.redLED(true);
    if (!isClosed)
    {
        return;
    }
    isClosed = false;
    //TODO
}

void closeBlinds()
{
    CircuitPlayground.redLED(false);
    if (isClosed)
    {
        return;
    }
    isClosed = true;
    //TODO
}

void defaultToggleBlinds()
{
    if (isBright())
    {
        openBlinds();
    }
    else
    {
        closeBlinds();
    }
}

void forceToggleBlinds()
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

void continuousOverrideBlinds()
{
    if (isBright())
    {
        continuousOverrideState = OVERRIDE_LIGHT;
    }
    else
    {
        continuousOverrideState = OVERRIDE_DARK;
    }
    forceToggleBlinds();
}

void timerOverrideBlinds()
{
    lastOverrideMillis = millis();
    forceToggleBlinds();
}

void checkSerialInputs()
{
    char input = Serial.read();
    if (input == 'o')
    {
        if (isTimerOn)
        {
            timerOverrideBlinds();
        }
        else
        {
            continuousOverrideBlinds();
        }
    }
}