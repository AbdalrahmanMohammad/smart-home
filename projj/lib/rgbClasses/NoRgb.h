#ifndef NO_RGB_H
#define NO_RGB_H

#include <Arduino.h>
#include <RGB.h>

class NoRgb : public RGB
{
private:
public:
    NoRgb() : RGB(-1, -1) {}

    void init() override {}

    void init(byte d) override {}

    void setAll(int r, int g, int b) override {}

    void setpixle(int r, int g, int b, int i) override {}

    void on() override {}

    void off() override {}

    bool isOn() override { return false; }

    void setBrightness(int a) override {}

    void brightnessup() override {}

    void brightnessdown() override {}

    void setButton(int i) override {}

    bool btnstate() override { return false; }

    int btn() override { return -1; }

    int getBrightness() override { return -1; }

    void toggle() override {}

    byte getRed() override { return -1; }

    byte getGreen() override { return -1; }

    byte getBlue() override { return -1; }

    void setRed(byte t) override {}

    void setGreen(byte t) override {}

    void setBlue(byte t) override {}
    boolean checkIfNo() const override // this is to let the invoker know that is NoRgb
    {
        return true;
    }
};

#endif