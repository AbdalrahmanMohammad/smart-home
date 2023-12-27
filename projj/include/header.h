#include <WiFi.h>
#include <LedClass.h>
#include <RGB.h>
#include <ROOM.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define pr(x) Serial.println(x)

// Set your network credentials
const char *ssid = "PL";
const char *password = "87654321";
String postData = "";
String payload = "";
boolean startEspException2 = true; // this will goes to every part of control_room2 that is necessary to read when starting up
                                  // and then in the end when it come out will be false
RGB rgb(5, 4, 8);
LedClass wifiLed(32);
LedClass ledPin(12, 17);
TV tv(2);
// RGB rgb(16, 23, 8);
// LedClass ledPin(21, 22);

DimUpCommand dimupcom(&rgb);
DimDownCommand dimdowncom(&rgb);
ChangeColorCommand chcolorcom(&rgb);
TurnOnCommand ledoncom(&ledPin);
TurnOnCommand rgboncom(&rgb);
Command *commands[] = {&ledoncom, &rgboncom};
MacroCommand onboth(commands, 2);
SendIRCommand presstvbtncmd(&tv);

ROOM room1;
ROOM room2;
ROOM room3;
