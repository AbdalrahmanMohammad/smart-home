
// Set your network credentials
const char* ssid = "PL";
const char* password = "87654321";

// Set your static IP address here
IPAddress staticIP(192, 168, 8, 177); 
IPAddress gateway(192, 168, 8, 1);    
IPAddress subnet(255, 255, 255, 0);  

WebServer server(80);

int ledPin = 13; 
bool state=false;
unsigned long previous;
int button=2;
unsigned long buttonprevious;