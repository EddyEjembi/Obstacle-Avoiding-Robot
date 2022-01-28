//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>  
//#include <NewPing.h>
#include <Servo.h> 

int trigpin = A2; 
int echopin = A1; 
#define col_dist 30 
#define MAX_SPEED 255 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 70

//NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor leftmotor1(1, MOTOR12_1KHZ); 
AF_DCMotor leftmotor2(2, MOTOR12_1KHZ);
AF_DCMotor rightmotor1(3, MOTOR34_1KHZ);
AF_DCMotor rightmotor2(4, MOTOR34_1KHZ);
Servo myservo;   

//boolean goesForward=false;
int current_dist = 0;
int speedSet = 0;
int ldst,rdst;
int distance;
long feedback;

void setup() {
Serial.begin(9600);
  myservo.attach(10);  
  myservo.write(90); 
  pinMode(trigpin,OUTPUT);
    pinMode(echopin,INPUT);

}

void loop() {
  myservo.write(90); 
  current_dist= readDistance();
  Serial.println(current_dist);
  if(current_dist < col_dist)
  {
    //moveStop();
    //delay(1000);
    moveBackward();
   }
   else{
    moveForward();
    delay(500);
 }
}
 


int readDistance() { 
  digitalWrite(trigpin,LOW);
  delay(2);
  digitalWrite(trigpin,HIGH);
  delay(100);
  digitalWrite(trigpin,LOW);
  feedback = pulseIn(echopin,HIGH);
  distance = (feedback * 0.034) /2 ;
  return distance;
}

void moveStop() {
  leftmotor1.run(RELEASE); 
  leftmotor2.run(RELEASE);
  rightmotor1.run(RELEASE);
  rightmotor2.run(RELEASE);
  } 
  
void moveForward() {

//goesForward=true;
    leftmotor1.run(FORWARD);      
    leftmotor2.run(FORWARD);
    rightmotor1.run(FORWARD); 
    rightmotor2.run(FORWARD);     
   for (speedSet = 170; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    leftmotor1.setSpeed(speedSet);
    leftmotor2.setSpeed(speedSet);
    rightmotor1.setSpeed(speedSet);
    rightmotor2.setSpeed(speedSet);
     delay(500);
   }
  }


void moveBackward() {
    leftmotor1.run(BACKWARD);      
    leftmotor2.run(BACKWARD);
    rightmotor1.run(BACKWARD);
    rightmotor2.run(BACKWARD);  
  for (speedSet = 170; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftmotor1.setSpeed(speedSet);
    leftmotor2.setSpeed(speedSet);
    rightmotor1.setSpeed(speedSet);
    rightmotor2.setSpeed(speedSet);
    delay(50);
  }
  delay(500);
  changePath();
}  

void turnRight() {
  leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(BACKWARD);
  rightmotor2.run(BACKWARD);
  rightmotor1.setSpeed(MAX_SPEED_OFFSET);
  rightmotor2.setSpeed(MAX_SPEED_OFFSET);     
  delay(1500);
  //leftmotor1.run(FORWARD);      
  //leftmotor2.run(FORWARD);
  //rightmotor1.run(FORWARD);
  //rightmotor2.run(FORWARD);      
} 
 
void turnLeft() {
  leftmotor1.run(BACKWARD);     
  leftmotor2.run(BACKWARD);  
  rightmotor2.run(FORWARD);
  rightmotor2.run(FORWARD);   
  leftmotor1.setSpeed(MAX_SPEED_OFFSET);
  leftmotor2.setSpeed(MAX_SPEED_OFFSET);     
  delay(1500);
  //rightmotor1.run(FORWARD);
  //rightmotor2.run(FORWARD);
}  
void   changePath(){
  moveStop();
      myservo.write(180); 
      delay(500);
      ldst = readDistance();
      delay(500);
    myservo.write(0); 
    delay(500);
    rdst = readDistance();
    delay(500);
    myservo.write(90); 
    //delay(100);
    compareDistance();
  }
void compareDistance(){
  if(rdst>ldst){
  turnRight();
  }
  else if(ldst>rdst){
  turnLeft();
  }
  else{
    turnAround();
    //delay(500);
    }
  }
void     turnAround(){
   leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(BACKWARD);
  rightmotor2.run(BACKWARD);     
  delay(1000);
  }




