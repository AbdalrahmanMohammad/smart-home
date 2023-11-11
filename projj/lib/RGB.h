#ifndef RGB_h
#define RGB_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

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
    unsigned long previous;
    unsigned long duration;
    unsigned long startTime;

    RGB(byte pin, byte buttonPin, int num) : RGB(pin, num)
    {
        setButton(buttonPin);
    }

    RGB(byte pin, int num)
    {
        hasbutton = false;
        this->pin = pin;
        numpixles = num;
        strip = Adafruit_NeoPixel(numpixles, pin, NEO_GRB + NEO_KHZ800);
        previous = 0UL;
        state = LOW;
        brightness = 255;
    }

    void init()
    {
        strip.begin();
        strip.show();
        if (hasbutton)
        {
            pinMode(buttonPin, INPUT_PULLUP);
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
        setAll(0, 0, 0);
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
        if (brightness > 245)
        {
            setBrightness(255);
        }
        else
        {
            setBrightness(brightness + 10);
        }
    }

    void brightnessdown()
    {
        if (brightness < 11)
        {
            setBrightness(5);
        }
        else
        {
            setBrightness(brightness - 10);
        }
    }

    void setButton(int i)
    {
        hasbutton = true;
        buttonPin = i;
    }

    int getBrightness()
    {
        return brightness;
    }
};

#endif
