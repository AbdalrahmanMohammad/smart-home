
// Set your network credentials
const char* ssid = "PLL";
const char* password = "87654321";

// Set your static IP address here
IPAddress staticIP(192, 168, 154, 177); 
IPAddress gateway(192, 168, 154, 1);    
IPAddress subnet(255, 255, 255, 0);  

AsyncWebServer server(80);

int ledPin = 13; 
bool state=false;
unsigned long previous;
int button=0;
unsigned long buttonprevious;