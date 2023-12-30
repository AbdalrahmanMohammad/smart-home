#include <WiFi.h>
#include <LedClass.h>
#include "DHT.h"
#include "Timer.h"
#include "SmokeSensor.h"
#include <RGB.h>
#include <ROOM.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define pr(x) Serial.println(x)
/// dht sensor ////////////////
DHT dht(13, DHT11);
Timer dhtTimer(20UL);
/// smoke Sensor //////////////// 
SmokeSensor smk(34, 25);


// Set your network credentials
const char *ssid = "PL";
const char *password = "87654321";
String postData = "";
String payload = "";
RGB room2rgb(5, 4, 8, RMT_CHANNEL_0);
LedClass wifiLed(14);
LedClass room3led(12, 17);
TV room3tv(2);
RGB room1rgb(15, 23, 8, RMT_CHANNEL_1);
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
