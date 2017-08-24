#include "Arduino.h"
#include <Servo.h>
#include "Mtrack.h"
#include "Lcd.h"
#include "Engine.h"
#include "Echo.h"

#define I2C_ADDRESS 0x3C

const int PWM_A = 3, DIR_A = 12, BRAKE_A = 9, SNS_A = A0; //Engine left
const int PWM_B = 11, DIR_B = 13, BRAKE_B = 8, SNS_B = A1; //Engine right
const int FRONT_ECHO_PIN = 7, FRONT_TRIG_PIN = 4;
const int DELAY_AFTER_LOOP_FINISHED = 200;

const int MAX_FRONT_DISTANCE_CM = 20;

Lcd *lcd;
Mtrack *tr;
Engine *left;
Engine *right;
Echo *frontEcho;
int forwardDistance = 0;
boolean turningLeft = false;
boolean movingforward = false;

//char loading[] = "-\\|/";
char STARTING[] = "Starting!";

void setup() {      
  Serial.begin(9600);
  lcd = new Lcd(I2C_ADDRESS);
  lcd->init();
  left =    new Engine(PWM_A, DIR_A,BRAKE_A, SNS_A);
  right =   new Engine(PWM_B, DIR_B,BRAKE_B, SNS_B);
  tr = new Mtrack(left, right, lcd);
  frontEcho = new Echo(FRONT_ECHO_PIN, FRONT_TRIG_PIN, lcd);
  lcd->line1(STARTING);
}

void loop() {
  forwardDistance = frontEcho->getDistance();
  if(forwardDistance <= MAX_FRONT_DISTANCE_CM){
    if(!turningLeft){       tr->stopEngine();       }
    tr->turnLeft();
    movingforward = false;
    turningLeft = true;
  }
  else{
    if(!movingforward){ tr->stopEngine(); tr->forward(); }
    turningLeft = false;
    movingforward = true;
  }
  delay(DELAY_AFTER_LOOP_FINISHED);
}
