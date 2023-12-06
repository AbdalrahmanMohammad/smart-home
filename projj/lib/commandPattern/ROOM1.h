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

    void logRgb()
    {
        if (rgb == &NoRgb::getInstance())
            return;
        String colors = String(rgb->getRed()) + "," + String(rgb->getGreen());
        colors += "," + String(rgb->getBlue());
        LoggingFunctions::writeLog("rgbCol", colors);
        LoggingFunctions::writeLog("rgbDim", rgb->getBrightness());
    }

    void logLed()
    {
        if (led == &NoLed::getInstance())
            return;

        String val = String(led->isOn());
        LoggingFunctions::writeLog("led", val);
    }

    void logAll()
    {
        logLed();
        logRgb();
    }

public:
    ROOM1()
    {
        NoCommand *noCmd = &NoCommand::getInstance();
        ledtogcommand = noCmd;
        changecolorcommand = noCmd;
        dimupcommand = noCmd;
        dimdowncommand = noCmd;
        onboth = noCmd;
        led = &NoLed::getInstance();
        rgb = &NoRgb::getInstance();
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
        logAll();
    }

    void excOffBoth()
    {
        onboth->undo();
        logAll();
    }

    void excLed()
    {
        ledtogcommand->execute();
        logAll();
    }

    void excLedPushbutton()
    {
        led->setBtncurstate(led->btnstate());

        if (led->getBtncurvstate() == LOW && led->getBtnprevstate() == HIGH)
        {
            if (millis() - led->getPrevious() >= 500UL)
            {
                this->excLed();
                led->setPrevious(millis());
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
        logAll();
    }

    void excDimUp()
    {
        dimupcommand->execute();
        logAll();
    }

    void excDimDown()
    {
        dimdowncommand->execute();
        logAll();
    }

    void undoColor()
    {
        changecolorcommand->undo();
        logAll();
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