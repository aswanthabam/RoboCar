#include <Servo.h>

#define blu_rx 0 // Bluetooth RX pin
#define blu_tx 1 // Bluetooth TX pin

#define ul_echo 2 // Ultrasonic sensor Echo pin
#define ul_trig 3  // Ultrasonic Sensor Trig pin

#define ML_1 4  // left side motors control input 1
#define ML_2 5  // left side motors control input 2
#define MR_1 6  // right side motors control input 1
#define MR_2 7  // Roght side motors control input 2
#define M_speed 9 // All motor speed pin (ENA & ENB pins)
# define M_delay90 500 // Delay needed for rotating the car 90 degree

#define S_pin 10 // Servo motor pin
#define spoint 103 // Servo default position
Servo servo;
char mode = 'C',val;
int distance,L,R,Left,Right;

void setup(){
  Serial.begin(9600); // burd rate
  pinMode(ul_echo,OUTPUT);
  pinMode(ul_trig,INPUT);
  servo.attach(S_pin);
}

void loop(){
  if(Serial.available() > 0){
    // Bluetooth signal available
    val = Serial.read();
    processVal(val); // Process the value got from the Bluetooth and do the task
    return;
  }
  if(mode = 'O'){
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
        left();
        break;
      case 'R':
        // Move right side 
        right();
        break;
      case 'B':
        // Move back side 
        backward();
        break;
      case 'F':
        // Move forward
        forward();
        break;
      case 'S':
        // stop movement
        stop();
        break;
      // below cases are for changing mode
      case 'C':
        // Change mode to control
        mode = 'C';
        break;
      case 'O':
        // Change mode to obstacle Avoiding 
        mode= 'O';
        break;
    }
  }
  else if(mode = 'O'){
    // In obstacle mode 
    switch(value){
      case 'S':
        stop();
        break;
      // below cases are for changing modes
      case 'C':
        mode = 'C';
        break;
    }
  }
}

void left(){
  digitalWrite(MR_1,HIGH);
  digitalWrite(MR_2,LOW);
  digitalWrite(ML_1,LOW);
  digitalWrite(ML_2,HIGH);
}

void right(){
  digitalWrite(MR_1,LOW);
  digitalWrite(MR_2,HIGH);
  digitalWrite(ML_1,HIGH);
  digitalWrite(ML_2,LOW);
}
void forward(){
  digitalWrite(MR_1,HIGH);
  digitalWrite(MR_2,LOW);
  digitalWrite(ML_1,HIGH);
  digitalWrite(ML_2,LOW);
}
void backward(){
  digitalWrite(MR_1,LOW);
  digitalWrite(MR_2,HIGH);
  digitalWrite(ML_1,LOW);
  digitalWrite(ML_2,HIGH);
}
void stop(){
  backward();
  delay(100);
  analogWrite(M_speed,0);
}
void obstacle (){
  distance = ultrasonic(); // Get the current distance
  if (distance <= 12) {
    // Distance less than 12 Cm
    stop(); 
    /*backward();
    delay(100);*/
    //stop();
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      right();
      delay(M_delay90);
      stop();
      delay(200);
    } else if (L > R) {
      left();
      delay(M_delay90);
      stop();
      delay(200);
    }
  } else {
    forward();
  }
}

int ultrasonic() {
  // Read the value of ul sensor and return it.in cm
  digitalWrite(ul_trig, LOW);
  delayMicroseconds(4);
  digitalWrite(ul_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ul_trig, LOW);
  long t = pulseIn(ul_echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}
int rightsee() {
  // Rotate the servo motor to right side and return the ultrasonic sensor value
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return left;
}

int leftsee() {
  // Rotate the servo to left side and return the ultrasonic sensor value
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return right;
}
