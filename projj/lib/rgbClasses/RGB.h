#ifndef RGB_h
#define RGB_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Toggelable.h>

class RGB : public Togglable
{
private:
    int buttonPin;
    bool hasbutton;
    int pin;
    bool state;
    int brightness; // from 0 to 255
    int numpixles;
    Adafruit_NeoPixel strip;
    int red;
    int green;
    int blue;


public:
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
        red = 0;
        green = 0;
        blue = 0;

        previous = 0UL;
        duration = 0UL;
        startTime = 0UL;

        hasbutton = false;
        btncurstate = HIGH;
        btnprevstate = HIGH;
        buttonPin = -1;
    }

    virtual void init()
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

    virtual void init(byte defaultState)
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

    virtual void setAll(int r, int g, int b)
    {
        if (r == g && g == b && b == 0)
        {
            this->off();
        }
        for (int i = 0; i < numpixles; i++)
        {
            setpixle(r, g, b, i);
            red = r;
            green = g;
            blue = b;
        }
    }

    virtual void setpixle(int r, int g, int b, int i)
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

    virtual void on() override
    {
        setAll(255, 255, 255);
    }

    virtual void off() override
    {
        setBrightness(0);
        for (int i = 0; i < numpixles; i++)
        {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
        strip.show();
        state = LOW;
        red = 0;
        green = 0;
        blue = 0;
        brightness = 255; // so when i turn any LED after the off state it will be on full brightness
    }

    virtual bool isOn()
    {
        return (state == HIGH);
    }

    virtual void setBrightness(int a) // never set brightness 0, because then leds will get off and you need
    {                                 // to explicitly turn them on
        if (a < 1)
        {
            return;
        }
        brightness = a;
        strip.setBrightness(a);
        strip.show();
    }

    virtual void brightnessup()
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

    virtual void brightnessdown()
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

    virtual void setButton(int i)
    {
        hasbutton = true;
        buttonPin = i;
    }

    virtual bool btnstate()
    {
        return digitalRead(buttonPin);
    }

    virtual int btn()
    {
        return buttonPin;
    }

    virtual int getBrightness()
    {
        return brightness;
    }

    virtual void toggle() override
    {
        if (isOn())
        {
            off();
        }
        else
        {
            on();
        }
    }

    virtual byte getRed()
    {
        return red;
    }
    virtual byte getGreen()
    {
        return green;
    }
    virtual byte getBlue()
    {
        return blue;
    }
    virtual void setRed(byte t)
    {
        red = t;
    }
    virtual void setGreen(byte t)
    {
        green = t;
    }
    virtual void setBlue(byte t)
    {
        blue = t;
    }
    virtual boolean checkIfNo() const // this function to let the invoker know that is not instance from NoRgb
    {
        return false;
    }

};

#endif
