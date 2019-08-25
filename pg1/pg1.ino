#include <Adafruit_CircuitPlayground.h>

#define MAX_BRIGHT 1023
#define MIN_BRIGHT 0
#define MILLIS_PER_MIN 60000
#define LEFT_NEOS 1001
#define RIGHT_NEOS 1002
#define YELLOW_R 255
#define YELLOW_G 255
#define YELLOW_B 0

//control blinds
static bool isClosed = false;
static int lightThreshold = MAX_BRIGHT;
static int darkThreshold = MIN_BRIGHT;

//manual override with clapping
static long baseTime = 0;
static int manualOverrideMillis = 0;

_Bool isLongPressLeft();
_Bool isLongPressRight();

void setup()
{
    CircuitPlayground.begin();
    Serial.begin(9600);
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

    //check for calibration inputs
    checkForCalibration();

    //run every second
    delay(1000);
}

void checkForCalibration()
{
    if (CircuitPlayground.slideSwitch()) //slide switch left
    {
        if (isLongPressLeft())
        {
            calibrateDarkThreshold();
        }
        if (isLongPressRight())
        {
            calibrateLightThreshold();
        }
    }
    else
    {
        if (isLongPressLeft())
        {
            //TODO
        }
        if (isLongPressRight())
        {
            //TODO
        }
    }
}

_Bool isLongPressLeft()
{
    if (!CircuitPlayground.leftButton())
    {
        return false;
    }
    delay(1000);
    return CircuitPlayground.leftButton();
}

_Bool isLongPressRight()
{
    if (!CircuitPlayground.rightButton())
    {
        return false;
    }
    delay(1000);
    return CircuitPlayground.rightButton();
}

void calibrateDarkThreshold()
{
    darkThreshold = CircuitPlayground.lightSensor();
    Serial.print("Dark threshold set to: ");
    Serial.println(darkThreshold);
    blinkNeos(LEFT_NEOS, YELLOW_R, YELLOW_G, YELLOW_B);
}

void calibrateLightThreshold()
{
    lightThreshold = CircuitPlayground.lightSensor();
    Serial.print("Light threshold set to: ");
    Serial.println(lightThreshold);
    blinkNeos(RIGHT_NEOS, YELLOW_R, YELLOW_G, YELLOW_B);
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

void blinkNeos(int side, int red, int green, int blue)
{
    //neos to blink
    int NUM_NEOS = 5;
    if (side == LEFT_NEOS)
    {
        int neosLeft[] = {0, 1, 2, 3, 4};
        blinkNeosThrice(neosLeft, NUM_NEOS, red, green, blue);
    }
    else if (side == RIGHT_NEOS)
    {
        int neosRight[] = {5, 6, 7, 8, 9};
        blinkNeosThrice(neosRight, NUM_NEOS, red, green, blue);
    }
    else
    {
        Serial.println("Invalid side argument for NEOs.");
    }
}

void blinkNeosThrice(int neos[], int size, int red, int green, int blue)
{
    for (int timesBlinked = 0; timesBlinked < 3; timesBlinked++)
    {
        for (int neoIndex = 0; neoIndex < size; neoIndex++)
        {
            CircuitPlayground.setPixelColor(neos[neoIndex], red, green, blue);
        }
        delay(100);
        CircuitPlayground.clearPixels();
        delay(100);
    }
}