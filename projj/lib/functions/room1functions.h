void control_room1_rgb(JSONVar myObject)
{

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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["color_flag"], "-1") != 0 || room1.startException) // second condition to set color value after restarting
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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatergb.php");
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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatergb.php");
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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatergb.php");
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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatergb.php");
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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatergb.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (room1.startException) // to set brightness value after restarting
  {
    String bright = myObject["brightness"];
    int brightness = (int)strtol(bright.c_str(), NULL, 10);
    room1.getRgb().setBrightness(brightness);
  }
}

void control_room1_fan(JSONVar myObject)
{

  if (room1.startException) // to set speed value after restarting
  {
    String speed = myObject["speed"];
    int speeed = (int)strtol(speed.c_str(), NULL, 10);
    room1.getFan().setSpeed(speeed);
  }

  if (JSON.typeof(myObject) == "undefined")
  {
    return;
  }

  if (strcmp(myObject["state"], "ON") == 0 && room1.getFan().isOn() == false)
  {
    room1.excFanOn();
  }

  if (strcmp(myObject["state"], "OFF") == 0 && room1.getFan().isOn() == true)
  {
    room1.excFanOff();
  }

  if (strcmp(myObject["timer"], "-1") != 0) // control fan timer
  {
    String sec = myObject["timer"];
    int seconds = (int)strtol(sec.c_str(), NULL, 10);
    room1.getFan().setDuration(seconds * 1000);
    room1.getFan().setStartTime(millis());
    ///////////////////////////////////  now make the timer -1 so i don't read it here anymore
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&table=fan";
    postData += "&timer=-1";
    postData += "&flag=no"; // this flag to tell updatetimer page not to update timer_time just to update timer.
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
  if (strcmp(myObject["speedup_flag"], "-1") != 0 && room1.getFan().isOn())
  {
    room1.excSpeedUp();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&speedup_flag=-1";
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatefan.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["speeddown_flag"], "-1") != 0 && room1.getFan().isOn())
  {
    room1.excSpeedDown();
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&speeddown_flag=-1";
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatefan.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }

  if (strcmp(myObject["speed"], String(room1.getFan().getSpeed()).c_str()) != 0) // send the speed to DB, so that esp is what changes speed value in DB not web page
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&speed=" + String(room1.getFan().getSpeed());
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatefan.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
}

void room1get(JSONVar rgb1Obj, JSONVar fan1Obj)
{

  control_room1_rgb(rgb1Obj);

  control_room1_fan(fan1Obj);
  room1.startException = false;
}

void room1send()
{
  if (WiFi.status() == WL_CONNECTED && room1.rgbbuttonclicked == true)
  {
    room1.rgbbuttonclicked = false;
    HTTPClient http;
    int httpCode;
    String FAN_State = "";
    if (room1.getRgb().isOn() == true)
      FAN_State = "ON";
    else if (room1.getRgb().isOn() == false)
      FAN_State = "OFF";

    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&table=rgb";
    postData += "&changed_by=";
    postData += (room1.rgbbuttonclickedbytimer ? "timer" : "button");
    postData += "&state=" + FAN_State;
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
    room1.rgbbuttonclickedbytimer = false;
  }

  if (WiFi.status() == WL_CONNECTED && room1.fantoggledbytimer == true)
  {
    room1.fantoggledbytimer = false;
    HTTPClient http;
    int httpCode;
    String FAN_State = "";
    if (room1.getFan().isOn() == true)
      FAN_State = "ON";
    else if (room1.getFan().isOn() == false)
      FAN_State = "OFF";

    postData = "id=esp1";
    postData += "&roomID=1";
    postData += "&table=fan";
    postData += "&changed_by=timer";
    postData += "&state=" + FAN_State;
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatestate.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
  }
  // i put sending speed in control_room1
}