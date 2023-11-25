#include <Command.h>
#include <Arduino.h>
#include <LedClass.h>

class LedToggleCommand : public Command
{
private:
    LedClass* led;

public:
    LedToggleCommand(LedClass* l) : led(l) {}

    void execute() override
    {
        led->toggle();
    }

    void undo() override
    {
        led->toggle();
    }
};