#ifndef RGB_TOGGLE_COMMAND_H
#define RGB_TOGGLE_COMMAND_H

#include <Command.h>
#include <Arduino.h>
#include <RGB.h>

class RgbToggleCommand : public Command
{
private:
    RGB* rgb;

public:
    RgbToggleCommand(RGB* r) : rgb(r) {}

    void execute() override
    {
        rgb->toggle();
    }

    void undo() override
    {
        rgb->toggle();
    }
};
#endif