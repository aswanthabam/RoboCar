#include <Servo.h>
#include<SoftwareSerial.h>

/* MOTOR PINS */

#define M1_1 7    // IN 1
#define M1_2 8    // IN 2
#define M2_1 5    // IN 3 
#define M2_2 4    // IN 4
#define M_SPEED 6 // EN 
#define M_delay90 500 // DELAY FOR ROTATING (90) DEG

/* SERVO PINS */

#define S_pin 10 // Servo motor pin
#define spoint 103 // Servo default position

/* BLUETOOTH */

SoftwareSerial bt(2,3); /* (Rx,Tx) */  
char mode = 'C'; // Default in control mode

/* ULTRASONIC */

const int trigPin = 9;
const int echoPin = 10;

float duration, distance;
int L,R,Left,Right;

/* Servo */

Servo servo;

void setup() {
  // SET ALL PIN OF MOTOR DRIVERS TO OUTPUT
  pinMode(M1_1,OUTPUT);
  pinMode(M1_2,OUTPUT);
  pinMode(M2_1,OUTPUT);
  pinMode(M2_2,OUTPUT);
  pinMode(M_SPEED,OUTPUT);
  bt.begin(9600); /* Define baud rate for software serial communication */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(S_pin);
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
  if(mode == 'O'){
    // In Obstacle avoidance mode
    obstacle();
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
void obstacle (){
  distance = ultrasonic(); // Get the current distance
  if (distance <= 12) {
    // Distance less than 12 Cm
    brake(); 
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      right();
      delay(M_delay90);
      stop();
    } else if (L > R) {
      left();
      delay(M_delay90);
      stop();
    }
  } else {
    forward();
  }
}
float ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  return distance;
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
void centersee() {
  // Rotate the servo motor to right side and return the ultrasonic sensor value
  servo.write(spoint);
}
int rightsee() {
  // Rotate the servo motor to right side and return the ultrasonic sensor value
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}

int leftsee() {
  // Rotate the servo to left side and return the ultrasonic sensor value
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}
