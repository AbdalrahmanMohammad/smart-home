#include <WiFi.h>
#include "SPIFFS.h"
#include <WebServer.h>
#include "../lib/functions.h"
#include "../lib/my_library.h"

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

 if (!SPIFFS.begin(true)) { Serial.println("An Error has occurred while mounting SPIFFS");return; }
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


