#include "Arduino.h"
#include "Mtrack.h"
#include "Lcd.h"

#include "Engine.h"

Mtrack::Mtrack(Engine* left, Engine* right, Lcd *lcd)
{
 _left= left;
 _right = right;
  _lcd = lcd;
  char b[] = "Starting";
  _lcd->line1(b);
}

void Mtrack::forward()
{
  _left->forward();
  _right->forward();
  char f[] = "forward";
  _lcd->line1(f);
}

void Mtrack::back()
{
  _left->back();
  _right->back();
char f[] = "back";
  
  _lcd->line1(f);
}

void Mtrack::stopEngine()
{
  
  _left->stopMe();
  _right->stopMe();
char f[] = "stop";
  _lcd->line1(f);
}

void Mtrack::turnLeft()
{
  _left->forward();
  _right->back();
char f[] = "Turning l";
  _lcd->line1(f);
}

void Mtrack::turnRight()
{
  _left->back();
  _right->forward();
char f[] = "Turning r";
 _lcd->line1(f);
}
