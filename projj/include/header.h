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
RGB room2rgb(5, 4, 8);
LedClass wifiLed(32);
LedClass room3led(12, 17);
TV room3tv(2);
RGB room1rgb(16, 23, 8);
LedClass room2led(21, 22);

DimUpCommand room2dimupcom(&room2rgb);
DimDownCommand room2dimdowncom(&room2rgb);
ChangeColorCommand room2chcolorcom(&room2rgb);
TurnOnCommand room2rgboncom(&room2rgb);
/////////////////////////////////////////////
DimUpCommand room1dimupcom(&room1rgb);
DimDownCommand room1dimdowncom(&room1rgb);
ChangeColorCommand room1chcolorcom(&room1rgb);
TurnOnCommand room1rgboncom(&room1rgb);
/////////////////////////////////////////////
TurnOnCommand room3ledoncom(&room3led);
TurnOnCommand room2ledoncom(&room2led);
// Command *commands[] = {&ledoncom, &rgboncom};
// MacroCommand onboth(commands, 2);
SendIRCommand room3presstvbtncmd(&room3tv);

ROOM room1;
ROOM room2;
ROOM room3;
