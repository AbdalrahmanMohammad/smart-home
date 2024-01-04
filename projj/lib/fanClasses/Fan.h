#ifndef Fan_h
#define Fan_h

#include <Arduino.h>
#include <Toggelable.h>

class Fan : public Togglable
{
private:
    byte pin;
    boolean state;
    int speed;

public:
    Fan(byte pin)
    {
        this->pin = pin;
        state = LOW;
        speed = 255;
    }

    virtual void init()
    {
        pinMode(pin, OUTPUT);
    }
    virtual void init(byte defaultState)
    {
        init();
        if (defaultState == HIGH)
        {
            on();
        }
        else
        {
            off();
        }
    }

    virtual void on() override
    {
        speed = 255;
        analogWrite(pin, speed);
        state = HIGH;
    }
    virtual void off() override
    {
        speed = 0;
        analogWrite(pin, speed);
        state = LOW;
    }

    virtual bool isOn()
    {
        return (state == HIGH);
    }

    virtual void toggle() override // you can just digialWrite(pin,!digitalRead(pin)); but this is better
    {
        if (isOn())
        {
            off();
        }
        else
        {
            on();
        }
    }
    virtual String getName()
    {
        return "fan";
    }

    virtual boolean checkIfNo() const // this function to let the invoker know that is not instance from NoFan
    {
        return false;
    }

    virtual void speedUp()
    {
        speed += 20;
        speed = (speed > 255) ? 255 : speed;
        speed = (speed < 140) ? 0 : speed; // in case we speed up while it is off
        // analogWrite(pin, 255);
        // delay(100);
        analogWrite(pin, speed);
    }

    virtual void speedDown()
    {
        speed -= 20;
        speed = (speed < 140) ? 140 : speed;
        // analogWrite(pin, 255);
        // delay(100);
        analogWrite(pin, speed);
    }
    virtual int getSpeed()
    {
        return speed;
    }
};

#endif
