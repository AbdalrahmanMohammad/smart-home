
void control_room2_rgb()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["state"], "ON") == 0 && room2.getRgb().isOn() == false) // control rgb on
  {
    room2.excRgb(); // toggles the led so it will be on
  }

  if (strcmp(myObject["state"], "OFF") == 0 && room2.getRgb().isOn() == true) // control rgb off
  {
    room2.excRgb(); // toggles the led so it will be off
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control rgb timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room2.getRgb().setDuration(seconds * 1000);
    room2.getRgb().setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&table=rgb";
    postData += "&timer=-1";
    postData += "&flag=no"; // this flag to tell updatetimer page not to update timer_time just to update timer.
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["color_flag"], "-1") != 0 || room2.startException) // second condition to set color value after restarting
  {
    String colorValue = myObject["color"];
    int red = (int)strtol(colorValue.substring(1, 3).c_str(), NULL, 16);
    int green = (int)strtol(colorValue.substring(3, 5).c_str(), NULL, 16);
    int blue = (int)strtol(colorValue.substring(5, 7).c_str(), NULL, 16);
    room2.excColor(red, green, blue);
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&color_flag=-1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["dimup_flag"], "-1") != 0)
  {
    room2.excDimUp();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&dimup_flag=-1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["dimdown_flag"], "-1") != 0)
  {
    room2.excDimDown();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&dimdown_flag=-1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["undo_flag"], "-1") != 0)
  {
    room2.undoColor();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&undo_flag=-1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["brightness"], String(room2.getRgb().getBrightness()).c_str()) != 0)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&brightness=" + String(room2.getRgb().getBrightness());
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (room2.startException) // to set brightness value after restarting
  {
    String bright = myObject["brightness"];
    int brightness = (int)strtol(bright.c_str(), NULL, 10);
    room2.getRgb().setBrightness(brightness);
  }
}

void control_room2_led()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["state"], "ON") == 0 && room2.getLed().isOn() == false) // control led on
  {
    room2.excLedOn();
  }
  if (strcmp(myObject["state"], "OFF") == 0 && room2.getLed().isOn() == true) // control led off
  {
    room2.excLedOff();
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control led timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room2.getLed().setDuration(seconds * 1000);
    room2.getLed().setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=2";
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


void room2get()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&table=rgb";
    postData += "&roomID=2";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_room2_rgb();
    room2.startException = false;
  }

    if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&table=led";
    postData += "&roomID=2";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_room2_led();
  }
}



void room2send()
{
  if (WiFi.status() == WL_CONNECTED && room2.rgbbuttonclicked == true)
  {
    room2.rgbbuttonclicked = false;
    HTTPClient http;
    int httpCode;
    String LED_State = "";
    if (room2.getRgb().isOn() == true)
      LED_State = "ON";
    else if (room2.getRgb().isOn() == false)
      LED_State = "OFF";

    postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&table=rgb";
    postData += "&changed_by=";
    postData+= (room2.rgbbuttonclickedbytimer ? "timer" : "button");    postData += "&state=" + LED_State;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
    room2.rgbbuttonclickedbytimer=false;
  }
  // i put sending brightness in control_room2

    if (WiFi.status() == WL_CONNECTED && room2.ledbuttonclicked == true)
  {
    room2.ledbuttonclicked = false;
    HTTPClient http;
    int httpCode;
    String LED_State = "";
    if (room2.getLed().isOn() == true)
      LED_State = "ON";
    else if (room2.getLed().isOn() == false)
      LED_State = "OFF";
 
     postData = "id=esp1";
    postData += "&roomID=2";
    postData += "&table=led";
    postData += "&changed_by=";
    postData+= (room2.ledbuttonclickedbytimer ? "timer" : "button");
    postData += "&state=" + LED_State;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
    room2.ledbuttonclickedbytimer = false;
  }

}