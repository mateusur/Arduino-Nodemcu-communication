//This code goes to Arduino
#include <Wire.h>

void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 //Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */
 pinMode(13, OUTPUT);
 digitalWrite(13, LOW);
}

void loop() {
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    int c = Wire.read();      /* receive byte as a character */
    Serial.print(c);/* print the character */
    if(c==65)
    {
     digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
    else if(c==60)
    {
    digitalWrite(13,LOW);
    }
  }
 Serial.println();             /* to newline */
}
//// function that executes whenever data is requested from master
//void requestEvent() {
// Wire.write("Hello NodeMCU");  /*send string on request */
//}
