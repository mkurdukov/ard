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
  _oled.begin(&Adafruit128x64, _address);
  _oled.setFont(Adafruit5x7);  
  _oled.set2X();
 
}

void Lcd::line1(char t[]){   line(0, t); }
void Lcd::line2(char t[]){   line(2, t); }
void Lcd::line3(char t[]){   line(4, t); }
void Lcd::line4(char t[]){   line(6, t); }

void Lcd::line(uint8_t number, char t[])
{
  _oled.setCursor(0, number);
  _oled.write(t);
}
