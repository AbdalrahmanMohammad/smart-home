#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  // if (!SPIFFS.begin(true))
  // {
  //   Serial.println("An Error has occurred while mounting SPIFFS");
  //   return;
  // }

  room1.setLed(&ledPin, &ledoncom);
  // room1.setRgb(&rgb, &dimupcom, &dimdowncom, &chcolorcom);
  // room1.setOnBoth(&onboth);
  // room1.setTV(&tv, &presstvbtncmd);

  wifiLed.init(LOW);
  room1.init();

  wificonnection();
}



void loop()
{
  if (Serial.available() > 0)
  {
    String userInput = Serial.readString();
  }

  getdata();
  ///////////////////////////////////////////////////////////////////////
  togglergb(); // toggles the rgb led using the button
  toggleled(); // toggles the led using the button
  checkWifi();
  room1.timers();
  //////////////////////////////////////////////////
  senddata();
}