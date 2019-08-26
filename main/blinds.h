#ifndef BLINDS_H
#define BLINDS_H

#define MAX_BRIGHT 1023
#define MIN_BRIGHT 0

struct BlindsState
{
    bool isTimerOn;
    long lastOverrideMillis;
    long timerMillis;
    bool isContinuousOverrideOn;
    bool lastLightState;
    bool isClosed;
    int lightThreshold;
    int darkThreshold;
};

void setupBlinds();

void operateBlinds();

void overrideBlinds();

struct BlindsState *getBlindsState();

#endif