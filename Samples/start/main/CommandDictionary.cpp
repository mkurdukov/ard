#include "Arduino.h"
#include "CommandDictionary.h"

CommandDictionary::CommandDictionary(bool sendToSerial){
  _sendToSerial = sendToSerial;
  _lastCommand = 0;
  _incomingByte = -1;
  Serial.begin(9600);
}

void CommandDictionary::readNext(){ 
  if (Serial.available() > 0) {
    _incomingByte = Serial.read();
    //Serial.print("I received: ");
    //Serial.println(_incomingByte);
    return true;
  }

  return false;
}


void CommandDictionary::_message(String message){    if(_sendToSerial){  Serial.println(message);}  }

bool CommandDictionary::forward(){ return _cmd(CMD_FORWARD); }
bool CommandDictionary::back(){ return _cmd(CMD_BACK); }
bool CommandDictionary::stopMe(){ return _cmd(CMD_STOP); }
bool CommandDictionary::left(){ return _cmd(CMD_LEFT); }
bool CommandDictionary::right(){ return _cmd(CMD_RIGHT); }
bool CommandDictionary::headTop(){ return _cmd(CMD_HEAD_TOP); }
bool CommandDictionary::headBottom(){ return _cmd(CMD_HEAD_BOTTOM); }

bool CommandDictionary::_cmd(int expected){ 
  Serial.println(expected);
  return _incomingByte == expected;
}
