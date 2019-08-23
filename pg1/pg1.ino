#include <Adafruit_CircuitPlayground.h>

#define MAX_BRIGHT 1023
#define MIN_BRIGHT 0

static bool isClosed = false;
static int lightThreshold = MAX_BRIGHT;
static int darkThreshold = MIN_BRIGHT;

void setup()
{
    Serial.begin(9600);
    CircuitPlayground.begin();
}

void loop()
{
    //open or close blinds based on brightness
    int brightness = CircuitPlayground.lightSensor();
    Serial.print("Brightness: "); //log sensor
    Serial.println(brightness);
    if (brightness > (lightThreshold + darkThreshold) / 2) //theshold is average brightness
    {
        CircuitPlayground.redLED(true);
        openBlinds();
    }
    else
    {
        CircuitPlayground.redLED(false);
        closeBlinds();
    }

    //use buttons to calibrate brightness
    if (CircuitPlayground.leftButton())
    {
        calibrateDarkThreshold();
    }
    else if (CircuitPlayground.rightButton())
    {
        calibrateLightThreshold();
    }

    delay(1000); //runs every second
}

void calibrateDarkThreshold()
{
    darkThreshold = CircuitPlayground.lightSensor();
    Serial.print("Dark threshold set to: ");
    Serial.println(darkThreshold);
    blinkRedLedThrice();
}

void calibrateLightThreshold()
{
    lightThreshold = CircuitPlayground.lightSensor();
    Serial.print("Light threshold set to: ");
    Serial.println(lightThreshold);
    blinkRedLedThrice();
}

void openBlinds()
{
    if (!isClosed)
    {
        return;
    }
    isClosed = false;
    //TODO
}

void closeBlinds()
{
    if (isClosed)
    {
        return;
    }
    isClosed = true;
    //TODO
}

void toggleBlinds()
{
    if (isClosed)
    {
        openBlinds();
    }
    else
    {
        closeBlinds();
    }
}

void blinkRedLedThrice()
{
    CircuitPlayground.redLED(false);
    delay(1000);
    for (int i = 0; i < 3; i++)
    {
        CircuitPlayground.redLED(true);
        delay(200);
        CircuitPlayground.redLED(false);
        delay(200);
    }
}