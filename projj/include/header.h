#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <LedClass.h>
#include <RGB.h>
#include <ROOM.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define pr(x) Serial.println(x)

// Set your network credentials
const char *ssid = "PL";
const char *password = "87654321";


RGB rgb(5, 4, 8);
LedClass wifiLed(32);
LedClass ledPin(12, 17);
TV tv(0, 2);

DimUpCommand dimupcom(&rgb);
DimDownCommand dimdowncom(&rgb);
ChangeColorCommand chcolorcom(&rgb);
TurnOnCommand ledoncom(&ledPin);
TurnOnCommand rgboncom(&rgb);
Command *commands[] = {&ledoncom, &rgboncom};
MacroCommand onboth(commands, 2);
PressTvButton presstvbtncmd(&tv);

ROOM room1;
