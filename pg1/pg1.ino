#include <Adafruit_CircuitPlayground.h>

void testSensors();

static void setup() {
    Serial.begin(9600);
    CircuitPlayground.begin();
}

static void loop() {
    clapSensor();
}



void clapSensor()
{
  float value = CircuitPlayground.mic.soundPressureLevel(10);
  
  Serial.print("Sound Sensor SPL: ");
  Serial.println(value);
  
  
  if (value >= 68)
  {
       CircuitPlayground.redLED(HIGH);
       delay(50);
       CircuitPlayground.redLED(LOW);
       delay(50);
  }
  

 // Serial.print("Sound Sensor SPL: ");
 // Serial.println(value2);

  delay(90);

}


