#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  room1.setLed(&ledPin, &ledoncom);
  room2.setRgb(&rgb, &dimupcom, &dimdowncom, &chcolorcom);
  // room1.setOnBoth(&onboth);
  // room1.setTV(&tv, &presstvbtncmd);

  wifiLed.init(LOW);
  room1.init();
  room2.init();

  wificonnection();

}



void loop()
{
  if (Serial.available() > 0)
  {
    String userInput = Serial.readString();
    if(userInput=="1")
    room1.excDimUp();
        if(userInput=="0")
    room1.excDimDown();

  }

  getdata();
  ///////////////////////////////////////////////////////////////////////
  togglergb(); // toggles the rgb led using the button
  toggleled(); // toggles the led using the button
  checkWifi();
  room1.timers();
  room2.timers();
  //////////////////////////////////////////////////
  senddata();
}