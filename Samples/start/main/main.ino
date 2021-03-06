#include "Arduino.h"
#include <Servo.h>
#include "Mtrack.h"
#include "Lcd.h"
#include "Engine.h"
#include "Obstacle.h"
#include "HeadServo.h"
#include "CommandDictionary.h"
#include <avr/wdt.h>

#define I2C_ADDRESS 0x3C

const int PWM_A = 3, DIR_A = 12, BRAKE_A = 9, SNS_A = A0; //Engine left
const int PWM_B = 11, DIR_B = 13, BRAKE_B = 8, SNS_B = A1; //Engine right
const int FRONT_ECHO_PIN = 4, FRONT_TRIG_PIN = 2;
const int OBSTACLE_PIN = 7;
const int DELAY_AFTER_LOOP_FINISHED = 100;
const int SERVO_VERTICAL_PIN = 5, SERVO_HORIZONTAL_PIN = 6;

const int MAX_FRONT_DISTANCE_CM = 40;
const int MIN_FRONT_DISTANCE_CM = 10;

Obstacle *obstacle;
Lcd *lcd;
Mtrack *tr;
Engine *left;
Engine *right;
CommandDictionary *cmd;

HeadServo *head;
int forwardDistance = 0;
boolean turningLeft = false;
boolean movingforward = false;
int incomingByte = 0;

char STARTING[] = "Starting!";

void setup() {      

  cmd = new CommandDictionary(false);
  obstacle = new Obstacle(MAX_FRONT_DISTANCE_CM, MIN_FRONT_DISTANCE_CM, OBSTACLE_PIN, FRONT_TRIG_PIN, FRONT_ECHO_PIN);
  
  lcd = new Lcd(I2C_ADDRESS);
  lcd->line1(STARTING);
  left =    new Engine(PWM_A, DIR_A,BRAKE_A, SNS_A, false);
  right =   new Engine(PWM_B, DIR_B,BRAKE_B, SNS_B, true);
  tr = new Mtrack(left, right, lcd);
  head = new HeadServo(SERVO_VERTICAL_PIN, SERVO_HORIZONTAL_PIN,lcd);
  wdt_enable(WDTO_4S);//8
}


void loop() {
  cmd->readNext();

    bool isObstacle = obstacle->isObstacle();
    Serial.print("Is Obstacle: ");
    Serial.print(isObstacle);
    Serial.print(" Is Echo: ");
    Serial.print(obstacle->isEcho());
    Serial.print(" distance: ");
    Serial.println(obstacle->getLastDistance());

    if(isObstacle){
      Serial.println("Go Left");
      if(!turningLeft){       tr->stopEngine();       }
      if(!obstacle->isEcho()){
        //TODO: Remove hardcoded delay!!!!
        tr->back();
        delay(1000);
        tr->turnLeft();
        delay(500);
      }
      tr->turnLeft();
      movingforward = false;
      turningLeft = true;
    }
    else{
      Serial.println("Go Forward");
      if(!movingforward){ tr->stopEngine(); tr->forward(); }
      turningLeft = false;
      movingforward = true;
    }
    
    Serial.println("New Loop");
    wdt_reset();
    delay(DELAY_AFTER_LOOP_FINISHED);
    wdt_reset();
}
