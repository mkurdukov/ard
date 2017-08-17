#include "Arduino.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#ifndef Lcd_h
#define Lcd_h


class Lcd
{
  public:
    Lcd(uint8_t address);
    void init();
    void text(char ch);
    void text(String line1);
    void text(String line1,String line2);
    void text(String line1,String line2,String line3);
    void text(String line1,String line2,String line3,String line4);
  private:
    uint8_t _address;
    SSD1306AsciiAvrI2c _oled;
};

#endif
