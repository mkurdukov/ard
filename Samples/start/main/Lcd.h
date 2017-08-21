#ifndef Lcd_h
#define Lcd_h


//https://github.com/greiman/SSD1306Ascii thank you man!
#include "Arduino.h"
#include "SSD1306Ascii.h"
#include "lcd/SSD1306AsciiAvrI2c.h"



class Lcd
{
  public:
    Lcd(uint8_t address);
    void init();
    
    void line1(char t[]);
    void line2(char t[]);
    void line3(char t[]);
    void line4(char t[]);

  private:
    void line(uint8_t number, char t[]);
    uint8_t _address;
    SSD1306AsciiAvrI2c _oled;
};

#endif
