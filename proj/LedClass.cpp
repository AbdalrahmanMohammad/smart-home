#include "LedClass.h"

LedClass::LedClass(byte pin)
{
    this->pin = pin;
    state=LOW;

}

void LedClass::init()
{
    pinMode(pin, OUTPUT);
}
void LedClass::init(byte defaultState)
{
    init();
    if (defaultState == HIGH)
    {
        on();
    }
    else
    {
        off();
    }
}

void LedClass::on()
{
    digitalWrite(pin, HIGH);
    state=HIGH;
}
void LedClass::off()
{
    digitalWrite(pin, LOW);
    state=LOW;
}

bool LedClass::isOn()
{
  return (state==HIGH);
}


void LedClass::toggle() // you can just digialWrite(pin,!digitalRead(pin)); but this is better
{
  Serial.println(isOn());
  if(isOn())
  {
    off();
    }
    else {
      on();
      }
}
