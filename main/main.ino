#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"
#include "blinds.h"
#include "motor.h"
#include "clap_sensor.h"

#define MOTOR_CW1 A10
#define MOTOR_CW2 A9
#define MOTOR_CCW1 A7
#define MOTOR_CCW2 A11

//motor info
static struct Motor motor = {
    .pinCw1 = MOTOR_CW1,
    .pinCw2 = MOTOR_CW2,
    .pinCcw1 = MOTOR_CCW1,
    .pinCcw2 = MOTOR_CCW2};

//create blinds state
static struct BlindsState state = {
    .isTimerOn = false,
    .lastOverrideMillis = 0L,
    .timerMillis = 0L,
    .isContinuousOverrideOn = false,
    .lastLightState = true,
    .isClosed = true,
    .lightThreshold = MAX_BRIGHT,
    .darkThreshold = MIN_BRIGHT,
    .openCallback = []() { motorOpenBlinds(motor); },
    .closeCallback = []() { motorCloseBlinds(motor); }};

//clap sensor info
static struct ClapSensor clapSensor = {
    .soundLevel = 90,
    .soundPressureLevel = 10,
    .sensorCallback = []() { overrideBlinds(&state); }};

void setup()
{
    CircuitPlayground.begin();
    Serial.begin(9600);

    //set up motor pins
    pinMode(MOTOR_CW1, OUTPUT);
    pinMode(MOTOR_CW2, OUTPUT);
    pinMode(MOTOR_CCW1, OUTPUT);
    pinMode(MOTOR_CCW2, OUTPUT);
}

void loop()
{
    //log light sensor
    Serial.print("Brightness: "); //log sensor
    Serial.println(CircuitPlayground.lightSensor());

    //calibrates blinds state properties
    calibrate(&state);

    //controller
    operateBlinds(&state);

    //detect claps
    runClapSensor(clapSensor);

    //check computer inputs for debugging
    processSerialInputs(&state);

    //run every 50 milliseconds
    delay(50);
}

//send inputs from computer
void processSerialInputs(struct BlindsState *state)
{
    char input = Serial.read();
    if (input == 'o')
        overrideBlinds(state);
}