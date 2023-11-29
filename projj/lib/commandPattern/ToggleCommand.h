#ifndef TOGGLE_COMMAND
#define TOGGLE_COMMAND
#include <Command.h>
#include <Arduino.h>
#include <Toggelable.h>

class ToggleCommand : public Command
{
private:
    Togglable *device;

public:
    ToggleCommand(Togglable *l) : device(l) {}

    void execute() override
    {
        device->toggle();
    }

    void undo() override
    {
        device->toggle();
    }
};
#endif