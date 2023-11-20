#include "../lib/LedClass.h"

LedClass::LedClass(byte pin)
{
    hasbutton = false;
    this->pin = pin;
    state = LOW;
    previous = 0UL;
    duration = 0UL;
    startTime = 0UL;
}

LedClass::LedClass(byte pin, byte buttonPin) : LedClass(pin)
{ // i called the first constructor
    setButton(buttonPin);
}

void LedClass::init()
{
    if (hasButton())
    {
        pinMode(buttonPin, INPUT_PULLUP);
    }
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
    state = HIGH;
}
void LedClass::off()
{
    digitalWrite(pin, LOW);
    state = LOW;
}

bool LedClass::isOn()
{
    return (state == HIGH);
}

void LedClass::toggle() // you can just digialWrite(pin,!digitalRead(pin)); but this is better
{
    if (isOn())
    {
        off();
    }
    else
    {
        on();
    }
}

void LedClass::setButton(int i)
{
    hasbutton = true;
    buttonPin = i;
}

byte LedClass::btn()
{
    return buttonPin;
}

bool LedClass::hasButton()
{
    return hasbutton;
}

void LedClass::timer()// toggles the led after (duration) seconds
{

    if (this->duration > 0UL && (millis() - this->startTime >= this->duration))
    {
        this->toggle();
        this->duration = 0; // Reset the delay
    }
}

void LedClass::onPushbuttonIsClicked() // this toggles when the pushbutton is pressed
{

    if (millis() - this->previous >= 300UL)
    {
        this->toggle();
        this->previous = millis();
    }
}
