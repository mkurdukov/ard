#ifndef Obstacle_h
#define Obstacle_h

#include "Arduino.h"

class Obstacle
{
  public:
    Obstacle(uint8_t pin);
    void init();
    bool isObstacle();
  private:
    uint8_t _pin;
};

#endif
