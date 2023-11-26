#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  wifiLed.init(LOW);
  room1.init(LOW);
  room2.init(LOW);/// @brief ////////////////////////////////  just to show you how it works ( delete it in the next push)

  attachInterrupt(digitalPinToInterrupt(ledPin.btn()), toggleled, FALLING);

  // Connect to Wi-Fi with static IP
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  wificonnection();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/rgbx", HTTP_GET, handlergbx);
  server.on("/ledstate", HTTP_GET, handleLEDState);

  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  server.begin();

}

void loop()
{
  checkWifi();
  room1.timers(); 
  room2.timers();/// @brief ////////////////////////////////  just to show you how it works ( delete it in the next push)
  togglergb(); // toggles the rgb led using the button
}
