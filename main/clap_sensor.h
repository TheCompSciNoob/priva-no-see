#ifndef CLAP_SENSOR_H
#define CLAP_SENSOR_H

struct ClapSensor
{
    long sensorMillis;
    long detectMillisStart;
    long detectMillisEnd;
    float loudDifference;
    void (*sensorCallback)();
};

void setupClapSensor(struct ClapSensor sensor, long allowSetupMillis);

void runClapSensor(struct ClapSensor sensor);

#endif