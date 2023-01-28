#define M1_1 7    // IN 1
#define M1_2 6    // IN 2
#define M2_1 5    // IN 3 
#define M2_2 4    // IN 4
#define M_SPEED 9 // EN 

void setup() {
  // SET ALL PIN OF MOTOR DRIVERS TO OUTPUT
  pinMode(M1_1,OUTPUT);
  pinMode(M1_2,OUTPUT);
  pinMode(M2_1,OUTPUT);
  pinMode(M2_2,OUTPUT);
  pinMode(M_SPEED,OUTPUT);
}
void loop() {
  // RANDOM MOVEMENT
  forward();
  delay(3000);
  backward();
  delay(3000);
  left();
  forward();
  delay(3000);
  right();
  forward();
  delay(3000);
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
void Break(){
  // MOVE BACKWARD FOR A 100 MILLI SECONDS AND STOP THE MOTOR (FOR INSTANT BREAKING)
  start();
  backward();
  delay(100);
  stop();
}