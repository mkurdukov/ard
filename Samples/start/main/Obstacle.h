#ifndef Obstacle_h
#define Obstacle_h

#include "Arduino.h"

class Obstacle
{
  public:
    Obstacle(int maxDistanceToObstacleCm, int minDistanceToObstacleCm, uint8_t pinIk, uint8_t pinTrig, uint8_t pinEcho);
    bool isObstacle();
    int getDistance();
    int getLastDistance();
    bool isEcho();
    bool isIk();
    bool tooClose();

  private:
    int _getDistance();
    uint8_t _pinIk;
    uint8_t _pinTrig; 
    uint8_t _pinEcho;
    int _maxDistanceToObstacleCm;
    int _minDistanceToObstacleCm;
    int _distance;
    bool _ikObstacle;
    bool _tooClose;
    bool _isEcho;
    long _duration;
};

#endif
