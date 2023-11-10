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
  if (millis() - wifiLed.previous >= 3000UL)// this uses the previous differently it uses it to repeat
  {                                         // with constant period. (it doesn't have a button, so this is fine)
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

int secondsToToggle(LedClass a) // this is used to calculate remind time, to be then sent to web page
{
  if (a.duration==0)
  return -1;
  return (a.duration-(millis()-a.startTime))/1000;
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


      if (request->hasArg("seconds")) {/////////////////         this part for recieve data from web page
        String colorValue = request->arg("seconds");
        int seconds= (int)strtol(colorValue.c_str(), NULL, 10);
      ledPin.duration = seconds * 1000; // Convert seconds to milliseconds
      ledPin.startTime = millis(); // Start time
      return;
    }
    //------------------------------------------------------------------
                                                 /////////////      this part for send data to web page

    String stateOfLed=ledPin.isOn() ? "On" : "Off";
    long secondsToTog = secondsToToggle(ledPin);
    String info = "{\"state\": \"" + stateOfLed + "\", \"secondsToToggle\": "+secondsToTog+"}";
    request->send(200, "application/json", info);

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
    toggleled();
    ledPin.duration = 0; // Reset the delay
  }
}

