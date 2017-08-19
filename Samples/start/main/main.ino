#include "Arduino.h"
#include <Servo.h>
#include "Mtrack.h"
#include "Lcd.h"

#define I2C_ADDRESS 0x3C

Lcd lcd(I2C_ADDRESS);

char loading[] = "-\\|/";

void setup() {      
  lcd.init();
}

int index = 0;
int maxindex = 3;
void loop() {

if(index>maxindex){  index = 0;}
  lcd.text("9999999", String(loading[index]));
  //display(loading[index]);
  delay(100);
  index++;
 
} 

