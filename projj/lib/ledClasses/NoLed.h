#ifndef NO_LED_H
#define NO_LED_H

#include <Arduino.h>
#include <LedClass.h>

class NoLed : public LedClass
{
private:
    NoLed() : LedClass(-1) {}

public:
    static NoLed& getInstance() {
        static NoLed instance; 
        return instance;
    }

    void init() override {}
    void init(byte defaultState) override {}
    void on() override {}
    void off() override {}
    bool isOn() override { return false; }
    void toggle() override {}
    void setButton(int i) override {}
    byte btn() override { return 0; }
    bool hasButton() override { return false; }
    boolean checkIfNo() const override { return true; }// this is to let the invoker know that is NoRgb
    unsigned long getDuration() override { return -1; }
    unsigned long getPrevious() override { return (millis() - 10); }//so (millis() - led->getPrevious() >= 300UL) never satisfies, even though if it satisfy it nothing happens but to save cpu cycles
    unsigned long getStartTime() override { return -1; }            // -10 because it takes some time to get the value from led->getPrevious(), if so happens it will be true because of unsigned overvflow
    void setDuration(unsigned long f) override {}
    void setPrevious(unsigned long f) override {}
    void setStartTime(unsigned long f) override {}
};

#endif
