#ifndef NO_RGB_H
#define NO_RGB_H

#include <Arduino.h>
#include <RGB.h>

class NoRgb : public RGB
{
private:
    NoRgb() : RGB(-1, -1,RMT_CHANNEL_7) {}

public:
    static NoRgb& getInstance() {
        static NoRgb instance; 
        return instance;
    }

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

    boolean checkIfNo() const override { return true; }// this is to let the invoker know that is NoRgb

    unsigned long getDuration() override { return -1; }
    unsigned long getPrevious() override { return (millis() - 10); }//same reason an in noled, (even though that is not necessar for rgb because it will not even reach this if statement)
    unsigned long getStartTime() override { return -1; }
    boolean getBtnprevstate() override { return false; }
    boolean getBtncurvstate() override { return false; }
    void setDuration(unsigned long f) override {}
    void setPrevious(unsigned long f) override {}
    void setStartTime(unsigned long f) override {}
    void setBtnprevstate(boolean s) override {}
    void setBtncurstate(boolean s) override {}
};

#endif
