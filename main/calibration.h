#ifndef CALIBRATION_H
#define CALIBRATION_H

static const int OVERRIDE_NONE = 0;
static const int OVERRIDE_LIGHT = 1;
static const int OVERRIDE_DARK = 2;

void calibrate(
    int *darkThreshold,
    int *lightThreshold,
    bool isBright(void),
    bool *isTimerOn,
    int *manualOverrideMode,
    long *timerMillis);

#endif
