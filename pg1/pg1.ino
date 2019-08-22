#include <Adafruit_CircuitPlayground.h>

void testSensors();

static void setup() {
    Serial.begin(9600);
    CircuitPlayground.begin();
}

static void loop() {
    //stop program by sending in 'q'
    static bool done = false;
    char input = Serial.read();
    if (input == 'q') {
        done = true;
    }

    //continue to run if 'q' is not entered
    if(!done) {
        testSensors();
    }
}

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