#ifndef MACRO_COMMAND
#define MACRO_COMMAND

#include <Command.h>
#include <Arduino.h>

class MacroCommand : public Command
{
private:
    Command **commands;// this how we declare array pointer
    int numCommands;

public:
    MacroCommand(Command **commands, int numCommands) : commands(commands), numCommands(numCommands) {}

    void execute() override
    {
        for (int i = 0; i < numCommands; i++)
        {
            commands[i]->execute();
        }
    }

    void undo() override
    {
        for (int i = numCommands - 1; i >= 0; i--)
        {
            commands[i]->undo();
        }
    }
};

#endif