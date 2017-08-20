#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine {
  public:
    Engine(uint8_t pwm, uint8_t dir, uint8_t br);
    void forward();
    void back();
    void stopMe();  
  private:  
    uint8_t _pwm;
    uint8_t _dir;
    uint8_t _br;
};

#endif
