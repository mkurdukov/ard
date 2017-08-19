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

void Lcd::text(char ch)
{
 text(String(ch), "", "", "");
}

void Lcd::text(String line1)
{
text(line1, "", "", "");
}

void Lcd::text(String line1,String line2)
{
text(line1, line2, "", "");
}

void Lcd::text(String line1,String line2,String line3)
{
  text(line1, line2, line3, "");
}

void Lcd::text(String line1,String line2,String line3,String line4)
{
  _oled.clear();  
  _oled.println(line1);
  _oled.println(line2);
  _oled.println(line3);
  _oled.println(line4);
}
