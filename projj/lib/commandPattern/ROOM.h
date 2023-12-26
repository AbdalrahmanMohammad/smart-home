#ifndef ROOM_H
#define ROOM_H

#include <Command.h>
#include <DimUpCommand.h>
#include <DimDownCommand.h>
#include <ChangeColorCommand.h>
#include <LedClass.h>
#include <RGB.h>
#include <NoCommand.h>
#include <NoRgb.h>
#include <NoLed.h>
#include <MacroCommand.h>
#include <TurnOnCommand.h>
#include <TV.h>
#include <NoTV.h>
#include <SendIRCommand.h>

class ROOM
{
private:
    Command *ledoncommand; // i have to make it pointer because of polymorphism (that is how c++ works)
    Command *changecolorcommand;
    Command *dimupcommand;
    Command *dimdowncommand;
    Command *onboth;
    LedClass *led;
    RGB *rgb;
    TV *tv;
    Command *presstvbuttoncommand;// it is of type SendIRCommand

public:
    boolean ledbuttonclicked;
    boolean rgbbuttonclicked;

    ROOM()
    {
        NoCommand *noCmd = &NoCommand::getInstance();
        ledoncommand = noCmd;
        changecolorcommand = noCmd;
        dimupcommand = noCmd;
        dimdowncommand = noCmd;
        onboth = noCmd;
        presstvbuttoncommand = noCmd;
        led = &NoLed::getInstance();
        rgb = &NoRgb::getInstance();
        tv = &NoTV::getInstance();
        ledbuttonclicked = false;
        rgbbuttonclicked = false;
    }

    void setLed(LedClass *l, Command *ledoncom)
    {
        led = l;
        ledoncommand = ledoncom;
    }
    void setRgb(RGB *r, Command *dimup, Command *dimdown, Command *changecolor)
    {
        rgb = r;
        dimupcommand = dimup;
        dimdowncommand = dimdown;
        changecolorcommand = changecolor;
    }

    void setOnBoth(MacroCommand *m)
    {
        onboth = m;
    }

    void setTV(TV *t, Command *pressbtncmd)
    {
        tv = t;
        presstvbuttoncommand = pressbtncmd;
    }

    void init()
    {
        led->init(LOW);
        rgb->init(LOW);
        tv->init();
    }

    void excOnBoth()
    {
        onboth->execute();
    }

    void excOffBoth()
    {
        onboth->undo();
    }

    void excLedOn()
    {
        ledoncommand->execute();
    }

    void excLedOff()
    {
        ledoncommand->undo();
    }

    void excLedTog()
    {
        if (led->isOn())
            this->excLedOff();
        else
            this->excLedOn();
    }

    void excTvButton(String s)
    {
        tv->setButton(s);
        if (s == "x")
            presstvbuttoncommand->undo();
        else
            presstvbuttoncommand->execute();
    }

    void excLedPushbutton()
    {
        led->setBtncurstate(led->btnstate());

        if (led->getBtncurvstate() == LOW && led->getBtnprevstate() == HIGH)
        {
            if (millis() - led->getPrevious() >= 500UL)
            {
                this->excLedTog();
                led->setPrevious(millis());
                ledbuttonclicked = true;
            }
        }
        led->setBtnprevstate(led->getBtncurvstate());
    }

    void excRgb()
    {
        if (rgb->isOn())
            this->excColor(0, 0, 0);
        else
            this->excColor(255, 255, 255);
    }

    void excRgbPushbutton()
    {
        rgb->setBtncurstate(rgb->btnstate());

        if (rgb->getBtncurvstate() == LOW && rgb->getBtnprevstate() == HIGH)
        {
            if (millis() - rgb->getPrevious() >= 500UL)
            {
                this->excRgb();
                rgb->setPrevious(millis());
                rgbbuttonclicked = true;
            }
        }
        rgb->setBtnprevstate(rgb->getBtncurvstate());
    }

    void Timer(Togglable *device)
    {
        if (device->getDuration() > 0UL && (millis() - device->getStartTime() >= device->getDuration()))
        {
            device->setDuration(0); // Reset the delay
            if (device->getName() == "rgb")
            {
                this->excRgb();
                rgbbuttonclicked = true;
            }
            else if (device->getName() == "led")
            {
                this->excLedTog();
                ledbuttonclicked = true;
            }
            else if (device->getName() == "tv")
                this->excTvButton("toggle");
        }
    }

    void timers()
    {
        this->Timer(led);
        this->Timer(rgb);
        this->Timer(tv);
    }

    void excColor(int r, int g, int b)
    {
        rgb->setRed(r);
        rgb->setGreen(g);
        rgb->setBlue(b);
        changecolorcommand->execute();
    }

    void excDimUp()
    {
        dimupcommand->execute();
    }

    void excDimDown()
    {
        dimdowncommand->execute();
    }

    void undoColor()
    {
        changecolorcommand->undo();
    }

    LedClass &getLed()
    {
        return *led;
    }
    RGB &getRgb()
    {
        return *rgb;
    }
    TV &getTV()
    {
        return *tv;
    }
};

#endif