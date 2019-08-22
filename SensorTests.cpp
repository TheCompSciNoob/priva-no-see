#include <Adafruit_CircuitPlayground.h>

void printSoundLevel()
{
    float value = CircuitPlayground.mic.soundPressureLevel(10);
    Serial.print("Sound Sensor SPL: ");
    Serial.println(value);
}

void printTemperature()
{
    float tempC = CircuitPlayground.temperature();
    float tempF = CircuitPlayground.temperatureF();
    Serial.print(tempC);
    Serial.print(" ; ");
    Serial.println(tempF);
}

void blinkRedLed()
{
    CircuitPlayground.redLED(true);
    delay(200);
    CircuitPlayground.redLED(false);
    delay(200);
    CircuitPlayground.redLED(true);
    delay(200);
    CircuitPlayground.redLED(false);
    delay(1000);
}

void testSensors() {
    blinkRedLed();
    printTemperature();
    printSoundLevel();
}