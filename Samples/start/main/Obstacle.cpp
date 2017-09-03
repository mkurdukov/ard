#include "Arduino.h"
#include "Obstacle.h"

Obstacle::Obstacle(uint8_t pin)
{
  _pin = pin;
}

void Obstacle::init()
{
  pinMode(_pin, INPUT);
}

bool Obstacle::isObstacle(){ return digitalRead(_pin); }
