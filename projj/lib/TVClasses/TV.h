#ifndef TVClass_h
#define TVClass_h

#include <Arduino.h>
#include <IRremote.h>

class TV : public Togglable// important: for esps32 you need to go to IRremote.hpp and #define IR_SEND_PIN 2
{                          // replace 2 with any gpio you want to connect irSender to. if you don't do that
private:                    // it won't send anything. (by default it will be choosen 0, but 0 shouldn't be grounded at booting)
    byte pin;
    IRsend irsend;
    String button; // last button i pressed (importat for SendIRCommand class)

public:
    TV(byte pin) 
    {
        this->pin = pin;
    }

    virtual void init()
    {
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
    virtual String getName()
    {
        return "tv";
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
        else if (userInput == "toggle") // this causes some troubles with timer if i do it just once
        {                               
            for (int i = 0; i < 5; i++)
            {
                irsend.sendNECMSB(0x40BF708F, 32);
            }
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
