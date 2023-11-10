#include "../lib/LedClass.h"

LedClass::LedClass(byte pin)
{
    this->pin = pin;
    state=LOW;
    previous=0UL;
}

LedClass::LedClass(byte pin, byte buttonPin) : LedClass(pin) { // i called the first constructor

    this->buttonPin = buttonPin;
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
  if(isOn())
  {
    off();
    }
    else {
      on();
      }
}

    void LedClass::setButton(int i)
    {
        buttonPin=i;
    }

    byte LedClass::btn()
    {
        return buttonPin;
    }