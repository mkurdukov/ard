#include <SPI.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define SSD1306_LCDHEIGHT 64


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int textSize = 2;
int index = 0;
int tindex = 0;
int mSize = 6;
int tSize = 7;
const char t[]= "|/-\\|/-";

void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
}

void loop() {

  if(index<0 || index>=mSize){index = 0;}
  if(tindex<0 || tindex>=tSize){tindex = 0;}
  if(textSize == 0 || textSize >= 5) {   textSize = 1;   }
  showText(textSize, "", t[tindex]);
  //showText(textSize, "", t[tindex]);
  index++;
  tindex++;
  delay(100);
  Serial.println(index);
}

void showText(int s, String text, char c){
  display.clearDisplay();
  display.setTextSize(s);
  display.setTextColor(WHITE);
 
  display.setCursor(0,0);
  display.print(text + "\nColor\n" + c);
  display.display();
}
