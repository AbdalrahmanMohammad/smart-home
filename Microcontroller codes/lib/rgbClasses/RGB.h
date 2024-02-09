
#ifndef RGB_h
#define RGB_h

#include <Arduino.h>
#include <LiteLED.h>
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
    // Declare a LiteLED object instead of a Adafruit_NeoPixel object
    LiteLED strip;
    int red;
    int green;
    int blue;
    led_strip_type_t stripType = LED_STRIP_WS2812;

public:
    RGB(byte pin, byte buttonPin, int num, rmt_channel_t channel) : RGB(pin, num, channel)
    {
        setButton(buttonPin);
    }

    RGB(byte pin, int num, rmt_channel_t channel) : strip(stripType, false, channel)
    {
        this->pin = pin;
        numpixles = num;
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
        strip.begin(pin, numpixles);
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
        else
        {
            strip.brightness(brightness); // important if i set a pixle after the LED was off
            rgb_t Color = {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)};
            rgb_t colors[numpixles];
            std::fill_n(colors, numpixles, Color);
            esp_err_t result = strip.setPixels(0, numpixles, colors, true);
            state = HIGH;
        }
    }

    virtual void setpixle(int r, int g, int b, int i) // this is unused so far
    {
        // Use the setBrightness() method to adjust the overall brightness of the LED strip
        strip.brightness(brightness); // important if i set a pixle after the LED was off

        if (r == g && g == b && b == 0) // you can't use this function to turn the led off, in order to keep state clean
        {
            return;
        }
        state = HIGH;
        rgb_t desiredColor = {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)};
        strip.setPixel(i, desiredColor);
        strip.show();
    }

    virtual void on() override
    {
        setAll(255, 255, 255);
    }

    virtual void off() override
    {

        rgb_t offColor = {0, 0, 0};
        rgb_t colors[numpixles];
        std::fill_n(colors, numpixles, offColor);
        esp_err_t result = strip.setPixels(0, numpixles, colors, true);
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
        strip.brightness(a);
        strip.show();
    }

    virtual void brightnessup()
    {
        if (brightness + 50 > 255)
        {
            setBrightness(255);
        }
        else
        {
            setBrightness(brightness + 50);
        }
    }

    virtual void brightnessdown()
    {
        if (brightness - 50 < 0)
        {
            setBrightness(5);
        }
        else
        {
            setBrightness(brightness - 50);
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

    virtual String getName()
    {
        return "rgb";
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
