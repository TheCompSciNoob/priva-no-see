#include <Adafruit_CircuitPlayground.h>
#include "blinds.h"

void setupBlinds();
void operateBlinds();
void operateTimerMode();
void operateContinuousOverrideMode();
void defaultOperateBlinds();
void forceToggleBlinds();
void openBlinds();
void closeBlinds();
void continuousOverrideBlinds();
void timerOverrideBlinds();
void overrideBlinds();
bool isBright();

struct BlindsState state = {
    .isTimerOn = false,
    .lastOverrideMillis = 0L,
    .timerMillis = 0L,
    .isContinuousOverrideOn = false,
    .lastLightState = true,
    .isClosed = false,
    .lightThreshold = MAX_BRIGHT,
    .darkThreshold = MIN_BRIGHT};

struct BlindsState *getBlindsState()
{
    return &state;
}

void operateBlinds()
{
    if (state.isTimerOn)
        operateTimerMode();
    else
        operateContinuousOverrideMode();
}

void operateTimerMode()
{
    if (millis() - state.lastOverrideMillis > state.timerMillis)
        defaultOperateBlinds(); //stop override when time is up
}

void operateContinuousOverrideMode()
{
    if (state.lastLightState != isBright()) //change in light state
    {
        state.lastLightState = !state.lastLightState;
        state.isContinuousOverrideOn = false;
    }
    if (!state.isContinuousOverrideOn)
    {
        defaultOperateBlinds();
    }
}

void defaultOperateBlinds()
{
    if (isBright())
        openBlinds();
    else
        closeBlinds();
}

void forceToggleBlinds()
{
    if (state.isClosed)
        openBlinds();
    else
        closeBlinds();
}

void openBlinds()
{
    CircuitPlayground.redLED(true);
    if (!state.isClosed)
        return;
    state.isClosed = false;
    //TODO
}

void closeBlinds()
{
    CircuitPlayground.redLED(false);
    if (state.isClosed)
        return;
    state.isClosed = true;
    //TODO
}

void continuousOverrideBlinds()
{
    state.isContinuousOverrideOn = true;
    forceToggleBlinds();
}

void timerOverrideBlinds()
{
    state.lastOverrideMillis = millis();
    forceToggleBlinds();
}

void overrideBlinds()
{
    if (state.isTimerOn)
        timerOverrideBlinds();
    else
        continuousOverrideBlinds();
}

bool isBright()
{
    return CircuitPlayground.lightSensor() > (state.lightThreshold + state.darkThreshold) / 2;
}