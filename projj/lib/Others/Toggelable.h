#ifndef TOGGLABLE_H
#define TOGGLABLE_H

class Togglable {
public:
    bool btnprevstate;// to toggle the led using button
    bool btncurstate;// to toggle the led using button
    unsigned long previous;  // for button debounce (has nothing to do with the timer)
    unsigned long duration;  // for timer (how many seconds to toggle)
    unsigned long startTime; // when i sat the timer

        virtual boolean getBtnprevstate()
    {
        return btnprevstate;
    }
    virtual void setBtnprevstate(boolean s)
    {
        btnprevstate = s;
    }
    virtual boolean getBtncurvstate()
    {
        return btncurstate;
    }
    virtual void setBtncurstate(boolean s)
    {
        btncurstate = s;
    }

     virtual unsigned long getStartTime()
    {
        return startTime;
    }
    virtual void setStartTime(unsigned long s)
    {
        startTime = s;
    }
    virtual unsigned long getPrevious()
    {
        return previous;
    }
    virtual void setPrevious(unsigned long s)
    {
        previous = s;
    }
    virtual unsigned long getDuration()
    {
        return duration;
    }
    virtual void setDuration(unsigned long s)
    {
        duration = s;
    }
    
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void toggle() = 0;

    virtual ~Togglable() {} // Virtual destructor for proper polymorphic destruction
};

#endif
