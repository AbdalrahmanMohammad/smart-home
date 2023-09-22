#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "../lib/functions.h"
#include "../lib/my_library.h"
#include "../lib/LedClass.h" 
void setup()
{
    // Initialize serial communication
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(button), toggleled, FALLING);

    previous = 0;
    buttonprevious = 0;

    // Initialize LED pin as an output
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    pinMode(button, INPUT_PULLUP);

    // Connect to Wi-Fi with static IP
    WiFi.config(staticIP, gateway, subnet);
    WiFi.begin(ssid, password);

    if (WiFi.status() != WL_CONNECTED)
    {
        delay(3000);
        Serial.println("Connecting to WiFi...");
    }
    if (WiFi.status() != WL_CONNECTED)
    {
        delay(3000);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Connected to WiFi");

        Serial.print("ESP32 IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.print("we will continue without connection");
    }
    server.on("/", HTTP_GET, handleRoot);
    server.on("/tog", HTTP_GET, handletoggle);
    server.on("/ledstate", HTTP_GET, handleLEDState); // prints variable state on this route. so when i refresh the page each 300 millis
                                                      // i visit this to get the updates on it and then change the button state depending on the value here

    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    server.begin();
}

void loop()
{
    if (millis() - previous >= 1000UL)
    {
        Serial.println(WiFi.status());
        previous = millis();
        // #######put some code to light up the built-in led when it is connected##########
    }
}
