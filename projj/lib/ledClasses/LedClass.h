#ifndef LedClass_h
#define LedClass_h

#include <Arduino.h>

class LedClass
{
protected:
    byte pin;
    byte buttonPin; // it is optional to use
    boolean state;
    boolean hasbutton;

public:
    unsigned long previous; // for button debounce (has nothing to do with the timer)
    unsigned long duration; // for timer (how many seconds to toggle)
    unsigned long startTime; // when i sat the timer

    LedClass(byte pin)
{
    hasbutton = false;
    this->pin = pin;
    state = LOW;
    previous = 0UL;
    duration = 0UL;
    startTime = 0UL;
}

LedClass(byte pin, byte buttonPin) : LedClass(pin)
{ // i called the first constructor
    setButton(buttonPin);
}

void init()
{
    if (hasButton())
    {
        pinMode(buttonPin, INPUT_PULLUP);
    }
    pinMode(pin, OUTPUT);
}
void init(byte defaultState)
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

void on()
{
    digitalWrite(pin, HIGH);
    state = HIGH;
}
void off()
{
    digitalWrite(pin, LOW);
    state = LOW;
}

bool isOn()
{
    return (state == HIGH);
}

void toggle() // you can just digialWrite(pin,!digitalRead(pin)); but this is better
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

void setButton(int i)
{
    hasbutton = true;
    buttonPin = i;
}

byte btn()
{
    return buttonPin;
}

bool hasButton()
{
    return hasbutton;
}

void timer()// toggles the led after (duration) seconds
{

    if (this->duration > 0UL && (millis() - this->startTime >= this->duration))
    {
        this->toggle();
        this->duration = 0; // Reset the delay
    }
}

void onPushbuttonIsClicked() // this toggles when the pushbutton is pressed
{

    if (millis() - this->previous >= 300UL)
    {
        this->toggle();
        this->previous = millis();
    }
}
};

#endif
