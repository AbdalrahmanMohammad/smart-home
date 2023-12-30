#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  dht.begin();
  smk.init();
  myStepper.setSpeed(10);

  // room1.setOnBoth(&onboth);
  room1.setRgb(&room1rgb, &room1dimupcom, &room1dimdowncom, &room1chcolorcom);
  room2.setRgb(&room2rgb, &room2dimupcom, &room2dimdowncom, &room2chcolorcom);
  room2.setLed(&room2led, &room2ledoncom);
  room3.setTV(&room3tv, &room3presstvbtncmd);
  room3.setLed(&room3led, &room3ledoncom);

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

    if (userInput == "1")
      myStepper.step(512);
    if (userInput == "0")
      myStepper.step(-512);
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