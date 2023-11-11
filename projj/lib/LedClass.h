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

    LedClass() {} // do not use
    LedClass(byte pin);
    LedClass(byte pin,byte buttonPin);

    void init();
    void init(byte defaultState);

    void setButton(int i);

    void on();
    void off();
    void toggle();

    bool isOn();
    bool hasButton();

    byte btn();
};

#endif
