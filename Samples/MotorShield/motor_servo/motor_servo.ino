#include <Servo.h>

Servo s1;
Servo s2;

const int 
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9,
SNS_A   = A0,//Don't really understand this
PWM_B   = 11,
DIR_B   = 13,
BRAKE_B = 8,
SNS_B   = A1;//Don't really understand this

int sPos = 0;

void setup() {
  // Configure the A output
  configureMotor(BRAKE_A, DIR_A);
  configureMotor(BRAKE_B, DIR_B);

  s1.attach(5);
  s2.attach(6);
  

  // Open Serial communication
  Serial.begin(9600);
  Serial.println("Motor shield DC motor Test:\n");
}

void loop() {


  for(sPos = 0; sPos<180; sPos++){
    s1.write(sPos);
    s2.write(sPos);
    delay(10);
    
    }

      for(sPos = 180; sPos>0; sPos--){
    s1.write(sPos);
    s2.write(sPos);
    delay(10);
    
    }

  //testMotors();

s1.detach();
    s2.detach();
  
  while(1);
}


void testMotors(){
  moveForward(255);
  delay(1000);
  moveForward(100);
  delay(1000);

  moveBack(100);
  delay(1000);
  moveBack(255);
  delay(1000);

  stop();
}


void stop(){
  analogWrite(PWM_A, 0); 
  analogWrite(PWM_B, 0); 
}


void moveBack(int speedValue){
  setBackMotor(BRAKE_A, DIR_A, PWM_A, speedValue);
  setBackMotor(BRAKE_B, DIR_B, PWM_B, speedValue);
}


void setBackMotor(int breakPin, int dir, int speedPin, int speedValue){
  digitalWrite(breakPin, LOW);  // setting againg the brake LOW to disable motor brake
  digitalWrite(dir, LOW);    // now change the direction to backward setting LOW the DIR_A pin

  analogWrite(speedPin, speedValue);     // Set the speed of the motor
}

void moveForward(int speedValue){
  setForwardMotor(BRAKE_A, DIR_A, PWM_A, speedValue);
  setForwardMotor(BRAKE_B, DIR_B, PWM_B, speedValue);
}

void setForwardMotor(int breakPin, int dir, int speedPin, int speedValue){
  digitalWrite(breakPin, LOW);  // setting brake LOW disable motor brake
  digitalWrite(dir, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(speedPin, speedValue);     // Set the speed of the motor, 255 is the maximum value
}

void configureMotor(int breakPin, int dir){
  pinMode(breakPin, OUTPUT);  // Brake pin on channel A
  pinMode(dir, OUTPUT);    // Direction pin on channel A
}


