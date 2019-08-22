#include <Adafruit_CircuitPlayground.h>
#include <SensorTests.h>

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