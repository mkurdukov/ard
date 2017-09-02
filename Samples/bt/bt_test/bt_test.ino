int data = 0;

void setup() {
  Serial.begin(9600);  
      Serial.println("Starting");   
      
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
   }
   else{
    Serial.println("Serial is no available");   
    }

    delay(1000);
}
