#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  room1.setLed(&room1led, &room1ledoncom);
    // room1.setOnBoth(&onboth);
  room2.setRgb(&room2rgb, &room2dimupcom, &room2dimdowncom, &room2chcolorcom);
  room3.setTV(&room3tv, &room3presstvbtncmd);

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