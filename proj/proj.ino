#include <WiFi.h>
#include <WebServer.h>

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



void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(button),toggleled,FALLING);

  previous=0; 
  buttonprevious=0;
  
  // Initialize LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(button,INPUT_PULLUP);

  // Connect to Wi-Fi with static IP
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/tog", HTTP_GET, handletoggle);


  server.begin();
}

void loop() {
  server.handleClient();
    if(millis()-previous>=3000UL)
  {
    Serial.println(WiFi.status());
    previous=millis();
              // #######put some code to light up the built-in led when it is connected##########
    }
}


void handleRoot() {
  String html = "<html><body>";
  html += "<h1>NodeMCU LED Control</h1>";
  html += "<button id=\"myButton\" onclick=\"toggle()\">" + String(state ? "Off" : "On") + "</button>";
  html += "<script>";
  html += "function toggle() {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/tog', true);";
  html += "  xhr.send();";
  html += "  var button = document.getElementById('myButton');";
  html += "  if (button.innerHTML === 'On') {";
  html += "    button.innerHTML = 'Off';";
  html += "  } else {";
  html += "    button.innerHTML = 'On';";
  html += "  }";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html); // ### this is so important because it sends back to client that server got it###
}


void handletoggle() {
toggleled();
    server.send(200, "text/plain", "LED toggled"); // note this is so heavy for the interrupt
}




void toggleled()// #####keep this for all leds (300 millis is very small) and make array for states and name the leds by numbers#######
{
      if(millis()-buttonprevious>=300UL)
 {
    state=!state;
  digitalWrite(ledPin, state); 
      buttonprevious=millis();
  }
  }
