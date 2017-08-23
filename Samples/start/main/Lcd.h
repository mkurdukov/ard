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
    
    void line1(const char t[]);
    void line2(const char t[]);
    void line3(const char t[]);
    void line4(const char t[]);

    char *convertToCharArray(int value);

  private:
    void line(uint8_t number, const char t[]);
    uint8_t _address;
    SSD1306AsciiAvrI2c _oled;
    char *_convertToCharArray(int i, char *p);
};

#endif
