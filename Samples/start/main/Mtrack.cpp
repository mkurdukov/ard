#include "Arduino.h"
#include "Mtrack.h"

Mtrack::Mtrack(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Mtrack::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Mtrack::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
