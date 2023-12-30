void temp_sensor()
{
  if (dhtTimer.clause() && WiFi.status() == WL_CONNECTED) // first clause is timer each 1 minute
  {
    HTTPClient http;
    int httpCode;

    String humidity = String(dht.readHumidity());
    String temperature = String(dht.readTemperature());

    postData = "id=esp1";
    postData += "&temperature=" +temperature ;
    postData += "&humidity=" +humidity ;

    payload = "";
    http.begin("http://192.168.8.110/GP/back/updatetempsensor.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(postData);
    payload = http.getString(); // return nothing
    http.end();
  }
}