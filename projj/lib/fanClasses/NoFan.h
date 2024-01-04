#ifndef NO_Fan_H
#define NO_Fan_H

#include <Arduino.h>
#include <Fan.h>

class NoFan : public Fan
{
private:
    NoFan() : Fan(-1) {}

public:
    static NoFan &getInstance()
    {
        static NoFan instance;
        return instance;
    }

    void init() override {}
    void init(byte defaultState) override {}
    void on() override {}
    void off() override {}
    bool isOn() override { return false; }
    void toggle() override {}
    boolean checkIfNo() const override { return true; } // this is to let the invoker know that is NoFan
    String getName() override { return ""; }
    void speedUp() override {}
    void speedDown() override {}
    int getSpeed() override {return -1;}
};

#endif
