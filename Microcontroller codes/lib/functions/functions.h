#include "room1functions.h"
#include "room2functions.h"
#include "room3functions.h"
#include "sensors.h"

void wificonnection()
{ // it tries to connected to wifi for 6 seconds after this it will contiune wihtout connection

  WiFi.begin(ssid, password);

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

void checkWifi() // checks wifi connection every 3 seconds and shows the condition on wifiLed
{
  if (millis() - wifiLed.getPrevious() >= 3000UL) // this uses the previous differently it uses it to repeat
  {                                               // with constant period. (it doesn't have a button, so this is fine)
    if (WiFi.status() == WL_CONNECTED)
    {
      wifiLed.on();
    }
    else
    {
      wifiLed.off();
    }

    // Serial.println(WiFi.status());

    wifiLed.setPrevious(millis());
  }
}

void room1toggles() // works when the led's pushbutton is pressed
{
  room1.excRgbPushbutton();
}

void room2toggles() // works when the led's or rgb's pushbutton is pressed
{
  room2.excRgbPushbutton();
  room2.excLedPushbutton();
}

void room3toggles()
{
  room3.excLedPushbutton();
}

void senddata()
{
  room1send();
  room2send();
  room3send();
  temp_sensor();
  smoke_sensor();
  check_connection();
}

void getallrooms()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/getallrooms.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();

    JSONVar jsonDoc = JSON.parse(payload);

    room1get(jsonDoc["rgb1"], jsonDoc["fan1"]);
    room2get(jsonDoc["rgb2"], jsonDoc["led2"]);
    room3get(jsonDoc["tv3"], jsonDoc["led3"]);
  }
}

void getdata()
{
  if (inhancer == 0)
    getallrooms();
  else if (inhancer == 1)
    get_others(); // i didn't know what to name it but it gets 1.smokeSensor / 2.lcd / 3.door / 4. bedTimeCommand

  inhancer++;
  inhancer = (inhancer > 1) ? 0 : inhancer;
}
