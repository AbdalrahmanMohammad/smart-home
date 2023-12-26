#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  room1.setLed(&ledPin, &ledoncom);
    // room1.setOnBoth(&onboth);
  room2.setRgb(&rgb, &dimupcom, &dimdowncom, &chcolorcom);
  room3.setTV(&tv, &presstvbtncmd);

  wifiLed.init(LOW);
  room1.init();
  room2.init();
  room3.init();

  wificonnection();

}



void loop()
{
    if (Serial.available() > 0)
  {
    String userInput = Serial.readString();

    room3.excTvButton(userInput);
  }

  getdata();
  ///////////////////////////////////////////////////////////////////////
  togglergb(); // toggles the rgb led using the button
  toggleled(); // toggles the led using the button
  checkWifi();
  room1.timers();
  room2.timers();
  room3.timers();
  //////////////////////////////////////////////////
  senddata();
}