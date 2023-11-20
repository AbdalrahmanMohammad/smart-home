#ifndef RGB_h
#define RGB_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "LoggingFunctions.h"

class RGB
{
private:
    int buttonPin;
    bool hasbutton;
    int pin;
    bool state;
    int brightness; // from 0 to 255
    int numpixles;
    Adafruit_NeoPixel strip;

public:
    bool btnprevstate; // these two btn states because interrupt can't handle rgb functions
    bool btncurstate;  // so they're to toggle the led using button
    unsigned long previous;
    unsigned long duration;
    unsigned long startTime;

    RGB(byte pin, byte buttonPin, int num) : RGB(pin, num)
    {
        setButton(buttonPin);
    }

    RGB(byte pin, int num)
    {
        this->pin = pin;
        numpixles = num;
        strip = Adafruit_NeoPixel(numpixles, pin, NEO_GRB + NEO_KHZ800);
        state = LOW;
        brightness = 255;

        previous = 0UL;
        duration = 0UL;
        startTime = 0UL;

        hasbutton = false;
        btncurstate=HIGH;
        btnprevstate=HIGH;
        buttonPin=-1;
    }

    void init()
    {
        strip.begin();
        strip.show();
        if (hasbutton)
        {
            pinMode(buttonPin, INPUT_PULLUP);
            btnprevstate = digitalRead(buttonPin);
            btncurstate = digitalRead(buttonPin);
        }
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

    void setAll(int r, int g, int b)
    {
        for (int i = 0; i < numpixles; i++)
        {
            setpixle(r, g, b, i);
        }
    }

    void setpixle(int r, int g, int b, int i)
    {
        strip.setBrightness(brightness); // important if i set a pixle after the LED was off

        if (r == g && g == b && b == 0) // you can't use this function to turn the led off, in order to keep state clean
        {
            return;
        }
        state = HIGH;
        strip.setPixelColor(i, strip.Color(r, g, b));
        strip.show();
    }

    void on()
    {
        setAll(255, 255, 255);
    }

    void off()
    {
        setBrightness(0);
        for (int i = 0; i < numpixles; i++)
        {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
        strip.show();
        state = LOW;
        brightness = 255; // so when i turn any LED after the off state it will be on full brightness
    }

    bool isOn()
    {
        return (state == HIGH);
    }

    void setBrightness(int a) // never set brightness 0, because then leds will get off and you need
    {                         // to explicitly turn them on
        if (a < 1)
        {
            return;
        }
        brightness = a;
        strip.setBrightness(a);
        strip.show();
    }

    void brightnessup()
    {
        if (brightness + 20 > 255)
        {
            setBrightness(255);
        }
        else
        {
            setBrightness(brightness + 20);
        }
    }

    void brightnessdown()
    {
        if (brightness - 20 < 0)
        {
            setBrightness(5);
        }
        else
        {
            setBrightness(brightness - 20);
        }
    }

    void setButton(int i)
    {
        hasbutton = true;
        buttonPin = i;
    }

    bool btnstate()
    {
        return digitalRead(buttonPin);
    }

    int btn()
    {
        return buttonPin;
    }

    int getBrightness()
    {
        return brightness;
    }

    void toggle()
    {
        if (isOn())
        {
            off();
            LoggingFunctions::writeLog("rgb", "off");
        }
        else
        {
            on();
            LoggingFunctions::writeLog("rgb", "on");
        }
    }
};

#endif
