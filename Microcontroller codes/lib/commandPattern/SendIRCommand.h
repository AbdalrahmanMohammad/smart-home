#ifndef SendIRCommand_H
#define SendIRCommand_H

#include <Command.h>
#include <Arduino.h>
#include <TV.h>

class SendIRCommand : public Command
{
private:
    TV *tv;
    String button;
    String prevButton;

public:
    SendIRCommand(TV *t) : tv(t)
    {
        button = "";
        prevButton = "";
    }

    void execute() override
    {
        prevButton = button;
        button = tv->getButton();
         if (button == "on")
            prevButton = "off";
        else if (button == "off")
            prevButton = "on";
        else if (button == "toggle")
            prevButton = "toggle";
        else if (button == "volup")
            prevButton = "voldown";
        else if (button == "voldown")
            prevButton = "volup";

        tv->sendSignal(button);
    }

    void undo() override // works just for one signal(can't go from 12 to 13 and back (just one signal))
    {                   // no undo for channel up or down just for numbers and volume and on off
        tv->sendSignal(prevButton);
        String temp = prevButton;
        prevButton = button;
        button = temp;
    }
};

#endif