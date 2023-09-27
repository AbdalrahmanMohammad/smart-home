#include "../lib/LedClass.h" // include the classes you make here

// Set your network credentials
const char* ssid = "PL";
const char* password = "87654321";

// Set your static IP address here
IPAddress staticIP(192, 168, 8, 177); 
IPAddress gateway(192, 168, 8, 1);    
IPAddress subnet(255, 255, 255, 0);  

AsyncWebServer server(80);

unsigned long wifiLedPrevious;
unsigned long buttonprevious;

const byte button= 0;
LedClass wifiLed(32); 
LedClass ledPin(13); 

