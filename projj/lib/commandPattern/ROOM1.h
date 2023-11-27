#include <Command.h>
#include <LedClass.h>
#include <RGB.h>
#include <DimUpCommand.h>
#include <DimDownCommand.h>
#include <ChangeColorCommand.h>
#include <NoRgb.h>
class ROOM1
{
private:
    Command *ledcommand; // i have to make it pointer because of polymorphism (that is how c++ works)
    Command *rgbcommand;
    Command *changecolorcommand;
    Command *dimupcommand;
    Command *dimdowncommand;
    LedClass *led;
    RGB *rgb;

public:
    ROOM1(Command *ledcmd, Command *rgbcmd, LedClass *l, RGB *r, Command *dimup, Command *dimdown, Command *changecolor)
    {
        ledcommand = ledcmd;
        rgbcommand = rgbcmd;
        led = l;
        rgb = r;

        dimupcommand = dimup;
        dimdowncommand = dimdown;
        changecolorcommand = changecolor;
    }

    void init(byte defaultState)
    {
        led->init(defaultState);
        rgb->init(defaultState);
    }

    void excLed()
    {
        ledcommand->execute();
    }

    void excLedPushbutton()
    {
        if (led->checkIfNo()) // checks if it's from Noled class
        {
            return;
        }

        if (millis() - led->getPrevious() >= 300UL)
        {
            this->excLed();
            led->setPrevious(millis());
        }
    }

    void excRgb()
    {
        rgbcommand->execute();
    }

    void excRgbPushbutton()
    {
        if (rgb->checkIfNo())
        {
            return;
        }

        rgb->setBtncurstate(rgb->btnstate());

        if (rgb->getBtncurvstate() == LOW && rgb->getBtnprevstate() == HIGH)
        {
            if (millis() - rgb->getPrevious() >= 500UL)
            {
                rgbcommand->execute();
                rgb->setPrevious(millis());
            }
        }
        rgb->setBtnprevstate(rgb->getBtncurvstate());
    }

    void rgbTimer()
    {
        if (rgb->checkIfNo())
        {
            return;
        }

        if (rgb->getDuration() > 0UL && (millis() - rgb->getStartTime() >= rgb->getDuration()))
        {
            this->excRgb();
            rgb->setDuration(0); // Reset the delay
        }
    }

    void ledTimer()
    {
        if (led->checkIfNo())
        {
            return;
        }

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
        if (rgb->checkIfNo())
        {
            return;
        }

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
};