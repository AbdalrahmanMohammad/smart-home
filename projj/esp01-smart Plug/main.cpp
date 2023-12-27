
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <LedClass.h>

WiFiClient client;
const char *ssid = "PL";
const char *password = "87654321";
String postData = "";
String payload = "";
LedClass ledPin(0, 3);
boolean buttonclicked = false;
boolean buttonclickedbytimer = false;

void setup()
{
  Serial.begin(115200);
  ledPin.init();
  WiFi.begin(ssid, password);

  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void control()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["state"], "ON") == 0 && ledPin.isOn() == false) // control led on
  {
    ledPin.on();
  }
  if (strcmp(myObject["state"], "OFF") == 0 && ledPin.isOn() == true) // control led off
  {
    ledPin.off();
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control led timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    ledPin.setDuration(seconds * 1000);
    ledPin.setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp01";
    postData += "&roomID=-";
    postData += "&table=plug";
    postData += "&timer=-1";
    postData += "&flag=no"; // this flag to tell updatetimer page not to update timer_time just to update timer.
    payload = "";
    http.begin(client, "http://192.168.8.110/GP/back/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
}

void getdata()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp01";
    postData += "&table=plug";
    postData += "&roomID=-";
    payload = "";
    http.begin(client, "http://192.168.8.110/GP/back/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control();
  }
}

void senddata()
{
  if (WiFi.status() == WL_CONNECTED && buttonclicked == true)
  {
    buttonclicked = false;
    HTTPClient http;
    int httpCode;
    String LED_State = "";
    if (ledPin.isOn() == true)
      LED_State = "ON";
    else if (ledPin.isOn() == false)
      LED_State = "OFF";

    postData = "id=esp01";
    postData += "&roomID=-";
    postData += "&table=plug";
    postData += "&changed_by=";
    postData+= (buttonclickedbytimer ? "timer" : "button");
    postData += "&state=" + LED_State;
    payload = "";
    http.begin(client, "http://192.168.8.110/GP/back/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
    buttonclickedbytimer=false;
  }
}

void Timer()
{
  if (ledPin.getDuration() > 0UL && (millis() - ledPin.getStartTime() >= ledPin.getDuration()))
  {
    ledPin.setDuration(0); // Reset the delay
    ledPin.toggle();
    buttonclicked = true;
    buttonclickedbytimer = true;
  }
}

void LedPushbutton()
{
  ledPin.setBtncurstate(ledPin.btnstate());

  if (ledPin.getBtncurvstate() == LOW && ledPin.getBtnprevstate() == HIGH)
  {
    if (millis() - ledPin.getPrevious() >= 500UL)
    {
      ledPin.toggle();
      ledPin.setPrevious(millis());
      buttonclicked = true;
    }
  }
  ledPin.setBtnprevstate(ledPin.getBtncurvstate());
}

void loop()
{
  getdata();
  LedPushbutton();
  Timer();
  senddata();
}