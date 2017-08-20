#include "Arduino.h"
#include <Servo.h>
#include "Mtrack.h"
#include "Lcd.h"
#include "Engine.h"

#define I2C_ADDRESS 0x3C
#define leftEnginePin 

// Engine Left
#define PWM_A 3
#define DIR_A 12
#define BRAKE_A 9
#define SNS_A A0
// Engine Right
#define PWM_B 9
#define DIR_B 13
#define BRAKE_B 8
#define SNS_B A1

Lcd *lcd;
Mtrack *tr;
Engine *left;
Engine *right;

char loading[] = "-\\|/";

void setup() {      
  lcd = new Lcd(I2C_ADDRESS);
  lcd->init();
  left =    new Engine(PWM_A, DIR_A,BRAKE_A, SNS_A);
  right =   new Engine(PWM_B,DIR_B,BRAKE_B, SNS_B);
  tr = new Mtrack(left, right, lcd);
}

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
