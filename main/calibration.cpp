#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"

#define MILLIS_PER_MIN 60000L
#define LEFT_NEOS 1001
#define RIGHT_NEOS 1002
#define WHITE_HEX 0xffffff
#define BLINK_DELAY 150
#define BUTTON_LEFT 4
#define BUTTON_RIGHT 19

bool isLongPressLeft();
bool isLongPressRight();
void blinkNeosThrice(int neos[], int size, int hex);
void blinkRainbow();
void calibrateDarkThreshold(int *darkThreshold);
void calibrateLightThreshold(int *lightThreshold);
void resetManualOverrideTimer(long *timerMillis);
void calibrateManualOverrideTimer(long *timerMillis, bool isLongPress(void));
long getRainbowColor(int i, int size);

void calibrate(
    int *darkThreshold,
    int *lightThreshold,
    bool isBright(void),
    bool *isTimerOn,
    int *continuousOverrideState,
    long *timerMillis)
{
    if (CircuitPlayground.slideSwitch()) //slide switch left
    {
        if (isLongPressLeft())
        {
            calibrateDarkThreshold(darkThreshold);
            *continuousOverrideState = OVERRIDE_NONE;
        }
        if (isLongPressRight())
        {
            calibrateLightThreshold(lightThreshold);
            *continuousOverrideState = OVERRIDE_NONE;
        }
    }
    else
    {
        if (isLongPressLeft())
        {
            *isTimerOn = !*isTimerOn;
            Serial.print("Timer mode set to: ");
            Serial.println(*isTimerOn);
            if (*isTimerOn)
            {
                continuousOverrideState = OVERRIDE_NONE;
                blinkRainbow();
            }
            else
            {
                *timerMillis = 0;
                const int size = 10;
                int neos[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                blinkNeosThrice(neos, size, WHITE_HEX);
            }
        }
        if (isLongPressRight())
        {
            if (*isTimerOn)
            {
                resetManualOverrideTimer(timerMillis);
                calibrateManualOverrideTimer(timerMillis, isLongPressRight);
            }
            else //do not allow timer calibration if timer is off
            {
                const int size = 1;
                static int neos[] = {2};
                while (isLongPressRight())
                {
                    blinkNeosThrice(neos, size, WHITE_HEX);
                }
            }
        }
    }
}

bool isLongPressLeft()
{
    if (!CircuitPlayground.leftButton())
    {
        return false;
    }
    delay(1000);
    return CircuitPlayground.leftButton();
}

bool isLongPressRight()
{
    if (!CircuitPlayground.rightButton())
    {
        return false;
    }
    delay(1000);
    return CircuitPlayground.rightButton();
}

void calibrateDarkThreshold(int *darkThreshold)
{
    *darkThreshold = CircuitPlayground.lightSensor();
    Serial.print("Dark threshold set to: ");
    Serial.println(*darkThreshold);
    const int size = 5;
    int neos[] = {0, 1, 2, 3, 4};
    blinkNeosThrice(neos, size, WHITE_HEX);
}

void calibrateLightThreshold(int *lightThreshold)
{
    *lightThreshold = CircuitPlayground.lightSensor();
    Serial.print("Light threshold set to: ");
    Serial.println(*lightThreshold);
    const int size = 5;
    int neos[] = {5, 6, 7, 8, 9};
    blinkNeosThrice(neos, size, WHITE_HEX);
}

void blinkNeosThrice(int neos[], int size, int hex)
{
    for (int timesBlinked = 0; timesBlinked < 3; timesBlinked++)
    {
        for (int neoIndex = 0; neoIndex < size; neoIndex++)
        {
            CircuitPlayground.setPixelColor(neos[neoIndex], hex);
        }
        delay(BLINK_DELAY);
        CircuitPlayground.clearPixels();
        delay(BLINK_DELAY);
    }
}

void blinkRainbow()
{
    const int size = 10;
    for (int timesBlinked = 0; timesBlinked < 3; timesBlinked++)
    {
        for (int neoIndex = 0; neoIndex < size; neoIndex++)
        {
            CircuitPlayground.setPixelColor(neoIndex, getRainbowColor(neoIndex, size));
        }
        delay(BLINK_DELAY);
        CircuitPlayground.clearPixels();
        delay(BLINK_DELAY);
    }
}

void resetManualOverrideTimer(long *timerMillis)
{
    *timerMillis = 0L;
    Serial.println("Manual override timer reset.");
    blinkRainbow();
}

void calibrateManualOverrideTimer(long *timerMillis, bool isLongPress(void))
{
    Serial.println("Calibrating manual override timer...");
    const int size = 10;
    while (isLongPress())
    {
        int neoIndex = *timerMillis / MILLIS_PER_MIN % size;
        if (neoIndex == 0)
        {
            CircuitPlayground.clearPixels();
        }
        CircuitPlayground.setPixelColor(neoIndex, getRainbowColor(neoIndex, size));
        *timerMillis += MILLIS_PER_MIN;
    }
    delay(1000);
    CircuitPlayground.clearPixels();
    Serial.print("Calibrate manual override timer complete:　");
    Serial.print(*timerMillis / MILLIS_PER_MIN);
    Serial.println(" minutes.");
}

long getRainbowColor(int i, int size)
{
    return CircuitPlayground.colorWheel((i * 256 / size) & 255);
}