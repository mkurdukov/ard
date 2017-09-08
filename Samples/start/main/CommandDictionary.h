#ifndef CommandDictionary_h
#define CommandDictionary_h

#include "Arduino.h"
//https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html

class CommandDictionary {
  public:
    CommandDictionary(bool sendToSerial);
    void readNext();
    bool forward();
    bool back();
    bool stopMe();  
    bool left();
    bool right();
    bool headTop();
    bool headBottom();
    
  private:  
    void _message(String message);
    bool _cmd(int expected);
    uint8_t _lastCommand;
    bool _sendToSerial;
    int _incomingByte;

    const int CMD_STOP = 83;      //"S"
    const int CMD_FORWARD = 70;   //"F"
    const int CMD_BACK = 66;      //"B"
    const int CMD_LEFT = 76;      //"L"    
    const int CMD_RIGHT = 82;     //"R"    
    
    const int CMD_HEAD_TOP = 116;  //"t"
    const int CMD_HEAD_BOTTOM = 98;//"b"
};

#endif
