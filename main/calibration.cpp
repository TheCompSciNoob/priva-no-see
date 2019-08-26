#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"
#include "blinds.h"

#define MILLIS_PER_MIN 60000L
#define WHITE_HEX 0xffffff
#define BLINK_DELAY 150

bool isLongPressLeft();
bool isLongPressRight();
void blinkNeos(int neos[], int times, int size, int hex);
void blinkRainbow(int times);
void startTimerMode(struct BlindsState *state);
void startContinuousOverrideMode(struct BlindsState *state);
void calibrateDarkThreshold(struct BlindsState *state);
void calibrateLightThreshold(struct BlindsState *state);
void resetManualOverrideTimer(struct BlindsState *state);
void calibrateManualOverrideTimer(struct BlindsState *state, bool isLongPress(void));
long getRainbowColor(int i, int size);

//checks slide switch and button inputs for calibration
void calibrate(struct BlindsState *state)
{
    if (CircuitPlayground.slideSwitch()) //slide switch left
    {
        if (isLongPressLeft())
        {
            calibrateDarkThreshold(state);
            (*state).isContinuousOverrideOn = false;
        }
        if (isLongPressRight())
        {
            calibrateLightThreshold(state);
            (*state).isContinuousOverrideOn = false;
        }
    }
    else
    {
        if (isLongPressLeft())
        {
            (*state).isTimerOn = !(*state).isTimerOn;
            Serial.print("Timer mode set to: ");
            Serial.println((*state).isTimerOn);
            if ((*state).isTimerOn)
                startTimerMode(state);
            else
                startContinuousOverrideMode(state);
        }
        if (isLongPressRight())
        {
            if ((*state).isTimerOn)
            {
                resetManualOverrideTimer(state);
                calibrateManualOverrideTimer(state, isLongPressRight);
            }
            else //do not allow timer calibration if timer is off
            {
                const int size = 1;
                static int neos[] = {2};
                while (isLongPressRight())
                {
                    blinkNeos(neos, 3, size, WHITE_HEX);
                }
            }
        }
    }
}

//switches to timer mode and resets continuous override mode
void startTimerMode(struct BlindsState *state)
{
    (*state).isContinuousOverrideOn = false;
    //indicate timer mode with rainbow colors
    const int size = 10;
    for (int neoIndex = 0; neoIndex < size; neoIndex++)
        CircuitPlayground.setPixelColor(neoIndex, getRainbowColor(neoIndex, size));
    while (isLongPressLeft())
        ; //just wait
    CircuitPlayground.clearPixels();
}

//switches to continuous override mode and resets timer mode
void startContinuousOverrideMode(struct BlindsState *state)
{
    (*state).timerMillis = 0;
    //indicate continuous override mode with all white LEDs
    const int size = 10;
    for (int neoIndex = 0; neoIndex < size; neoIndex++)
        CircuitPlayground.setPixelColor(neoIndex, WHITE_HEX);
    while (isLongPressLeft())
        ; //just wait
    CircuitPlayground.clearPixels();
}

//detect for left button long press
bool isLongPressLeft()
{
    if (!CircuitPlayground.leftButton())
        return false;
    delay(1000);
    return CircuitPlayground.leftButton();
}

//detect for right button long press
bool isLongPressRight()
{
    if (!CircuitPlayground.rightButton())
        return false;
    delay(1000);
    return CircuitPlayground.rightButton();
}

//sets darkThreshold in BlindsState with button input
void calibrateDarkThreshold(struct BlindsState *state)
{
    (*state).darkThreshold = CircuitPlayground.lightSensor();
    Serial.print("Dark threshold set to: ");
    Serial.println((*state).darkThreshold);
    const int size = 5;
    int neos[] = {0, 1, 2, 3, 4};
    blinkNeos(neos, 3, size, WHITE_HEX);
}

//sets lightThreshold in BlindsState with button input
void calibrateLightThreshold(struct BlindsState *state)
{
    (*state).lightThreshold = CircuitPlayground.lightSensor();
    Serial.print("Light threshold set to: ");
    Serial.println((*state).lightThreshold);
    const int size = 5;
    int neos[] = {5, 6, 7, 8, 9};
    blinkNeos(neos, 3, size, WHITE_HEX);
}

//resets timer to 0
void resetManualOverrideTimer(struct BlindsState *state)
{
    (*state).timerMillis = 0L;
    Serial.println("Manual override timer reset.");
    blinkRainbow(2);
}

//calibrate timer with button input
void calibrateManualOverrideTimer(struct BlindsState *state, bool isLongPress(void))
{
    Serial.println("Calibrating manual override timer...");
    const int size = 10;
    while (isLongPress())
    {
        int neoIndex = (*state).timerMillis / MILLIS_PER_MIN % size;
        if (neoIndex == 0)
        {
            CircuitPlayground.clearPixels();
        }
        CircuitPlayground.setPixelColor(neoIndex, getRainbowColor(neoIndex, size));
        (*state).timerMillis += MILLIS_PER_MIN;
    }
    delay(1000);
    CircuitPlayground.clearPixels();
    Serial.print("Calibrate manual override timer complete:　");
    Serial.print((*state).timerMillis / MILLIS_PER_MIN);
    Serial.println(" minutes.");
}

void blinkNeos(int neos[], int times, int size, int hex)
{
    for (int timesBlinked = 0; timesBlinked < times; timesBlinked++)
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

void blinkRainbow(int times)
{
    const int size = 10;
    for (int timesBlinked = 0; timesBlinked < times; timesBlinked++)
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

long getRainbowColor(int i, int size)
{
    return CircuitPlayground.colorWheel((i * 256 / size) & 255);
}