#ifndef Turn_On_Command_H
#define Turn_On_Command_H

#include <Command.h>
#include <NoRgb.h>
#include <NoLed.h>

class TurnOnCommand: public Command
{
private:

    LedClass *led;
    RGB *rgb;

public:
    TurnOnCommand(LedClass* l)
    {
        NoRgb *noRgb = new NoRgb();
        rgb = noRgb;
        led=l;
    }
    TurnOnCommand(RGB* r)
    {
        NoLed *noLed = new NoLed();
        led = noLed;
        rgb=r;
    }
   
  void execute() override
    {
        rgb->on();
        led->on();

    }

    void undo() override
    {
        rgb->off();
        led->off();
    }

};

#endif