#include <Adafruit_CircuitPlayground.h>
#include "blinds.h"

void operateBlinds(struct BlindsState *state);
void operateTimerMode(struct BlindsState *state);
void operateContinuousOverrideMode(struct BlindsState *state);
void defaultOperateBlinds(struct BlindsState *state);
void forceToggleBlinds(struct BlindsState *state);
void openBlinds(struct BlindsState *state);
void closeBlinds(struct BlindsState *state);
void continuousOverrideBlinds(struct BlindsState *state);
void timerOverrideBlinds(struct BlindsState *state);
void overrideBlinds(struct BlindsState *state);
bool isBright(struct BlindsState *state);

void operateBlinds(struct BlindsState *state)
{
    if ((*state).isTimerOn)
        operateTimerMode(state);
    else
        operateContinuousOverrideMode(state);
}

void operateTimerMode(struct BlindsState *state)
{
    if (millis() - (*state).lastOverrideMillis > (*state).timerMillis)
        defaultOperateBlinds(state); //stop override when time is up
}

void operateContinuousOverrideMode(struct BlindsState *state)
{
    if ((*state).lastLightState != isBright(state)) //change in light state
    {
        (*state).lastLightState = !(*state).lastLightState;
        (*state).isContinuousOverrideOn = false;
    }
    if (!(*state).isContinuousOverrideOn)
    {
        defaultOperateBlinds(state);
    }
}

void defaultOperateBlinds(struct BlindsState *state)
{
    if (isBright(state))
        openBlinds(state);
    else
        closeBlinds(state);
}

void forceToggleBlinds(struct BlindsState *state)
{
    if ((*state).isClosed)
        openBlinds(state);
    else
        closeBlinds(state);
}

void openBlinds(struct BlindsState *state)
{
    CircuitPlayground.redLED(true);
    if (!(*state).isClosed)
        return;
    (*state).isClosed = false;
    //TODO
}

void closeBlinds(struct BlindsState *state)
{
    CircuitPlayground.redLED(false);
    if ((*state).isClosed)
        return;
    (*state).isClosed = true;
    //TODO
}

void continuousOverrideBlinds(struct BlindsState *state)
{
    (*state).isContinuousOverrideOn = true;
    forceToggleBlinds(state);
}

void timerOverrideBlinds(struct BlindsState *state)
{
    (*state).lastOverrideMillis = millis();
    forceToggleBlinds(state);
}

void overrideBlinds(struct BlindsState *state)
{
    if ((*state).isTimerOn)
        timerOverrideBlinds(state);
    else
        continuousOverrideBlinds(state);
}

bool isBright(struct BlindsState *state)
{
    return CircuitPlayground.lightSensor() > ((*state).lightThreshold + (*state).darkThreshold) / 2;
}