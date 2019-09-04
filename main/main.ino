#include <Adafruit_CircuitPlayground.h>
#include "calibration.h"
#include "blinds.h"
#include "motor.h"
#include "clap_sensor.h"

void setup()
{
    CircuitPlayground.begin();
    Serial.begin(9600);

    //set up motor (pins)
    setupMotor(getMotorInfo());

    //set up clap sensor (per-record sounds)
    setupClapSensor(getClapSensorInfo(), 10000); //10 seconds
}

void loop()
{
    //log light sensor
    Serial.print("Brightness: "); //log sensor
    Serial.println(CircuitPlayground.lightSensor());

    //calibrates blinds state properties
    calibrate(getBlindsState());

    //controller
    operateBlinds(getBlindsState());

    //detect claps
    runClapSensor(getClapSensorInfo());

    //check computer inputs for debugging
    processSerialInputs(getBlindsState());

    //run every 30 milliseconds
    delay(30);
}

struct BlindsState *getBlindsState()
{
    static struct BlindsState state = {
        .isTimerOn = false,
        .lastOverrideMillis = 0L,
        .timerMillis = 0L,
        .isContinuousOverrideOn = false,
        .lastLightState = true,
        .isClosed = true,
        .lightThreshold = MAX_BRIGHT,
        .darkThreshold = MIN_BRIGHT,
        .openCallback = []() { motorOpenBlinds(getMotorInfo()); },
        .closeCallback = []() { motorCloseBlinds(getMotorInfo()); }};
    return &state;
}

struct Motor *getMotorInfo()
{
    static struct Motor motor = {
        .pin1 = A11,
        .pin2 = A7,
        .pin3 = A9,
        .pin4 = A10,
        .delay = 1,
        .stepsCw = 200000, //open
        .stepsCcw = 200000}; //close
    return &motor;
}

struct ClapSensor *getClapSensorInfo()
{
    static struct ClapSensor clapSensor = {
        .sensorMillis = 10,
        .detectMillisStart = 200,
        .detectMillisEnd = 500,
        .minimumLevel = 75.0,
        .sensorCallback = []() { overrideBlinds(getBlindsState()); }};
    return &clapSensor;
}

//send inputs from computer
void processSerialInputs(struct BlindsState *state)
{
    char input = Serial.read();
    if (input == 'o')
        overrideBlinds(state);
}