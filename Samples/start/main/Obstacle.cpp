#include "Arduino.h"
#include "Obstacle.h"

Obstacle::Obstacle(int maxDistanceToObstacleCm, uint8_t pinIk, uint8_t pinTrig, uint8_t pinEcho)
{
  _pinIk = pinIk;
  _pinTrig=pinTrig;
  _pinEcho=pinEcho;
  _maxDistanceToObstacleCm = maxDistanceToObstacleCm;

  pinMode(_pinIk, INPUT);
  pinMode(_pinTrig, OUTPUT);
  pinMode(_pinEcho, INPUT);
}

bool Obstacle::isObstacle(){ 
  _getDistance();
  if(_distance == 0) {
    _isEcho = false;
    return digitalRead(_pinIk);
  }
  _isEcho = true;
  return _distance<=_maxDistanceToObstacleCm;
}

int Obstacle::getDistance(){
  return _getDistance();
}

int Obstacle::getLastDistance(){
  return _distance;
}

bool Obstacle::isEcho(){
  return _isEcho;
}

int Obstacle::_getDistance(){
  digitalWrite(_pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(_pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_pinTrig, LOW);
  _duration = pulseIn(_pinEcho, HIGH);
  _distance = _duration*0.034/2;

  return _distance;
}
