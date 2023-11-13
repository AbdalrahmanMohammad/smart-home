#include "../include/header.h"
#include "handlersFunctions.h"

void wificonnection()
{ // it tries to connected to wifi for 6 seconds after this it will contiune wihtout connection
  if (WiFi.status() != WL_CONNECTED)
  {
    delay(3000);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi...");
    delay(3000);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connected to WiFi");

    Serial.print("ESP32 IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.print("we will continue without connection");
  }
}

void checkWifi()// checks wifi connection every 3 seconds and shows the condition on wifiLed
{
  if (millis() - wifiLed.previous >= 3000UL)// this uses the previous differently it uses it to repeat
  {                                         // with constant period. (it doesn't have a button, so this is fine)
    if (WiFi.status() == WL_CONNECTED)
    {
      wifiLed.on();
    }
    else
    {
      wifiLed.off();
    }

    // Serial.println(WiFi.status());

    wifiLed.previous = millis();
  }
}

void toggleled()
{
  if (millis() - ledPin.previous >= 300UL)
  {
    ledPin.toggle();
    ledPin.previous = millis();
  }
}

void togglergb() // to toggle the rgb from a button
{

  rgb.btncurstate = rgb.btnstate();

  if (rgb.btncurstate == LOW && rgb.btnprevstate == HIGH)
  {
    if (millis() - rgb.previous >= 500UL)
    {
      rgb.toggle();
      rgb.previous = millis();
    }
  }
  rgb.btnprevstate = rgb.btncurstate;
}

void ledTimer()
{
  if (ledPin.duration > 0 && (millis() - ledPin.startTime >= ledPin.duration))
  {
    ledPin.toggle();
    ledPin.duration = 0; // Reset the delay
  }

  if (rgb.duration > 0 && (millis() - rgb.startTime >= rgb.duration))
  {
    rgb.toggle();
    rgb.duration = 0; // Reset the delay
  }
}
