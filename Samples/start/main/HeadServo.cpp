#include "Arduino.h"
#include "Lcd.h"
#include <Servo.h>
#include "HeadServo.h"

Servo _servoV;
Servo _servoH;
const char TOP[] = "Moving Top";
const char BOTTOM[] = "Moving Bottom";
const char RESET[] = "Reseting";

HeadServo::HeadServo(uint8_t pinVertical, uint8_t pinHorizontal, Lcd *lcd){
  _pinV = pinVertical;
  _pinH = pinHorizontal;
  _lcd = lcd;

  _servoV.attach(_pinV);
  _servoH.attach(_pinH);
}

void HeadServo::top(){ 
  _lcd->line3(TOP);
  
  _goToAngle(_servoV, 70);
  _goToAngle(_servoH, 0);
}


void HeadServo::reset(){ 
  _lcd->line3(RESET);
  _goToAngle(_servoV, 0);
  _goToAngle(_servoH, 0);
}

void HeadServo::bottom(){
  _lcd->line3(BOTTOM);
  _goToAngle(_servoH, 0);
  _goToAngle(_servoV, 0);
}


void HeadServo::_goToAngle(Servo s, byte finalAngle){
  
   byte currentAngle = s.read();
   if (finalAngle > currentAngle) {
      for (int i = currentAngle; i < finalAngle ; i++){
       s.write(i); 
       delay(5);  
      }
   }
   else {
     for (int i = currentAngle; i > finalAngle ; i--){
       s.write(i); 
       delay(5);   
     }
  }
}
