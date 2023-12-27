void control_room1_rgb()
{

  JSONVar myObject = JSON.parse(payload);

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["state"], "ON") == 0 && room1.getRgb().isOn() == false) // control rgb on
  {
    room1.excRgb(); // toggles the led so it will be on
  }

  if (strcmp(myObject["state"], "OFF") == 0 && room1.getRgb().isOn() == true) // control rgb off
  {
    room1.excRgb(); // toggles the led so it will be off
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control rgb timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room1.getRgb().setDuration(seconds * 1000);
    room1.getRgb().setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
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

  if (strcmp(myObject["color_flag"], "-1") != 0 || startEspException2) // second condition to set color value after restarting
  {
    String colorValue = myObject["color"];
    int red = (int)strtol(colorValue.substring(1, 3).c_str(), NULL, 16);
    int green = (int)strtol(colorValue.substring(3, 5).c_str(), NULL, 16);
    int blue = (int)strtol(colorValue.substring(5, 7).c_str(), NULL, 16);
    room1.excColor(red, green, blue);
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
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
    room1.excDimUp();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
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
    room1.excDimDown();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
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
    room1.undoColor();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&undo_flag=-1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["brightness"], String(room1.getRgb().getBrightness()).c_str()) != 0)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&brightness=" + String(room1.getRgb().getBrightness());
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (startEspException2) // to set brightness value after restarting
  {
    String bright = myObject["brightness"];
    int brightness = (int)strtol(bright.c_str(), NULL, 10);
    room1.getRgb().setBrightness(brightness);
  }
}

void room1get()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&table=rgb";
    postData += "&roomID=1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_room1_rgb();
    startEspException2 = false;
  }
}



void room1send()
{
  if (WiFi.status() == WL_CONNECTED && room1.rgbbuttonclicked == true)
  {
    room1.rgbbuttonclicked = false;
    HTTPClient http;
    int httpCode;
    String LED_State = "";
    if (room1.getRgb().isOn() == true)
      LED_State = "ON";
    else if (room1.getRgb().isOn() == false)
      LED_State = "OFF";

    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&table=rgb";
    postData += "&changed_by=";
    postData+= (room1.rgbbuttonclickedbytimer ? "timer" : "button");    postData += "&state=" + LED_State;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
    room1.rgbbuttonclickedbytimer=false;
  }
}