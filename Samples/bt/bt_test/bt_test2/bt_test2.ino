char command;
String string;
boolean ledon = false;
int incomingByte = 0;

  void setup()
  {
    Serial.begin(9600);
      pinMode(LED_BUILTIN, OUTPUT);
  }

  void loop()
  {
    if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte);
        }
    
    if(incomingByte == 53)
    {
        digitalWrite(LED_BUILTIN, HIGH); 
        ledon = true;
        //Serial.println(string);
    }
    
    if(incomingByte == 54)
    {
        digitalWrite(LED_BUILTIN, LOW); 
        ledon = false;
        //Serial.println(string);
    }

    incomingByte = 0;
    delay(100);
 }

