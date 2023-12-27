
void control_room1()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["state"], "ON") == 0 && room1.getLed().isOn() == false) // control led on
  {
    room1.excLedOn();
  }
  if (strcmp(myObject["state"], "OFF") == 0 && room1.getLed().isOn() == true) // control led off
  {
    room1.excLedOff();
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control led timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room1.getLed().setDuration(seconds * 1000);
    room1.getLed().setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&table=led";
    postData += "&timer=-1";
    postData += "&flag=no"; // this flag to tell updatetimer page not to update timer_time just to update timer.
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
}


void room1get()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&table=led";
    postData += "&roomID=1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_room1();
  }
}


void room1send()
{
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
    postData += "&roomID=1";
    postData += "&table=led";
    postData += "&changed_by=";
    postData+= (room1.ledbuttonclickedbytimer ? "timer" : "button");
    postData += "&state=" + LED_State;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
    room1.ledbuttonclickedbytimer = false;
  }
}
