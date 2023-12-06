#ifndef ROOM1_H
#define ROOM1_H

#include <LoggingFunctions.h>
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
    static int idCounter;
    int roomID;
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

        String redVlaue = String(rgb->getRed());
        String greenVlaue = String(rgb->getGreen());
        String blueVlaue = String(rgb->getBlue());

        String redKey = String(roomID) + "red";
        String greenKey = String(roomID) + "green";
        String blueKey = String(roomID) + "blue";
        String brightnessKey = String(roomID) + "rgbBrightness";
        LoggingFunctions::writeLog(redKey, redVlaue);
        LoggingFunctions::writeLog(greenKey, greenVlaue);
        LoggingFunctions::writeLog(blueKey, blueVlaue);
        LoggingFunctions::writeLog(brightnessKey, rgb->getBrightness());
    }

    void logLed()
    {
        if (led == &NoLed::getInstance())
            return;

        String key = String(roomID) + "led";
        String value = String(led->isOn());
        LoggingFunctions::writeLog(key, value);
    }

public:
    ROOM1()
    {
        roomID = idCounter++; // takes id and increment by 1 so the second room takes another id
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

    void init()
    {
        led->init(LOW);
        rgb->init(LOW);

        String ledkey = String(roomID) + "led";
        String redKey = String(roomID) + "red";
        String greenKey = String(roomID) + "green";
        String blueKey = String(roomID) + "blue";
        String brightnessKey = String(roomID) + "rgbBrightness";

        if (LoggingFunctions::readLog(ledkey) == "1")
        {
            excLed();
        }
        if (LoggingFunctions::readLog(brightnessKey) != "not existed!!") // brightness & colors are set together, so if one exists all of them exist
        {
            rgb->setBrightness(LoggingFunctions::readLog(brightnessKey).toInt());
            int r, b, g;
            r = LoggingFunctions::readLog(redKey).toInt();
            g = LoggingFunctions::readLog(greenKey).toInt();
            b = LoggingFunctions::readLog(blueKey).toInt();
            excColor(r, g, b);
        }
    }

    void excOnBoth()
    {
        onboth->execute();
        logLed();
        logRgb();
    }

    void excOffBoth()
    {
        onboth->undo();
        logLed();
        logRgb();
    }

    void excLed()
    {
        ledtogcommand->execute();
        logLed();
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
        logRgb();
    }

    void excDimUp()
    {
        dimupcommand->execute();
        logRgb();
    }

    void excDimDown()
    {
        dimdowncommand->execute();
        logRgb();
    }

    void undoColor()
    {
        changecolorcommand->undo();
        logRgb();
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
int ROOM1::idCounter = 0;

#endif