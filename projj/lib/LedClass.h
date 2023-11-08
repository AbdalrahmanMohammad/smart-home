#ifndef LedClass_h
#define LedClass_h

#include <Arduino.h>

class LedClass
{
private:
    byte pin;
    byte state;

public:
    unsigned long previous; // for button debounce
    unsigned long duration; // for timer (how many seconds to toggle)
    unsigned long startTime; // when i sat the timer

    LedClass() {} // do not use
    LedClass(byte pin);

    void init();
    void init(byte defaultState);

    void on();
    void off();
    void toggle();

    bool isOn();
};

#endif
