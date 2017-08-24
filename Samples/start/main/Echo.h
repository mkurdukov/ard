#ifndef Echo_h
#define Echo_h

#include "Arduino.h"
#include "Lcd.h"

class Echo {
  public:
    Echo(uint8_t echoPin, uint8_t trigPin, Lcd *lcd);
    int getDistance();
  private:  
    uint8_t _echoPin;
    uint8_t _trigPin;
    int _distance;
    Lcd *_lcd;
    int _getDistance();
};

#endif
