#include <WiFi.h>
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

RGB rgb(5,4,8);
LedClass wifiLed(32); 
LedClass ledPin(13,0); 

LedToggleCommand ledtogcom(&ledPin);
RgbToggleCommand rgbtogcom(&rgb);
DimUpCommand dimupcom(&rgb);
DimDownCommand dimdowncom(&rgb);
ChangeColorCommand chcolorcom(&rgb);
Command* commands[] = {&rgbtogcom, &ledtogcom};
MacroCommand togboth(commands, 2);


ROOM1 room1;
