#include "Arduino.h"
#include <Servo.h>
#include "Mtrack.h"
#include "Lcd.h"
#include "Engine.h"
//#include "Echo.h"
#include "Obstacle.h"
#include "HeadServo.h"
#include <avr/wdt.h>

#define I2C_ADDRESS 0x3C

const int PWM_A = 3, DIR_A = 12, BRAKE_A = 9, SNS_A = A0; //Engine left
const int PWM_B = 11, DIR_B = 13, BRAKE_B = 8, SNS_B = A1; //Engine right
//const int FRONT_ECHO_PIN = 2, FRONT_TRIG_PIN = 4;
const int OBSTACLE_PIN = 7;
const int DELAY_AFTER_LOOP_FINISHED = 200;
const int SERVO_VERTICAL_PIN = 5, SERVO_HORIZONTAL_PIN = 6;

//const int MAX_FRONT_DISTANCE_CM = 20;

Lcd *lcd;
Mtrack *tr;
Engine *left;
Engine *right;
//Echo *frontEcho;
Obstacle *obstacle;
HeadServo *head;
int forwardDistance = 0;
boolean turningLeft = false;
boolean movingforward = false;
int incomingByte = 0;

char STARTING[] = "Starting!";

void setup() {      
  Serial.begin(9600);
  Serial.println("Starting");
  lcd = new Lcd(I2C_ADDRESS);
  lcd->init();
  lcd->line1(STARTING);
  left =    new Engine(PWM_A, DIR_A,BRAKE_A, SNS_A, false);
  right =   new Engine(PWM_B, DIR_B,BRAKE_B, SNS_B, true);
  tr = new Mtrack(left, right, lcd);
  //frontEcho = new Echo(FRONT_ECHO_PIN, FRONT_TRIG_PIN, lcd);
  obstacle = new Obstacle(OBSTACLE_PIN);
  head = new HeadServo(SERVO_VERTICAL_PIN, SERVO_HORIZONTAL_PIN,lcd);
  //head->reset();
  wdt_enable(WDTO_4S);//8
  
}



void loop() {
    if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte);
        }

  if(incomingByte == 53) //5
  {
    head->top();  
  }

  if(incomingByte == 54) //6
  {
    head->bottom();  
  }
  

    bool isObstacle = obstacle->isObstacle();
    
    if(isObstacle){
      Serial.println("forwarding");
      if(!turningLeft){       tr->stopEngine();       }
      tr->turnLeft();
      movingforward = false;
      turningLeft = true;
    }
    else{
      Serial.println("left");
      if(!movingforward){ tr->stopEngine(); tr->forward(); }
      turningLeft = false;
      movingforward = true;
    }
  Serial.println("New Loop");
  wdt_reset();
  delay(100);
  wdt_reset();
}
