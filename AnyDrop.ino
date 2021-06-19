#include <Adafruit_NeoPixel.h>
#define PIN D2
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin();
}

void loop() {
  // Read water resistance value and trigger action
  triggerAction(analogRead(A0));
}

void triggerAction(int sensorValue)
{
  Serial.println(sensorValue);
  if(sensorValue >= 500){
    setColor(255,0,0,1000); //Dirty water -> Turn On Red led
  }
  else if(sensorValue > 100 && sensorValue < 500) {
    setColor(0,255,0,1000); //Clean water -> Turn On Green led
  }
  else {
    setColor(0,0,255,1000); //Active State -> Blue Led
  }
}

void setColor(int redValue, int greenValue, int blueValue, int delayValue)
{
  pixels.setPixelColor(0, pixels.Color(redValue, greenValue, blueValue)); 
  pixels.show();
  delay(delayValue);
}
