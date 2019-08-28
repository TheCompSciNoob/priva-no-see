#ifndef CLAP_SENSOR_H
#define CLAP_SENSOR_H

struct ClapSensor
{
    int soundLevel;
    int timeMillis;
    void (*sensorCallback)();
};

void runClapSensor(ClapSensor sensor);

#endif