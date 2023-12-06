int secondsToToggle(LedClass a) // this is used to calculate remind time, to be then sent to web page
{
    if (a.getDuration() == 0)
        return -1;
    return (a.getDuration() - (millis() - a.getStartTime())) / 1000;
}

void handleLEDState(AsyncWebServerRequest *request)
{
    /////////////////         this part for recieve data from web page

    if (request->hasArg("seconds")) // normal led timer
    {
        String colorValue = request->arg("seconds");
        int seconds = (int)strtol(colorValue.c_str(), NULL, 10);
        if (seconds == -555) // to toggle the led immediately
        {
            room1.excLed();
            request->send(200, "application/json", "{}");
            return;
        }
        room1.getLed().setDuration(seconds * 1000);
        room1.getLed().setStartTime(millis());
    }

    if (request->hasArg("rgbseconds")) // rgb timer
    {                                  /////////////////
        String colorValue = request->arg("rgbseconds");
        int seconds = (int)strtol(colorValue.c_str(), NULL, 10);
        if (seconds == -555)
        {
            room1.excRgb();
            request->send(200, "application/json", "{}");
            return;
        }
        room1.getRgb().setDuration( seconds * 1000);
        room1.getRgb().setStartTime(millis());
    }

    if (request->hasArg("color")) // rgb color
    {
        String colorValue = request->arg("color");
        int red = (int)strtol(colorValue.substring(1, 3).c_str(), NULL, 16);
        int green = (int)strtol(colorValue.substring(3, 5).c_str(), NULL, 16);
        int blue = (int)strtol(colorValue.substring(5, 7).c_str(), NULL, 16);
        room1.excColor(red, green, blue);
    }

    if (request->hasArg("intensity")) // rgb brightness
    {
        String colorValue = request->arg("intensity");
        if (colorValue == "up")
        {
            room1.excDimUp();
        }
        else
        {
            room1.excDimDown();
        }
    }

        if (request->hasArg("undo")) 
    {
        room1.undoColor();
    }
    //------------------------------------------------------------------
    /////////////      this part for send data to web page

    String stateOfLed = room1.getLed().isOn() ? "On" : "Off";
    String stateOfRGB = room1.getRgb().isOn() ? "On" : "Off";
    long secondsToTog = secondsToToggle(ledPin);
    long secondsToTogrgb = room1.getRgb().getDuration() == 0 ? -1 : ((room1.getRgb().getDuration() - (millis() - room1.getRgb().getStartTime())) / 1000); // didn't work with function, no clue why (it destroyed the whole esp32)

    String info = "{\"state\": \"" + stateOfLed + "\", \"secondsToToggle\": " + secondsToTog + ", \"rgbstate\": \"" + stateOfRGB + "\", \"secondsToTogglergb\": \"" + secondsToTogrgb + "\", \"brightness\": \"" + room1.getRgb().getBrightness() + "\"}";
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
    String buttonLabel = (room1.getLed().isOn() ? "Off" : "On");
    String buttonColor = (room1.getLed().isOn() ? "btn-danger" : "btn-success");
    html.replace("(LED_STATE)", buttonLabel);
    html.replace("btn-primary", buttonColor);

    // Send the HTML content as the response
    request->send(200, "text/html", html);
}

void handlergbx(AsyncWebServerRequest *request)
{ // note this code works just when refreshing the "/"
    // Read the HTML file into a String
    String html;
    File file = SPIFFS.open("/rgbx.html", "r");
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
    String buttonLabel = (room1.getRgb().isOn() ? "Off" : "On");
    String buttonColor = (room1.getRgb().isOn() ? "btn-danger" : "btn-success");
    html.replace("(LED_STATE)", buttonLabel);
    html.replace("btn-primary", buttonColor);

    // Send the HTML content as the response
    request->send(200, "text/html", html);
}