#include "Arduino.h"
#include <Servo.h>
#include "Mtrack.h"
#include "Lcd.h"
#include "Engine.h"
#include "Echo.h"

#define I2C_ADDRESS 0x3C

const int PWM_A = 3, DIR_A = 12, BRAKE_A = 9, SNS_A = A0; //Engine left
const int PWM_B = 11, DIR_B = 13, BRAKE_B = 8, SNS_B = A1; //Engine right
const int FRONT_ECHO_PIN = 2, FRONT_TRIG_PIN = 4;

Lcd *lcd;
Mtrack *tr;
Engine *left;
Engine *right;
Echo *frontEcho;

//char loading[] = "-\\|/";

void setup() {      
  lcd = new Lcd(I2C_ADDRESS);
  lcd->init();
  left =    new Engine(PWM_A, DIR_A,BRAKE_A, SNS_A);
  right =   new Engine(PWM_B, DIR_B,BRAKE_B, SNS_B);
  tr = new Mtrack(left, right, lcd);
  frontEcho = new Echo(FRONT_ECHO_PIN, FRONT_TRIG_PIN, lcd);
}

void loop() {
  frontEcho->getDistance();
  tr->forward();
  delay(2000);
  tr->back();
  frontEcho->getDistance();
  delay(2000);
  tr->turnLeft();
  frontEcho->getDistance();
  delay(2000);
  tr->turnRight();
  frontEcho->getDistance();
  delay(2000);
  tr->stopEngine();
  frontEcho->getDistance();
  delay(1000);
}
