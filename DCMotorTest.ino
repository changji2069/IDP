#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  AFMS.begin(); 
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHzx
  
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myMotor2->setSpeed(150);
  myMotor2->run(FORWARD); 
}

void loop() {
  uint8_t i;
  
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);
    myMotor2->setSpeed(i);
    delay(10);
  }
}
