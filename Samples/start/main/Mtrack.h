#ifndef Mtrack_h
#define Mtrack_h

#include "Arduino.h"

class Mtrack
{
  public:
    Mtrack(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};

#endif
