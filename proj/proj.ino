#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Set your network credentials
const char* ssid = "PL";
const char* password = "87654321";

// Set your static IP address here
IPAddress staticIP(192, 168, 8, 177); // Change to the desired static IP address
IPAddress gateway(192, 168, 8, 1);    // Your router's IP address
IPAddress subnet(255, 255, 255, 0);  // Subnet mask

ESP8266WebServer server(80);

int ledPin = D1; // GPIO pin connected to the LED

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi with static IP
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the NodeMCU's IP address
  Serial.print("NodeMCU IP address: ");
  Serial.println(WiFi.localIP());

  // Define web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  // Start the web server
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>NodeMCU LED Control</h1>";
  html += "<p>Click the buttons below to control the LED:</p>";
  html += "<a href='/on'><button>Turn On</button></a>";
  html += "<a href='/off'><button>Turn Off</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH); // Turn the LED on
  server.send(200, "text/html", "LED turned on"); // text/html or text/plain no big difference
}

void handleOff() {
  digitalWrite(ledPin, LOW); // Turn the LED off
  server.send(200, "text/plain", "LED turned off");
}
