#include "Arduino.h"
#include "Engine.h"

Engine::Engine(uint8_t pwm, uint8_t dir, uint8_t brake, uint8_t sns, boolean inversed){
  _pwm = pwm;
  _dir = dir;
  _brake = brake;
  _sns = sns;
  _speedValue = 255;
  _disabled = false;
  _inversed = inversed;
  pinMode(_brake, OUTPUT);
  pinMode(_dir, OUTPUT);
}

void Engine::forward(){ 
  if(_disabled) { return; } 
    digitalWrite(this->_brake, LOW);
  digitalWrite(this->_dir, _inversed ? LOW : HIGH);
  analogWrite(this->_pwm, _speedValue);
}

void Engine::back(){
   if(_disabled) { return; }
  digitalWrite(this->_brake, LOW);
  digitalWrite(this->_dir, _inversed ? HIGH : LOW);
  analogWrite(this->_pwm, _speedValue);  
}

void Engine::stopMe(){   
   if(_disabled) { return; } 
  digitalWrite(this->_brake, HIGH);  
  analogWrite(this->_pwm, 0); 
}

void Engine::updateSpeed(uint8_t speedValue){
  this->_speedValue = speedValue;  
}

void Engine::disable(){   _disabled = true; }

void Engine::enable(){   _disabled = false; }
