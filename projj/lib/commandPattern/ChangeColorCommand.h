#ifndef CHANGE_COLOR_COMMAND_H
#define CHANGE_COLOR_COMMAND_H

#include <Command.h>
#include <Arduino.h>
#include <RGB.h>

class ChangeColorCommand : public Command
{
private:
    RGB *rgb;
    int previousRed;
    int previousGreen;
    int previousBlue;
    int newRed;
    int newGreen;
    int newBlue;

public:
    ChangeColorCommand(RGB *r) : rgb(r), previousRed(0), previousGreen(0), previousBlue(0), newRed(0), newGreen(0), newBlue(0) {}

    void execute() override
    {
        previousRed = newRed;
        previousGreen = newGreen;
        previousBlue = newBlue;

        newRed = rgb->getRed();
        newGreen = rgb->getGreen();
        newBlue = rgb->getBlue();

        rgb->setAll(newRed, newGreen, newBlue);
    }

    void undo() override
    {
        rgb->setAll(previousRed, previousGreen, previousBlue);
        previousRed = newRed;
        previousGreen = newGreen;
        previousBlue = newBlue;
        newRed = rgb->getRed();
        newGreen = rgb->getGreen();
        newBlue = rgb->getBlue();
    }
};

#endif