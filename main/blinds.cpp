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

//blinds controller decides what mode to operate in
//determines if the blinds should open/close based on the BlindsState
void operateBlinds(struct BlindsState *state)
{
    if ((*state).isTimerOn)
        operateTimerMode(state);
    else
        operateContinuousOverrideMode(state);
}

//blinds controller in timer mode
void operateTimerMode(struct BlindsState *state)
{
    if (millis() - (*state).lastOverrideMillis > (*state).timerMillis)
        defaultOperateBlinds(state); //stop override when time is up
}

//blinds controller in continuous override mode
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

//open or close blinds based on brightness (default behavior)
void defaultOperateBlinds(struct BlindsState *state)
{
    if (isBright(state))
        openBlinds(state);
    else
        closeBlinds(state);
}

//force open or close blinds (overrides default behavior)
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

//override blinds in continuous override mode
void continuousOverrideBlinds(struct BlindsState *state)
{
    Serial.println("Start continuous override blinds.");
    (*state).isContinuousOverrideOn = true;
    forceToggleBlinds(state);
}

//override blinds in timer mode
void timerOverrideBlinds(struct BlindsState *state)
{
    Serial.println("Start timer override blinds.");
    (*state).lastOverrideMillis = millis();
    forceToggleBlinds(state);
}

//override blinds based on the current mode
void overrideBlinds(struct BlindsState *state)
{
    if ((*state).isTimerOn)
        timerOverrideBlinds(state);
    else
        continuousOverrideBlinds(state);
}

//determines whether it is light or dark
bool isBright(struct BlindsState *state)
{
    return CircuitPlayground.lightSensor() > ((*state).lightThreshold + (*state).darkThreshold) / 2;
}