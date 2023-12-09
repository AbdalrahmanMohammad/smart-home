#ifndef TVClass_h
#define TVClass_h

#include <Arduino.h>
#include <IRremote.h>

class TV : public Togglable
{
private:
    byte pin;
    byte helperPin; // for the esp32 i use no pin can transmit IR signals but pin 0, and pin 0 shouldn't
                    // be connected to ground at booting, otherwise esp will get forzen.
                    // so i use a transistor as a switch which connects pin to ground after esp boots up.
                    // and helper pin is the pin that control the transistor(the transistor is normally off and when microcontroller is in void setUP(it has booted) i make make pin helper high to close the circuit)
    IRsend irsend;

    String button; // last button i pressed (importat for PressTvButton class)

public:
    TV(byte pin, byte helper) // you have to use 0 for pin, but i will keep it like this in case another microcontroler is used
    {
        this->pin = pin;
        this->helperPin = helper;
    }

    virtual void init()
    {
        pinMode(helperPin, OUTPUT);
        digitalWrite(helperPin, HIGH);
        irsend.begin(pin);
    }

    virtual void toggle() override
    {
        sendSignal("toggle");
    }

    virtual void on() override
    {
        sendSignal("on");
    }
    virtual void off() override
    {
        sendSignal("off");
    }

    virtual String getButton()
    {
        return button;
    }
    virtual void setButton(String btn)
    {
        button = btn;
    }
    virtual void sendSignal(String userInput)
    {
        if (userInput == "0")
        {
            irsend.sendNECMSB(0x40BF22DD, 32);
        }
        else if (userInput == "1")
        {
            irsend.sendNECMSB(0x40BF48B7, 32);
        }
        else if (userInput == "2")
        {
            irsend.sendNECMSB(0x40BF6897, 32);
        }
        else if (userInput == "3")
        {
            irsend.sendNECMSB(0x40BF40BF, 32);
        }
        else if (userInput == "4")
        {
            irsend.sendNECMSB(0x40BF58A7, 32);
        }
        else if (userInput == "5")
        {
            irsend.sendNECMSB(0x40BF7887, 32);
        }
        else if (userInput == "6")
        {
            irsend.sendNECMSB(0x40BFC03F, 32);
        }
        else if (userInput == "7")
        {
            irsend.sendNECMSB(0x40BFF00F, 32);
        }
        else if (userInput == "8")
        {
            irsend.sendNECMSB(0x40BFD02F, 32);
        }
        else if (userInput == "9")
        {
            irsend.sendNECMSB(0x40BFE01F, 32);
        }
        else if (userInput == "toggle")
        {
            irsend.sendNECMSB(0x40BF708F, 32);
        }
        else if (userInput == "on")
        {
            irsend.sendNECMSB(0x40BF708F, 32);
        }
        else if (userInput == "off")
        {
            irsend.sendNECMSB(0x40BF708F, 32);
        }
        else if (userInput == "volup")
        {
            irsend.sendNECMSB(0x40BF8A75, 32);
        }
        else if (userInput == "voldown")
        {
            irsend.sendNECMSB(0x40BF8A75, 32);
        }
        else if (userInput == "chup")
        {
            irsend.sendNECMSB(0x40BF827D, 32);
        }
        else if (userInput == "chdown")
        {
            irsend.sendNECMSB(0x40BFA25D, 32);
        }
        else
        {
            // send nothing
        }
    };
};
#endif
