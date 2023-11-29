#ifndef TOGGLABLE_H
#define TOGGLABLE_H

class Togglable {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void toggle() = 0;

    virtual ~Togglable() {} // Virtual destructor for proper polymorphic destruction
};

#endif
