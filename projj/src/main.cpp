#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  room1.setLed(&ledPin, &ledtogcom);
  room1.setRgb(&rgb, &dimupcom, &dimdowncom, &chcolorcom);
  room1.setOnBoth(&onboth);

  wifiLed.init(LOW);
  room1.init(LOW);

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
  togglergb(); // toggles the rgb led using the button

  if (Serial.available() > 0)
  {
    // If there is data available to read
    int userInput = Serial.parseInt(); // Read the integer from Serial input

    if (userInput == 6)
    {
      room1.excOnBoth();
    }
    else if (userInput ==7)
    {
      room1.excOffBoth();
    }
    else
    {
      Serial.println("You didn't enter 6");
    }
  }
}