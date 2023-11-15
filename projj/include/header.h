#include "../lib/LedClass.h" // include the classes you make here
#include "../lib/RGB.h" 

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

