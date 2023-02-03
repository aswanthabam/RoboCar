#include<SoftwareSerial.h>

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(2,3); /* (Rx,Tx) */  

/* MOTOR PINS */
#define M1_1 7    // IN 1
#define M1_2 8    // IN 2
#define M2_1 5    // IN 3 
#define M2_2 4    // IN 4
#define M_SPEED 6 // EN 

char mode = 'C'; // Default in control mode

void setup() {
  // SET ALL PIN OF MOTOR DRIVERS TO OUTPUT
  pinMode(M1_1,OUTPUT);
  pinMode(M1_2,OUTPUT);
  pinMode(M2_1,OUTPUT);
  pinMode(M2_2,OUTPUT);
  pinMode(M_SPEED,OUTPUT);
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {
  if (bt.available()) /* If data is available on serial port */
  {
    char ch = bt.read();
    Serial.println("Value received: "+ch); /* Print character received on to the serial monitor */
    processVal(ch);
    return;
  }
}
void processVal(char value){
  if(mode == 'C'){
    // in Control mode
    switch(value){
      case 'L':
        // Move left side 
        Serial.println("Moving Left..");
        left();
        break;
      case 'R':
        // Move right side 
        Serial.println("Moving Right..");
        right();
        break;
      case 'B':
        // Move back side 
        Serial.println("Moving Backward..");
        backward();
        break;
      case 'F':
        // Move forward
        Serial.println("Moving Forward..");
        forward();
        break;
      case 'S':
        // stop movement
        Serial.println("Breaking..");
        brake();
        break;
      case 'X':
        // Release the motor. no movements
        Serial.println("Releasing Motors..");
        stop();
        break;
    }
  }
}

void forward(){
  // MOVE FORWARD, BOTH MOTORS CLOCKWOSE
  start(); // SET SPEED
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,HIGH);
  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,HIGH);
}
void backward(){
  // MOVE BACKWARD, BOTH MOTORS ANTI-CLOCKWOSE
  start();
  digitalWrite(M1_1,HIGH);
  digitalWrite(M1_2,LOW);
  digitalWrite(M2_1,HIGH);
  digitalWrite(M2_2,LOW);
}
void left(){
  // MOVE LEFT, RIGHT SIDE MOTORS FORWARD, LEFT SODE MOTORS BACKWARD
  start();
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,HIGH);
  digitalWrite(M2_1,HIGH);
  digitalWrite(M2_2,LOW);
}
void right(){
  // MOVE LEFT, RIGHT SIDE MOTORS BACKWARD, LEFT SODE MOTORS FORWARD
  start();
  digitalWrite(M1_1,HIGH);
  digitalWrite(M1_2,LOW);
  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,HIGH);
}
void stop(){
  // Set SPEED TO 0
  analogWrite(M_SPEED,0);
}
void start(){
  // SET SPEED TO 200/225
  analogWrite(M_SPEED,200);
}
void brake(){
  // MOVE BACKWARD FOR A 100 MILLI SECONDS AND STOP THE MOTOR (FOR INSTANT BREAKING)
  start();
  backward();
  delay(100);
  stop();
}
