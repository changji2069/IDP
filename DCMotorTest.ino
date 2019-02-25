#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *LMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RMotor = AFMS.getMotor(2);
int frontswitch = 9;
int sideswitch = 10;
int backswitch = 11;


void setup() {
  Serial.begin(9600);
  AFMS.begin(); 
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHzx
  pinMode(sideswitch, INPUT);
}

void loop() {
  wallfollow();
}

void front(int T, int LSpeed, int RSpeed) { //T is tuned to hopefully get a consistent 90 degree turn, CHECK if left 90 and right 90 has the same T
  LMotor->run(BACKWARD);
  RMotor->run(BACKWARD);
  LMotor->setSpeed(LSpeed); //200 and 194 for more or less a straight motion
  RMotor->setSpeed(RSpeed);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
}

void leftturn(int T, int LSpeed, int RSpeed) { //T is tuned to hopefully get a consistent 90 degree turn, CHECK if left 90 and right 90 has the same T
  LMotor->run(FORWARD);
  RMotor->run(BACKWARD);
  LMotor->setSpeed(LSpeed);
  RMotor->setSpeed(RSpeed);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
}

void rightturn(int T, int LSpeed, int RSpeed) { //T is tuned to hopefully get a consistent 90 degree turn, CHECK if left 90 and right 90 has the same T
  LMotor->run(BACKWARD);
  RMotor->run(FORWARD);
  LMotor->setSpeed(LSpeed);
  RMotor->setSpeed(RSpeed);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
}

void rightturn90(){
  leftturn(2300, 200, 0);
  leftturn(3050, 150, 150);
}

void wallfollow(){
  if(digitalRead(sideswitch)==HIGH){
    front(300, 200, 194);
  }else{
    front(10, 50, 200);
  }
}
