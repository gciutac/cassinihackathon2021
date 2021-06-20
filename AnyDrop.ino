#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>
#define PIN D2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  Serial.begin(115200);                       // Serial connection
  pixels.begin();
  WiFi.begin("SSID", "XXXXXXXXXXXXXX");    // WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {     // Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
}
 
void loop() {
 int value = getCurrentState(analogRead(A0));
 updateRgbLed(value);
 updateApi(value);
 delay(1000);  //Send a request every second
}

int getCurrentState(int sensorValue)
{
  Serial.println(sensorValue);
  if(sensorValue >= 500){
    return 1; //Dirty water -> Turn On Red led
  }
  else if(sensorValue > 100 && sensorValue < 500) {
    return 2; //Clean water -> Turn On Green led
  }
  else {
    return 3; //Active State -> Blue Led
  }
}

void updateRgbLed(int value)
{
  if(value == 1){
    setColor(255,0,0,1000); //Dirty water -> Turn On Red led
  }
  else if(value == 2) {
    setColor(0,255,0,1000); //Clean water -> Turn On Green led
  }
  else {
    setColor(0,0,255,1000); //Active State -> Blue Led
  }
}

void updateApi(int value)
{
  if(WiFi.status()== WL_CONNECTED){
   WiFiClient wifiClient;
   HTTPClient http;    //Declare object of class HTTPClient
   http.begin(wifiClient, "http://5.189.160.203:8110/api/esp/name/RGB?type=RGB&title=Rgb" + buildApiRequest(value) );      //Specify request destination
   http.addHeader("x-device-token", "Vh7X5JSkoxRSsyf8fgur2jZwt-sIdIYp");  //Specify content-type header
   int httpCode = http.POST("{}");   //Send the request
   Serial.println(httpCode);   //Print HTTP return code
   http.end();  //Close connection
 }else{
    Serial.println("Error in WiFi connection");   
 }
}
String buildApiRequest(int value)
{
  if(value == 1){
    return "&val1=1&val2=0&val3=0"; //Dirty water -> Turn On Red led
  }
  else if(value == 2) {
    return "&val1=0&val2=1&val3=0"; //Clean water -> Turn On Green led
  }
  else {
    return "&val1=0&val2=0&val3=1"; //Active State -> Blue Led
  }
}
void setColor(int redValue, int greenValue, int blueValue, int delayValue)
{
  pixels.setPixelColor(0, pixels.Color(redValue, greenValue, blueValue)); 
  pixels.show();
  delay(delayValue);
}
