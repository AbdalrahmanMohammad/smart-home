#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer
{
private:
    unsigned long previous;
    unsigned long duration;

public:
    Timer(unsigned long dur)
    {
        duration = dur*1000;
        previous = 0UL;
    }

    void setPrevious(unsigned long prv)
    {
        previous = prv;
    }

    void setDuration(unsigned long dur)
    {
        duration = dur;
    }

    unsigned long getPrevious()
    {
        return previous;
    }

    unsigned long getDuration()
    {
        return duration;
    }

    boolean clause()
    {

     if (getDuration() > 0UL && (millis()-getPrevious())>getDuration())
     {
        setPrevious(millis());
        return true;
     }
        return false;
    }
};

#endif
