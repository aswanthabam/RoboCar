#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
Servo myservo;
float duration, distance;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(3);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void left() {
  myservo.write(0);
  delay(150);
}
void right () {
  myservo.write(170);
  delay(150);
}
void servoCenter() {
  myservo.write(80);
  delay(150);
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

void loop() {
  distance = ultrasonic();
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
  if(distance >= 40) {
    left();
  }else if(distance <= 15) {
    right();
  }
}
