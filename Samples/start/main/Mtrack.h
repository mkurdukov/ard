#ifndef Mtrack_h
#define Mtrack_h

#include "Arduino.h"
#include "Lcd.h"
#include "Engine.h"

class Mtrack
{
  public:
    Mtrack(Engine* left, Engine* right, Lcd *lcd);
    void forward();
    void back();
    void stopEngine();
    void turnLeft();
    void turnRight();

  private:
    Engine *_left;
    Engine *_right;
    Lcd *_lcd;
};

#endif
