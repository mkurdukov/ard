#ifndef HeadServo_h
#define HeadServo_h

#include "Arduino.h"

class HeadServo {
  public:
    HeadServo(uint8_t pinVertical, uint8_t pinHorizontal, Lcd *lcd);
    void reset();
    void top();
    void bottom();
  private:  
    uint8_t _pinV;
    uint8_t _pinH;
    Lcd *_lcd;
    void _goToAngle(Servo s, byte finalAngle);
};

#endif
