#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <LedClass.h>
#include <RGB.h>
#include <LoggingFunctions.h>

#include<Command.h>
#include<ROOM1.h>
#include<LedToggleCommand.h>
#include <RgbToggleCommand.h>
#include <DimUpCommand.h>
#include <DimDownCommand.h>
#include <ChangeColorCommand.h>

#include <NoCommand.h>
#include <NoLed.h>
#include <NoRgb.h>


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

LedToggleCommand ledcom(&ledPin);
RgbToggleCommand rgbcom(&rgb);
DimUpCommand dimupcom(&rgb);
DimDownCommand dimdowncom(&rgb);
ChangeColorCommand chcolorcom(&rgb);

ROOM1 room1(&ledcom,&rgbcom,&ledPin,&rgb,&dimupcom,&dimdowncom,&chcolorcom);


/// @brief ////////////////////////////////  just to show you how it works ( delete it in the next push)
NoCommand no;
NoLed nol;
NoRgb nor;

ROOM1 room2(&no,&no,&nol,&nor,&no,&no,&no);
/// @brief ////////////////////////////////
