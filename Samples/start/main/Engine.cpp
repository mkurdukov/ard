#include "Arduino.h"
#include "Engine.h"

Engine::Engine(uint8_t pwm, uint8_t dir, uint8_t brake, uint8_t sns){
  _pwm = pwm;
  _dir = dir;
  _brake = brake;
  _sns = sns;
  _speedValue = 255;
  pinMode(_brake, OUTPUT);
  pinMode(_dir, OUTPUT);
}

void Engine::forward(){ 
    digitalWrite(this->_brake, LOW);
  digitalWrite(this->_dir, HIGH);
  analogWrite(this->_pwm, _speedValue);
}

void Engine::back(){
  digitalWrite(this->_brake, LOW);
  digitalWrite(this->_dir, LOW);
  analogWrite(this->_pwm, _speedValue);  
}

void Engine::stopMe(){    
  digitalWrite(this->_brake, HIGH);  
  analogWrite(this->_pwm, 0); 
}

void Engine::updateSpeed(uint8_t speedValue){
  this->_speedValue = speedValue;  
}
