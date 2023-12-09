#ifndef NO_TV_H
#define NO_TV_H

#include <Arduino.h>
#include <TV.h>

class NoTV : public TV
{
private:
    NoTV() : TV(-1, -1) {}

public:
    static NoTV &getInstance()
    {
        static NoTV instance;
        return instance;
    }

    void init() override {}
    void on() override {}
    void off() override {}
    void toggle() override {}
    unsigned long getDuration() override { return -1; }
    unsigned long getStartTime() override { return -1; }
    void setDuration(unsigned long f) override {}
    void setStartTime(unsigned long f) override {}
    String getButton()override{return "";}
    void setButton(String s)override{}
};

#endif
