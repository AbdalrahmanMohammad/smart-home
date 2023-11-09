#include "../include/header.h"

void wificonnection()
{ // it tries to connected to wifi for 6 seconds after this it will contiune wihtout connection
  if (WiFi.status() != WL_CONNECTED)
  {
    delay(3000);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi...");
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
}

void checkWifi()// checks wifi connection every 3 seconds and shows the condition on wifiLed
{
  if (millis() - wifiLed.previous >= 3000UL)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      wifiLed.on();
    }
    else
    {
      wifiLed.off();
    }

    // Serial.println(WiFi.status());

    wifiLed.previous = millis();
  }
}

void toggleled()
{
  if (millis() - ledPin.previous >= 300UL)
  {
    ledPin.toggle();
    ledPin.previous = millis();
  }
}

void handletoggle(AsyncWebServerRequest *request)
{
  toggleled();
  request->redirect("/");
}

void handleLEDState(AsyncWebServerRequest *request)
{


      if (request->hasArg("seconds")) {
        String colorValue = request->arg("seconds");
        int seconds= (int)strtol(colorValue.c_str(), NULL, 10);
      ledPin.duration = seconds * 1000; // Convert seconds to milliseconds
      ledPin.startTime = millis(); // Start time
      return;
    }

  request->send(200, "text/plain", String(ledPin.isOn() ? "On" : "Off"));
}

void handleRoot(AsyncWebServerRequest *request)
{ // note this code works just when refreshing the "/"
  // Read the HTML file into a String
  String html;
  File file = SPIFFS.open("/indexx.html", "r");
  if (file)
  {
    while (file.available())
    {
      html += (char)file.read();
    }
    file.close();
  }
  else
  {
    Serial.println("Failed to open HTML file");
    return;
  }

  // Replace the placeholder with LED state and color when reloading the page
  String buttonLabel = (ledPin.isOn()  ? "Off" : "On");
  String buttonColor = (ledPin.isOn()  ? "btn-danger" : "btn-success");
  html.replace("(LED_STATE)", buttonLabel);
  html.replace("btn-primary", buttonColor);

  // Send the HTML content as the response
  request->send(200, "text/html", html);
}
void  ledTimer()
{
  if (ledPin.duration > 0 && (millis() - ledPin.startTime >= ledPin.duration )) {
    Serial.println("yes i'm here");
    toggleled();
    ledPin.duration = 0; // Reset the delay
  }
}