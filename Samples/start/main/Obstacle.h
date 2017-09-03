#ifndef Obstacle_h
#define Obstacle_h

#include "Arduino.h"

class Obstacle
{
  public:
    Obstacle(int maxDistanceToObstacleCm, uint8_t pinIk, uint8_t pinTrig, uint8_t pinEcho);
    bool isObstacle();
    int getDistance();
    int getLastDistance();
    bool isEcho();
    
  private:
    int _getDistance();
    uint8_t _pinIk;
    uint8_t _pinTrig; 
    uint8_t _pinEcho;
    int _maxDistanceToObstacleCm;
    int _distance;
    bool _isEcho;
    long _duration;
};

#endif
