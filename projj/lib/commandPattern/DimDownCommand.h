#ifndef DIM_DOWN_COMMAND
#define DIM_DOWN_COMMAND

#include <Command.h>
#include <Arduino.h>
#include <RGB.h>

class DimDownCommand : public Command
{
private:
    RGB* rgb;

public:
    DimDownCommand(RGB* r) : rgb(r) {}

    void execute() override
    {
        rgb->brightnessdown();
    }

    void undo() override
    {
        rgb->brightnessup();
    }
};

#endif