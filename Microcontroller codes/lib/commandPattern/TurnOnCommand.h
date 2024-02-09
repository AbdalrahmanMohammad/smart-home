#ifndef Turn_On_Command_H
#define Turn_On_Command_H

#include <Command.h>
#include <Toggelable.h>

class TurnOnCommand : public Command
{
private:
    Togglable *device;

public:
    TurnOnCommand(Togglable *d)
    {
        device = d;
    }

    void execute() override
    {
        device->on();
    }

    void undo() override
    {
        device->off();
    }
};

#endif