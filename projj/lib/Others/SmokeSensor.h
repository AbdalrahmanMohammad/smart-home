#ifndef SMOKESENSOR_h
#define SMOKESENSOR_h

#include <Arduino.h>

class SmokeSensor
{
private:
    byte pin;
    byte buzzerPin;
    bool buzzerState;

public:
    SmokeSensor(byte pin, byte buzzerPin)
    {
        this->pin = pin;
        this->buzzerPin = buzzerPin;
        buzzerState = false;
    }

    void init()
    {
        pinMode(buzzerPin, OUTPUT);
        digitalWrite(buzzerPin, LOW);
        pinMode(pin, INPUT);
    }

    int sensorValue()
    {
        return analogRead(pin);
    }

    boolean thereIsFire()
    {
        // Serial.println(analogRead(pin));
        if (analogRead(pin) > 3000){
            return true;
        }
        else
            return false;
    }

    void startAlarm()
    {
        if (buzzerState == false)
        {
            digitalWrite(buzzerPin, HIGH);
            buzzerState = true;
        }
    }

    void endAlarm()
    {
        if (buzzerState == true)
        {
            digitalWrite(buzzerPin, LOW);
            buzzerState = false;
        }
    }

    bool ison()
    {
        return buzzerState;
    }
};

#endif
