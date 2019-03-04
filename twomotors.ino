#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *LMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RMotor = AFMS.getMotor(2);
int frontswitch = 8;
int sideswitch = 9;
int backswitch = 11;

int sensorpin = A1;                 // analog pin used to connect the sharp sensor
int val = 0;                 // variable to store the values from sensor(initially zero)

int var = 0;


void setup() {
  Serial.begin(9600);
  AFMS.begin(); 
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHzx
  pinMode(frontswitch, INPUT);
}

void loop() {
  while(digitalRead(frontswitch == LOW)){
    front(5000, 150, 150);
  }
  
}


// for reading values use this block of code >>>>
//  while(var<80){
//    val = get_Sharp_GP2Y0A21YK_Distance(sensorpin);
//    Serial.println(val);
//    delay(500);
//    var++;
//  }



void front(int T, int LSpeed, int RSpeed) { //T is tuned to hopefully get a consistent 90 degree turn, CHECK if left 90 and right 90 has the same T
  LMotor->setSpeed(LSpeed); //200 and 194 for more or less a straight motion
  RMotor->setSpeed(RSpeed);
  LMotor->run(BACKWARD);
  RMotor->run(BACKWARD);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
}

void back(int T, int LSpeed, int RSpeed) { //T is tuned to hopefully get a consistent 90 degree turn, CHECK if left 90 and right 90 has the same T
  LMotor->setSpeed(LSpeed); //200 and 194 for more or less a straight motion
  RMotor->setSpeed(RSpeed);
  LMotor->run(FORWARD);
  RMotor->run(FORWARD);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
}

void leftturn(int T, int LSpeed, int RSpeed) { //T is tuned to hopefully get a consistent 90 degree turn, CHECK if left 90 and right 90 has the same T
  LMotor->setSpeed(LSpeed);
  RMotor->setSpeed(RSpeed);
  LMotor->run(FORWARD);
  RMotor->run(BACKWARD);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
}

void rightturn(int T, int LSpeed, int RSpeed) { //T is tuned to hopefully get a consistent 90 degree turn, CHECK if left 90 and right 90 has the same T
  LMotor->setSpeed(LSpeed);
  RMotor->setSpeed(RSpeed);
  LMotor->run(BACKWARD);
  RMotor->run(FORWARD);
  delay(T);
  LMotor->setSpeed(0);
  RMotor->setSpeed(0);
}

void rightturn90(){
  leftturn(2300, 200, 0);
  leftturn(3050, 150, 150);
}

void wallfollow(){
  while(digitalRead(frontswitch) == HIGH){
    front(400, 150, 160);
    front(100, 130, 70);
  }
}

float get_Sharp_GP2Y0A21YK_Distance(int PinID) //calibrate the IR reading into meaningful distance in cm
{
    // Read analog to digital converter value
    float ADCValue = (float)analogRead(PinID);

    // Convert in millimeters and return distance
    return  200.3775040589502
            - 2.2657665648980 * ADCValue
            + 0.0116395328796 * ADCValue * ADCValue
            - 0.0000299194195 * ADCValue * ADCValue * ADCValue
            + 0.0000000374087 * ADCValue * ADCValue * ADCValue * ADCValue
            - 0.0000000000181 * ADCValue * ADCValue * ADCValue * ADCValue * ADCValue;
}

void shelfdetect(){
  while(var < 160){ //later change the condition to FRONTSWITCH == LOW && var < 20, then assign var = 21 when shelf is detected, recovery process if missed shelf, turn back
    val = get_Sharp_GP2Y0A21YK_Distance(sensorpin);
    Serial.println(val);
    k
    if(val > 33){
      front(100, 50, 100);
      front(100, 100, 50);
    }else if(val < 34 && val >30){
      front(100, 100, 97);
    }else if(val < 22){
      front(4000, 100, 97);
      var = 161;
    }
    else{
      front(100, 100, 50);
      front(100, 50, 100);
    }
    var++;
    }
}

void rightturn90andsticktowall(){
   back(300, 200, 194);
    rightturn90();
    back(2000,100,97);
  for(int i=0;i<9;i++){
    front(500,50,200);
    front(480,200,50);
    back(2000,100,97);
  }
}

void rightturn90andstay(){
   back(300, 200, 194);
    rightturn90();
    back(2000,100,97);
}
