#include <Arduino.h>
#include <LedClass.h>

class NoLed : public LedClass
{
private:
public:
    NoLed() : LedClass(-1) {}

    void init() override {}
    void init(byte defaultState) override {}
    void on() override {}
    void off() override {}
    bool isOn() override { return false; }
    void toggle() override {}
    void setButton(int i) override {}
    byte btn() override { return 0; }
    bool hasButton() override { return false; }
    boolean checkIfNo() const override // this is to let the invoker know that is NoRgb
    {
        return true;
    }
    unsigned long getDuration() override {return -1;}
    unsigned long getPrevious() override {return -1;}
    unsigned long getStartTime() override {return -1;}
    void setDuration(unsigned long f) override {}
    void setPrevious(unsigned long f) override {}
    void setStartTime(unsigned long f) override {}
};