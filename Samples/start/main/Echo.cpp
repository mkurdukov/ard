#include "Arduino.h"
#include "Echo.h"

Echo::Echo(uint8_t echoPin, uint8_t trigPin, Lcd *lcd){
  _echoPin = echoPin;
  _trigPin = trigPin;
  _lcd = lcd;
  _distance = 0;
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

// takes about 14- 15 microseconds to read
int Echo::getDistance(){
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  _distance = pulseIn(_echoPin, HIGH)*0.034/2;

  _lcd->line4(_lcd->convertToCharArray(_distance));
  
  return _distance;
}

