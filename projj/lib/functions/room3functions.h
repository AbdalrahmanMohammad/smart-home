
void control_room3()
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
    http.begin("http://192.168.8.110/GP/back/updatetv.php");
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
    http.begin("http://192.168.8.110/GP/back/updatetimer.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
  }
}


void room3get()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&table=tv";
    postData += "&roomID=3";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/getdata.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    control_room3();
  }
}