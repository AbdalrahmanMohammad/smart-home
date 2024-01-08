
void control_room3_tv()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["signal_value"], "-1") != 0) // control tv signal
  {
    String signal_value = JSON.stringify(myObject["signal_value"]);
    signal_value = signal_value.substring(1, signal_value.length() - 1); // because it returns the value betewen double quotations
    room3.excTvButton(signal_value);
    //////////////////////////////////
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=3";
    postData += "&signal_value=-1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatetv.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control tv timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room3.getTV().setDuration(seconds * 1000);
    room3.getTV().setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=3";
    postData += "&table=tv";
    postData += "&timer=-1";
    postData += "&flag=no"; // this flag to tell updatetimer page not to update timer_time just to update timer.
    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
}

void control_room3_led()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["state"], "ON") == 0 && room3.getLed().isOn() == false) // control led on
  {
    room3.excLedOn();
  }
  if (strcmp(myObject["state"], "OFF") == 0 && room3.getLed().isOn() == true) // control led off
  {
    room3.excLedOff();
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control led timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room3.getLed().setDuration(seconds * 1000);
    room3.getLed().setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=3";
    postData += "&table=led";
    postData += "&timer=-1";
    postData += "&flag=no"; // this flag to tell updatetimer page not to update timer_time just to update timer.
    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
}

void room3get()
{
  if (WiFi.status() == WL_CONNECTED) // for tv
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&table=tv";
    postData += "&roomID=3";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_room3_tv();
  }

    if (WiFi.status() == WL_CONNECTED) // for led
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&table=led";
    postData += "&roomID=3";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_room3_led();
  }
}

void room3send()
{
  if (WiFi.status() == WL_CONNECTED && room3.ledbuttonclicked == true)
  {
    room3.ledbuttonclicked = false;
    HTTPClient http;
    int httpCode;
    String LED_State = "";
    if (room3.getLed().isOn() == true)
      LED_State = "ON";
    else if (room3.getLed().isOn() == false)
      LED_State = "OFF";

    postData = "id=esp1";
    postData += "&roomID=3";
    postData += "&table=led";
    postData += "&changed_by=";
    postData+= (room3.ledbuttonclickedbytimer ? "timer" : "button");
    postData += "&state=" + LED_State;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
    room3.ledbuttonclickedbytimer = false;
  }
}
