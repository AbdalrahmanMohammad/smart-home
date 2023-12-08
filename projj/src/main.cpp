#include "header.h"
#include <functions.h>

void setup()
{
  Serial.begin(9600);

  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  room1.setLed(&ledPin, &ledtogcom);
  room1.setRgb(&rgb, &dimupcom, &dimdowncom, &chcolorcom);
  room1.setOnBoth(&onboth);

  wifiLed.init(LOW);
  room1.init();

  // Connect to Wi-Fi with static IP
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  wificonnection();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/rgbx", HTTP_GET, handlergbx);
  server.on("/ledstate", HTTP_GET, handleLEDState);

  server.begin();
}

void loop()
{
  checkWifi();
  room1.timers();
  togglergb(); // toggles the rgb led using the button
  toggleled(); // toggles the led using the button


  if (Serial.available() > 0)
  {
    int userInput = Serial.parseInt(); 

    switch (userInput)
    {
    case 0:
      irsend.sendNECMSB(0x40BF22DD, 32);
      Serial.println("kkkkk");
      break;

    case 1:
      irsend.sendNECMSB(0x40BF48B7, 32);
            Serial.println("111");
      break;

    case 2:
      irsend.sendNECMSB(0x40BF6897, 32);
      break;

    case 3:
      irsend.sendNECMSB(0x40BF40BF, 32);
      break;

    case 4:
      irsend.sendNECMSB(0x40BF58A7, 32);
      break;

    case 5:
      irsend.sendNECMSB(0x40BF7887, 32);
      break;

    case 6:
      irsend.sendNECMSB(0x40BFC03F, 32);
      break;

    case 7:
      irsend.sendNECMSB(0x40BFF00F, 32);
      break;

    case 8:
      irsend.sendNECMSB(0x40BFD02F, 32);
      break;

    case 9:
      irsend.sendNECMSB(0x40BFE01F, 32);
      break;

    case 111: // on
      irsend.sendNECMSB(0x40BF708F, 32);
      break;

    case 555: // voice
      irsend.sendNECMSB(0x40BF8A75, 32);
      break;

    case 88: // up
      irsend.sendNECMSB(0x40BF827D, 32);
      break;

    case 22: // down
      irsend.sendNECMSB(0x40BFA25D, 32);
      break;

    default:
      break;
    }
  }

}