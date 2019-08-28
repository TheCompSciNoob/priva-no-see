#include <Adafruit_CircuitPlayground.h>
#include "clap_sensor.h"

void runClapSensor(struct ClapSensor sensor)
{
    float value = CircuitPlayground.mic.soundPressureLevel(sensor.soundPressureLevel);

    Serial.print("Sound Sensor SPL: ");
    Serial.println(value);

    if (value >= sensor.soundLevel)
    {
        sensor.sensorCallback();
    }
}