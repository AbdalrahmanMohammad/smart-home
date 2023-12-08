#include <WiFi.h>
#include <IRremote.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <LedClass.h>
#include <RGB.h>
#include <LoggingFunctions.h>
#include<ROOM1.h>

#define pr(x) Serial.println(x)

// Set your network credentials
const char* ssid = "PL";
const char* password = "87654321";

// Set your static IP address here
IPAddress staticIP(192, 168, 8, 177); 
IPAddress gateway(192, 168, 8, 1);    
IPAddress subnet(255, 255, 255, 0);  

AsyncWebServer server(80);
IRsend irsend(0);


RGB rgb(5,4,8);
LedClass wifiLed(32); 
LedClass ledPin(12,17); 

ToggleCommand ledtogcom(&ledPin);
DimUpCommand dimupcom(&rgb);
DimDownCommand dimdowncom(&rgb);
ChangeColorCommand chcolorcom(&rgb);
TurnOnCommand ledoncom(&ledPin);
TurnOnCommand rgboncom(&rgb);
Command* commands[] = {&ledoncom, &rgboncom};
MacroCommand onboth(commands, 2);


ROOM1 room1;
