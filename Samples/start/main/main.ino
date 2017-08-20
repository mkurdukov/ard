#include "Arduino.h"
#include <Servo.h>
#include "Mtrack.h"
#include "Lcd.h"
#include "Engine.h"

#define I2C_ADDRESS 0x3C
#define leftEnginePin 


#define PWM_A 3
/*
#define 
DIR_A   = 12,
BRAKE_A = 9,
SNS_A   = A0,//Don't really understand this
PWM_B   = 11,
DIR_B   = 13,
BRAKE_B = 8,
SNS_B   = A1;//Don't really understand this


int lPin = 1;
int rPin = 2;

*/
Lcd *lcd;
Mtrack *tr;
Engine *left;
Engine *right;

char loading[] = "-\\|/";

void setup() {      
  lcd = new Lcd(I2C_ADDRESS);
  lcd->init();
  left = new Engine(1,1,1);
  right = new Engine(1,1,1);
  tr = new Mtrack(left, right, lcd);
}

int index = 0;
int maxindex = 3;
void loop() {

tr->forward();
delay(1000);
tr->back();
delay(1000);
tr->turnLeft();
delay(1000);
tr->turnRight();
delay(1000);
tr->stopEngine();
delay(1000);


}
