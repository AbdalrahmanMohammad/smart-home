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

void checkWifi() // checks wifi connection every 3 seconds and shows the condition on wifiLed
{
  if (millis() - wifiLed.previous >= 3000UL) // this uses the previous differently it uses it to repeat
  {                                          // with constant period. (it doesn't have a button, so this is fine)
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

void toggleled()// works when the led's pushbutton is pressed
{
  ledPin.onPushbuttonIsClicked();
}

void togglergb() // works when the rgb's pushbutton is pressed
{
    rgb.onPushbuttonIsClicked(); 
}

void ledTimer()
{
  ledPin.timer();
  rgb.timer();
}
