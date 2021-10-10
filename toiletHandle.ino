#include <Servo.h> // library for servo
Servo toiletHandle; //naming my servo tto be toiletHandle
//defining the pins for ultrasonic sensor and servo
#define echoPin 3
#define trigPin 4
#define servoPin 5
//defining the states of the servo/condition
#define TOILET_IN_USE 1
#define NOT_IN_USE 0

long duration;
int distance; 
int previousState = 0;
int useCount = 0;

void setup() {
  toiletHandle.attach(servoPin); 
  pinMode(trigPin, OUTPUT); // trig pin to be output
  pinMode(echoPin, INPUT); //echo pin to be input
  Serial.begin(9600); //setting baud rate for communication with serial monitor
  Serial.println("toilet sensor working");// comment on serial monitor to show sensor is active
  toiletHandle.write(0);// initiating the angle of servo
  delay(1000);
}
//calculating distance from duration
  int calculate_distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;// 0.034 constant for changing duration to distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
//condition part
void loop() {
  int value = calculate_distance();
  if(value>20){ //distance from human to sensor
    previousState = NOT_IN_USE;
    if(useCount>=5){// more than 5 seconds then it shows that the toilet is in use
      flashToilet();
      }
    useCount = 0;
    }
  else if(value<=20){
    if(previousState == TOILET_IN_USE){
      useCount++;
      delay(1000);
      } 
     previousState = TOILET_IN_USE;  
    }
}
//actuation part
void flashToilet(){ 
  toiletHandle.write(90);
  delay(1000);
  toiletHandle.write(0);
  delay(1000);
  }
