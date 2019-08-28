#ifndef CLAP_SENSOR_H
#define CLAP_SENSOR_H

struct ClapSensor
{
    int soundLevel;
    int timeMillis;
    void (*sensorCallback)();
};

void setupClapSensor(struct ClapSensor sensor, long allowSetupMillis);

void runClapSensor(struct ClapSensor sensor);

#endif