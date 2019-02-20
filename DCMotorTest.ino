#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHzx
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);

  myMotor2->setSpeed(150);
  myMotor2->run(FORWARD);
  myMotor2->run(RELEASE);  
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");

  myMotor->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  
  Serial.print("tock");

  myMotor->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    delay(10);

    
  }

  Serial.print("tech");
  myMotor->run(RELEASE);
  delay(1000);




  Serial.print("tick");

  myMotor2->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor2->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor2->setSpeed(i);  
    delay(10);
  }
  
  Serial.print("tock");

  myMotor2->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor2->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor2->setSpeed(i);  
    delay(10);

    
  }

  Serial.print("tech");
  myMotor2->run(RELEASE);
  delay(1000);
}
