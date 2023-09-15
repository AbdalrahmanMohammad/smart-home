unsigned long previous;
byte state=HIGH;

void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT_PULLUP);
pinMode(13,OUTPUT);
Serial.begin(9600);
      attachInterrupt(digitalPinToInterrupt(2), buttonInterrupt, FALLING);


previous =0;
}

void loop() {

//Serial.println( digitalRead(2));


}

void buttonInterrupt() {
    if ((millis() - previous) > 300UL) {
  digitalWrite(13,!digitalRead(13));
previous=millis();
    }
  
  }
