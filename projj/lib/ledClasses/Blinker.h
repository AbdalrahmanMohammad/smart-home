#ifndef Blinker_h
#define Blinker_h

#include "LedClass.h"

class Blinker // or we can make attribue called period and make setter for it and make blink without parameters
{
private:
    LedClass led;
    unsigned long previous;
    unsigned long current;

    
public:
    Blinker() {} // do not use
    Blinker(LedClass &led) // i tried Blinker(LedClass &led) and worked but this is better
    {
      this->led=led;
      previous=millis();
      current=millis();
      }

    void blink(unsigned long period)
    {
      current=millis();
      if(current-previous>=period)
    {
      led.toggle();
      previous=millis();
      }
      
      }
};

#endif
