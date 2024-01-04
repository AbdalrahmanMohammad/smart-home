#ifndef SPEED_UP_COMMAND
#define SPEED_UP_COMMAND


#include <Command.h>
#include <Arduino.h>
#include <Fan.h>

class SpeedUpCommand : public Command
{
private:
    Fan* fan;

public:
    SpeedUpCommand(Fan* f) : fan(f) {}

    void execute() override
    {
        fan->speedUp();
    }

    void undo() override
    {
        fan->speedDown();
    }
};

#endif