void printTemp()
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temper.: ");
  lcd.print(dht.readTemperature());
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(dht.readHumidity());
  lcd.print("%");
}

void printTime(String time, String date)
{
  time = time.substring(1, time.length() - 1);
  date = date.substring(1, date.length() - 1);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(date);

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(time);
}

void printFire()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FIRE!!!!!!!!!!");
  lcd.setCursor(0, 1);
  lcd.print("**************");
}

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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatetempsensor.php");
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
    printFire();
    HTTPClient http;
    int httpCode;

    postData = "id=esp1";
    postData += "&fire=true";
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/updatesmokesensor.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();

    postData = "id=esp1";
    postData += "&password=" + authorizationPassword;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/mail/sendForAll.php");
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
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/getsmokesensor.php");
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

void door_get()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&password=" + authorizationPassword;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/controldoor.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    JSONVar myObject = JSON.parse(payload);

    if (JSON.typeof(myObject) == "undefined")
    {
      return;
    }
    if (strcmp(myObject["flag"], "1") == 0)
    {
      String doorstate;
      if (strcmp(myObject["state"], "open") == 0)
      {
        myStepper.step(666);
        doorstate = "open";
      }
      else if (strcmp(myObject["state"], "closed") == 0)
      {
        myStepper.step(-666);
        doorstate = "closed";
      }
      postData = "id=esp1";
      postData += "&state=" + doorstate;
      postData += "&flag=0";
      postData += "&password=" + authorizationPassword;
      payload = "";
      http.begin("http://192.168.8.110/GP/back/controlData/controldoor.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      httpCode = http.POST(postData);
      payload = http.getString(); // returns nothing
      http.end();
    }
  }
}

void lcd_get()
{
  if (lcdTimer.clause() && WiFi.status() == WL_CONNECTED) // there is fire, and the user still didn't tell me that he managed the situation
  {
    HTTPClient http;
    int httpCode;
    postData = "id=esp1";
    postData += "&password=" + authorizationPassword;
    payload = "";
    http.begin("http://192.168.8.110/GP/back/controlData/getlcd.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString();
    http.end();
    JSONVar myObject = JSON.parse(payload);
    if (JSON.typeof(myObject) == "undefined")
    {
      return;
    }

    if (strcmp(myObject["fire"], "true") == 0)
    {
      printFire();
    }
    else
    {
      if (strcmp(myObject["show"], "temp") == 0)
      {
        printTemp();
      }
      if (strcmp(myObject["show"], "time") == 0)
      {
        String time = JSON.stringify(myObject["time"]);
        String date = JSON.stringify(myObject["date"]);

        printTime(time, date);
      }
    }
  }
}
