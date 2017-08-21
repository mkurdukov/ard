#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine {
  public:
    Engine(uint8_t pwm, uint8_t dir, uint8_t brake, uint8_t sns);
    void forward();
    void back();
    void stopMe();  
    void updateSpeed(uint8_t speedValue);
    void disable();
    void enable();
  private:  
    uint8_t _pwm;
    uint8_t _dir;
    uint8_t _brake;
    uint8_t _sns;
    uint8_t _speedValue;
    boolean _disabled;
};

#endif
