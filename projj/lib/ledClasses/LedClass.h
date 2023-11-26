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
    unsigned long previous;  // for button debounce (has nothing to do with the timer)
    unsigned long duration;  // for timer (how many seconds to toggle)
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

    virtual void init()
    {
        if (hasButton())
        {
            pinMode(buttonPin, INPUT_PULLUP);
        }
        pinMode(pin, OUTPUT);
    }
    virtual void init(byte defaultState)
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

    virtual void on()
    {
        digitalWrite(pin, HIGH);
        state = HIGH;
    }
    virtual void off()
    {
        digitalWrite(pin, LOW);
        state = LOW;
    }

    virtual bool isOn()
    {
        return (state == HIGH);
    }

    virtual void toggle() // you can just digialWrite(pin,!digitalRead(pin)); but this is better
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

    virtual void setButton(int i)
    {
        hasbutton = true;
        buttonPin = i;
    }

    virtual byte btn()
    {
        return buttonPin;
    }

    virtual bool hasButton()
    {
        return hasbutton;
    }
    virtual boolean checkIfNo() const // this function to let the invoker know that is not instance from NoRgb
    {
        return false;
    }
};

#endif
