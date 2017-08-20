#include "Arduino.h"
#include "Mtrack.h"
#include "Lcd.h"

#include "Engine.h"

Mtrack::Mtrack(Engine* left, Engine* right, Lcd *lcd)
{
 // pinMode(pinLeft, OUTPUT);
 _left= left;
 _right = right;
  _lcd = lcd;
  _lcd->text("Starting");
}

void Mtrack::forward()
{
  _left->forward();
  _right->forward();
  _lcd->text("forward");
}

void Mtrack::back()
{
  _left->back();
  _right->back();

  _lcd->text("back");
}

void Mtrack::stopEngine()
{
  
  _left->stopMe();
  _right->stopMe();

  _lcd->text("stop");
}

void Mtrack::turnLeft()
{
  _left->forward();
  _right->back();

  _lcd->text("Turning l");
}

void Mtrack::turnRight()
{
  _left->back();
  _right->forward();

 _lcd->text("Turning r");
}
