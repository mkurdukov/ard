#include "Arduino.h"
#include "Mtrack.h"
#include "Lcd.h"

#include "Engine.h"

const char FORWARD[] = "Forward";
const char BACK[] = "Back";
const char STOP[] = "Stop";
const char LEFT[] = "Left"; 
const char RIGHT[] = "Right";
const char START[] = "Start";


Mtrack::Mtrack(Engine* left, Engine* right, Lcd *lcd)
{
 _left= left;
 _right = right;
  _lcd = lcd;
  _lcd->line1(START);
}

void Mtrack::forward()
{
  _left->forward();
  _right->forward();
  _lcd->line1(FORWARD);
  _lcd->line2(FORWARD);
}

void Mtrack::back()
{
  _left->back();
  _right->back();
  _lcd->line1(BACK);
  _lcd->line2(BACK);
}

void Mtrack::stopEngine()
{
  
  _left->stopMe();
  _right->stopMe();
  _lcd->line1(STOP);
  _lcd->line2(STOP);
}

void Mtrack::turnLeft()
{
  _left->forward();
  _right->back();
  _lcd->line1(FORWARD);
  _lcd->line2(BACK);
}

void Mtrack::turnRight()
{
  _left->back();
  _right->forward();
  _lcd->line1(BACK);
  _lcd->line2(FORWARD);

}
