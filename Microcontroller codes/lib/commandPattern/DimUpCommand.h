#ifndef DIM_UP_COMMAND
#define DIM_UP_COMMAND


#include <Command.h>
#include <Arduino.h>
#include <RGB.h>

class DimUpCommand : public Command
{
private:
    RGB* rgb;

public:
    DimUpCommand(RGB* r) : rgb(r) {}

    void execute() override
    {
        rgb->brightnessup();
    }

    void undo() override
    {
        rgb->brightnessdown();
    }
};

#endif