#include "Arduino.h"
#include "Engine.h"

Engine::Engine(uint8_t pwm, uint8_t dir, uint8_t br){
  _pwm = pwm;
  _dir = dir;
  _br = br;
}

void Engine::forward(){}
void Engine::back(){}
void Engine::stopMe(){}
