#include "Arduino.h"
#include "SSD1306Ascii.h"
#include "lcd/SSD1306AsciiAvrI2c.h"
#include "Lcd.h"

SSD1306AsciiAvrI2c _oled;

Lcd::Lcd(uint8_t address)
{
  _address = address;
}

void Lcd::init()
{
  //_oled.begin(&Adafruit128x64, _address);
  _oled.setFont(Adafruit5x7);  
  _oled.set2X();
}

void Lcd::line1(const char t[]){   line(0, t); }
void Lcd::line2(const char t[]){   line(2, t); }
void Lcd::line3(const char t[]){   line(4, t); }
void Lcd::line4(const char t[]){   line(6, t); }

void Lcd::line(uint8_t number, const char t[])
{
  /* TODO: is this a problem ?
  _oled.clear(0, _oled.displayWidth() - 1, number, number+1);
  
  _oled.setCursor(0, number);
  _oled.write(t);
  */
}

char *Lcd::convertToCharArray(int i){
  char *b = (char*)malloc(10 * sizeof(char));
  _convertToCharArray(i, b);
  return b;
}

char *Lcd::_convertToCharArray(int i, char *p){
  if (i / 10 == 0) {
    *p++ = i + '0';
    *p = '\0';
    return p;
  }

  p = _convertToCharArray(i / 10, p);
  *p++ = i % 10 + '0';
  *p = '\0';
  return p;
  }
