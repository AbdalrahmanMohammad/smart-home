void temp_sensor()
{
  if (dhtTimer.clause() && WiFi.status() == WL_CONNECTED) // first clause is timer each 1 minute
  {
    HTTPClient http;
    int httpCode;

    String humidity = String(dht.readHumidity());
    String temperature = String(dht.readTemperature());

    postData = "id=esp1";
    postData += "&temperature=" + temperature;
    postData += "&humidity=" + humidity;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatetempsensor.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
  }
}

void smoke_sensor()
{
  if (smk.thereIsFire() && smk.ison() == false && WiFi.status() == WL_CONNECTED) // if there is fire, and it just happened now (i didn't send to data base), so i just send for once
  {
    smk.startAlarm();
    HTTPClient http;
    int httpCode;

    postData = "id=esp1";
    postData += "&fire=true";

    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatesmokesensor.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
  }
}

void smoke_sensor_get()
{
  if (smk.ison() == true && WiFi.status() == WL_CONNECTED) // there is fire, and the user still didn't tell me that he managed the situation
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    payload = "";
    http.begin("http://192.168.8.110/GP/back/getsmokesensor.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    JSONVar myObject = JSON.parse(payload);
    if (JSON.typeof(myObject) == "undefined")
    {
      return;
    }

    if (strcmp(myObject["fire"], "false") == 0)
    {
      smk.endAlarm();
    }
  }
}