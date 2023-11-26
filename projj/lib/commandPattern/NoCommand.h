#include <Command.h>
#include <Arduino.h>
class NoCommand : public Command
{
private:
public:
    NoCommand() {}

    void execute() override
    {
    }

    void undo() override
    {
    }
};