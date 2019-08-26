#ifndef BLINDS_H
#define BLINDS_H

#define MAX_BRIGHT 1023
#define MIN_BRIGHT 0

struct BlindsState
{
    //timer mode
    bool isTimerOn;
    long lastOverrideMillis;
    long timerMillis;
    //continuous override mode
    bool isContinuousOverrideOn;
    bool lastLightState;
    //configuration
    bool isClosed;
    int lightThreshold;
    int darkThreshold;
};

void operateBlinds(struct BlindsState *state);

void overrideBlinds(struct BlindsState *state);

#endif