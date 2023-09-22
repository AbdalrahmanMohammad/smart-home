#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "../lib/functions.h"
#include "../lib/my_library.h"

void setup()
{
    Serial.begin(9600);

    wifiLed.init(LOW); 
    ledPin.init(LOW);

    attachInterrupt(digitalPinToInterrupt(button), toggleled, FALLING);

    wifiLedPrevious = 0;
    buttonprevious = 0;

    pinMode(button, INPUT_PULLUP);

    // Connect to Wi-Fi with static IP
    WiFi.config(staticIP, gateway, subnet);
    WiFi.begin(ssid, password);

    wificonnection();

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
    checkWifi(); 
}
