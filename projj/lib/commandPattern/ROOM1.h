#ifndef ROOM1_H
#define ROOM1_H

#include <Command.h>
#include <ToggleCommand.h>
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


class ROOM1
{
private:
    Command *ledtogcommand; // i have to make it pointer because of polymorphism (that is how c++ works)
    Command *changecolorcommand;
    Command *dimupcommand;
    Command *dimdowncommand;
    Command *onboth;
    LedClass *led;
    RGB *rgb;

public:
    ROOM1()
    {
        NoCommand *noCmd = new NoCommand();
        NoLed *noLed = new NoLed();
        NoRgb *noRgb = new NoRgb();

        ledtogcommand = noCmd;
        changecolorcommand = noCmd;
        dimupcommand = noCmd;
        dimdowncommand = noCmd;
        onboth = noCmd;
        led = noLed;
        rgb = noRgb;
    }

    void setLed(LedClass *l, Command *ledtogcom)
    {
        led = l;
        ledtogcommand = ledtogcom;
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

    void init(byte defaultState)
    {
        led->init(defaultState);
        rgb->init(defaultState);
    }

    void excOnBoth()
    {
        onboth->execute();
    }

    void excOffBoth()
    {
        onboth->undo();
    }

    void excLed()
    {
        ledtogcommand->execute();
    }

    void excLedPushbutton()
    {
        if (millis() - led->getPrevious() >= 300UL)
        {
            this->excLed();
            led->setPrevious(millis());
        }
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
            }
        }
        rgb->setBtnprevstate(rgb->getBtncurvstate());
    }

    void rgbTimer()
    {
        if (rgb->getDuration() > 0UL && (millis() - rgb->getStartTime() >= rgb->getDuration()))
        {
            this->excRgb();
            rgb->setDuration(0); // Reset the delay
        }
    }

    void ledTimer()
    {
        if (led->getDuration() > 0UL && (millis() - led->getStartTime() >= led->getDuration()))
        {
            this->excLed();
            led->setDuration(0); // Reset the delay
        }
    }

    void timers()
    {
        this->ledTimer();
        this->rgbTimer();
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
};

#endif