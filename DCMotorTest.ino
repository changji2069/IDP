#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *LMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  AFMS.begin(); 
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHzx
  
}

void loop() {
  turn90(1000);
}

void turn90(int T) {
  LMotor->run(FORWARD);
  RMotor->run(BACKWARD);
  LMotor->setSpeed(150);
  RMotor->setSpeed(150);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
  exit(0);
}
