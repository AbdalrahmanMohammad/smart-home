#include "header.h"
#include <functions.h>

String postData = "";
String payload = "";

void setup()
{
  Serial.begin(9600);

  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  room1.setLed(&ledPin, &ledoncom);
  // room1.setRgb(&rgb, &dimupcom, &dimdowncom, &chcolorcom);
  // room1.setOnBoth(&onboth);
  // room1.setTV(&tv, &presstvbtncmd);

  wifiLed.init(LOW);
  room1.init();

  // Connect to Wi-Fi with static IP
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  wificonnection();
}

void control_LEDs()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    // Serial.println("returned");
    return;
  }

  if (strcmp(myObject["LED"], "ON") == 0 && room1.getLed().isOn() == false)
  {
    room1.excLedOn();
  }
  if (strcmp(myObject["LED"], "OFF") == 0 && room1.getLed().isOn() == true)
  {
    room1.excLedOff();
  }

  if (strcmp(myObject["timer_flag"], "1") == 0)
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room1.getLed().setDuration(seconds * 1000);
    room1.getLed().setStartTime(millis());
    ///////////////////////////////////  now make the flag zero so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&timer=" + sec;
    postData += "&timer_flag=0";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
    String userInput = Serial.readString();
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_LEDs();
  }
  ///////////////////////////////////////////////////////////////////////
  togglergb(); // toggles the rgb led using the button
  toggleled(); // toggles the led using the button
  checkWifi();
  room1.timers();

  //////////////////////////////////////////////////
  if (WiFi.status() == WL_CONNECTED && room1.ledbuttonclicked == true)
  {
    room1.ledbuttonclicked = false;
    HTTPClient http;
    int httpCode;
    String LED_State = "";
    if (room1.getLed().isOn() == true)
      LED_State = "ON";
    else if (room1.getLed().isOn() == false)
      LED_State = "OFF";

    postData = "id=esp1";
    postData += "&LED=" + LED_State;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatedata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
  }
}