#include <WiFi.h>
#include <LedClass.h>
#include "DHT.h"
#include "Timer.h"
#include <Stepper.h>
#include "SmokeSensor.h"
#include <LiquidCrystal.h>
#include <RGB.h>
#include <ROOM.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define pr(x) Serial.println(x)
/// dht sensor ////////////////
DHT dht(33, DHT11);
Timer dhtTimer(20UL);
/// smoke Sensor ////////////////
SmokeSensor smk(36, 19);
/// door motor ////////////////
Stepper myStepper(2048, 27, 25, 26, 21);
/// lcd ////////////////
LiquidCrystal lcd(15, 4, 16, 17, 5, 0);
Timer lcdTimer(3UL);
Timer connectionTimer(3UL);

int inhancer = 0;

// Set your network credentials
const char *ssid = "PL";
const char *password = "87654321";
String postData = "";
String payload = "";
String authorizationPassword = "esp1";
RGB room2rgb(23, 34, 8, RMT_CHANNEL_0);
LedClass wifiLed(13);
LedClass room3led(12, 39);
TV room3tv(2);
RGB room1rgb(22, 35, 8, RMT_CHANNEL_1);
LedClass room2led(14, 32);
Fan room1fan(18);

DimUpCommand room2dimupcom(&room2rgb);
ChangeColorCommand room2chcolorcom(&room2rgb);
TurnOnCommand room2rgboncom(&room2rgb);
/////////////////////////////////////////////
DimUpCommand room1dimupcom(&room1rgb);
ChangeColorCommand room1chcolorcom(&room1rgb);
TurnOnCommand room1rgboncom(&room1rgb);
SpeedUpCommand room1speedupcom(&room1fan);
/////////////////////////////////////////////
TurnOnCommand room3ledoncom(&room3led);
TurnOnCommand room2ledoncom(&room2led);
TurnOnCommand room1fanoncom(&room1fan);
SendIRCommand room3presstvbtncmd(&room3tv);
//////////////////////////////////
Command *commands[] = {&room2rgboncom, &room1rgboncom, &room2ledoncom, &room3ledoncom, &room1fanoncom};
MacroCommand bedtime(commands, 5);

ROOM room1;
ROOM room2;
ROOM room3;
