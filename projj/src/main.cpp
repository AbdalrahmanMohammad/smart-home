#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

    // room1.setOnBoth(&onboth);
  room2.setRgb(&room2rgb, &room2dimupcom, &room2dimdowncom, &room2chcolorcom);
  room2.setLed(&room2led,&room2ledoncom);
  room3.setTV(&room3tv, &room3presstvbtncmd);
  room3.setLed(&room1led, &room1ledoncom);

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
  room1toggles(); // toggles the rgb led using the button
  room2toggles(); // toggles the led using the button
  room3toggles();
  checkWifi();
  room1.timers();
  room2.timers();
  room3.timers();
  //////////////////////////////////////////////////
  senddata();
}