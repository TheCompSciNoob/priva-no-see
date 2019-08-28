#include <Adafruit_CircuitPlayground.h>
#include <math.h>
#include "clap_sensor.h"

#define N_SAMPLES 50
#define MIN_INTERVAL 50 //minimum interval between collecting samples is 50 milliseconds
#define GREEN_HEX 0x00ff00

void setupClapSensor(struct ClapSensor sensor, long allowSetupMillis);
void runClapSensor(struct ClapSensor sensor);
float averageSoundLevel();

static int sampleCount = 0;
static float soundLevels[N_SAMPLES];

void setupClapSensor(struct ClapSensor sensor, long allowSetupMillis)
{
    long intervalMillis = (long) fmax(MIN_INTERVAL, allowSetupMillis / N_SAMPLES);
    long nInitialSamples = allowSetupMillis / intervalMillis;
    const int neosSize = 10;
    Serial.println(nInitialSamples);
    for (sampleCount = 0; sampleCount < nInitialSamples; sampleCount++)
    {
        //progress indicator
        int progressNeo = (int) (neosSize * sampleCount / nInitialSamples);
        CircuitPlayground.setPixelColor(progressNeo, GREEN_HEX);
        //add sample to array
        float soundLevel = CircuitPlayground.mic.soundPressureLevel(sensor.timeMillis);
        soundLevels[sampleCount] = soundLevel;
        delay(intervalMillis);
    }
    CircuitPlayground.clearPixels();
}

void runClapSensor(struct ClapSensor sensor)
{
    float soundLevel = CircuitPlayground.mic.soundPressureLevel(sensor.timeMillis);

    Serial.print("Sound Sensor SPL: ");
    Serial.println(soundLevel);

    if (soundLevel >= sensor.soundLevel)
    {
        sensor.sensorCallback();
    }
}

float averageSoundLevel()
{
    float sum = 0;
    int nValidSamples = (int) fmin(sampleCount, N_SAMPLES);
    for (int i = 0; i < nValidSamples; i++)
    {
        sum += soundLevels[i];
    }
    return sum / nValidSamples;
}