/*
 * Arduino Uno.
 * Ultrasonic Sonic Sensor HC-SR04. Sensor 1, 2 and 3 is on port, front, starboard side respectively.
 * Arduino Motor Shield similar to model (L293) (SKU: DRI0001) with no brake control. Motor A and B is on port and starboard side respectively.
 * Wheel Encoders (SKU: SEN0038). Encoder A and B is attached to motor A and B respectively.
 */

const int trig1 = 8; // pin number for sensor 1 trigger pin
const int echo1 = 9; // pin number for sensor 1 echo pin
const int trig2 = 10; // pin number for sensor 2 trigger pin
const int echo2 = 11; // pin number for sensor 2 echo pin
const int trig3 = 12; // pin number for sensor 3 trigger pin
const int echo3 = 13; // pin number for sensor 3 echo pin

long duration1; // time for ultrasound to bound back to sensor 1
int distance1; // distance to obstacle on the port side in centimeters
long duration2; // time for ultrasound to bound back to sensor 2
int distance2; // distance to obstacle on the front in centimeters
long duration3; // time for ultrasound to bound back to sensor 3
int distance3; // distance to obstacle on the starboard side in centimeters

const int dirA = 4; // pin number for motor A direction control
const int pwmA = 5; // pin number for motor A pwm control
const int dirB = 7; // pin number for motor B direction control
const int pwmB = 6; // pin number for motor B pwm control
int speedAB = 255; // speed for motor to move between 0 to 255
int delaytime = 3000; // time of delay in milliseconds

const int interruptA = 2;  // pin number for encoder A interrupt pin
const int interruptB = 3; // pin number for encoder B interrupt pin

long coder[2] = {0,0}; // an array to hold wheel speed of left and right wheel encoders respectively

const int optimumdistance = 20; // optimum distance to trigger response from car in centimeter

// the setup function runs once when you press reset or power the board
void setup() {

  // setups sensor 1, 2 and 3
  pinMode(trig1, OUTPUT); // sets the sensor 1 trigger pin as an output
  pinMode(echo1, INPUT); // sets the sensor 1 echo pin as an input
  pinMode(trig2, OUTPUT); // sets the sensor 2 trigger pin as an output
  pinMode(echo2, INPUT); // sets the sensor 2 echo pin as an input
  pinMode(trig3, OUTPUT); // sets the sensor 3 trigger pin as an output
  pinMode(echo3, INPUT); // sets the sensor 3 echo pin as an input
  
  // setups motor A and B
  pinMode(dirA, OUTPUT); // initiates motor A direction control pin
  pinMode(dirB, OUTPUT); // initiates motor B direction control pin

  // setups interrupt mode of encoder A and B
  attachInterrupt(digitalPinToInterrupt(interruptA), leftwheelspeed, CHANGE); // initiates encoder A interrupt mode
  attachInterrupt(digitalPinToInterrupt(interruptB), rightwheelspeed, CHANGE); // initiates encoder B interrupt mode

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop(){

  checkdistance();

  // default respond for car is to move forward
  if (distance1 > optimumdistance){ // no obstacles in front of the car
    moveforward();
  }

  // obstacles directly in front of the car
  else {
    stopmoving(); 
    
    checkdistance();

    checkleftandright();

    while (distance1 < optimumdistance && distance3 < optimumdistance){
    
      movebackward();

      checkleftandright();

    return;

    }
  }

}

// sensors check their respective distance
int checkdistance(){
  
  digitalWrite(trig1, LOW); // clears all the sensors trigger pin
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH); // sets each of the trigger pin on HIGH state to emit ultrasound for 10 microseconds only
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH); // reads the echoPin, returns the sound wave travel time in microseconds
  distance1 = duration1*0.034/2; // calculate the respective distance which speed of sound is 0.034 centimeters per microseconds
  
  digitalWrite(trig2, LOW); // repeated for sensor 2
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH); 
  distance2 = duration2*0.034/2;
  
  digitalWrite(trig3, LOW); // repeated for sensor 3
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH); 
  distance3 = duration3*0.034/2;

  return distance1, distance2, distance3;
}


//determine the best response for either left or right turn
void checkleftandright(){

  // best response is left turn
  if (distance1 > distance3 && distance1 > optimumdistance){ // left-hand side of car is longer and has no obstacles
    turnleft();
  } 

  // best response is right turn
  else if (distance3 > distance1 && distance3 > optimumdistance){ // right-hand side of car is longer and has no obstacles
    turnright();
  }
  
  else{
    return;
  }
}


// car moves forward
void moveforward(){
  
  digitalWrite(dirA, HIGH); // establishes forward direction of motor A
  digitalWrite(dirB, HIGH); // establishes forward direction of motor B 
  analogWrite(pwmA, speedAB);   // spins motor A 
  analogWrite(pwmB, speedAB);   // spins motor B
  
}

// car moves backward
void movebackward(){
  
  digitalWrite(dirA, LOW); // establishes backward direction of motor A
  digitalWrite(dirB, LOW); // establishes backward direction of motor B
  analogWrite(pwmA, speedAB);   // spins motor A
  analogWrite(pwmB, speedAB);   // spins motor B
  delay(400);
}

// car stops
void stopmoving(){
  
  digitalWrite(dirA, HIGH); // establishes backward direction of motor A
  digitalWrite(dirB, HIGH); // establishes backward direction of motor B
  analogWrite(pwmA, 0);   // spins motor A
  analogWrite(pwmB, 0);   // spins motor B
  delay(400);
}

// car turns left
void turnleft(){
  
  digitalWrite(dirA, LOW); // establishes backward direction of motor A
  digitalWrite(dirB, HIGH); // establishes forward direction of motor B
  analogWrite(pwmA, speedAB);   // spins motor A
  analogWrite(pwmB, speedAB);   // spins motor B
  delay(400); // approximate time for 90 degrees left turn
}

//car turns right
void turnright(){
  
  digitalWrite(dirA, HIGH); // establishes backward direction of motor A
  digitalWrite(dirB, LOW); // establishes backward direction of motor B
  analogWrite(pwmA, speedAB);   // spins motor A
  analogWrite(pwmB, speedAB);   // spins motor B
  delay(400); // approximate time for 90 degrees right turn
}

// encoders check the speed of left and right wheels every 100 milliseconds and make corrections
void checkspeed(){

  static unsigned long timer = 0; // current time

  if (millis() - timer > 1000){  
    if (coder[0] - coder[1] > 2){
        digitalWrite(dirA, HIGH); 
        digitalWrite(dirB, HIGH); 
        analogWrite(pwmA, 180);   
        analogWrite(pwmB, 255);   
        delay(500);
    } else if (coder[1] - coder[0] >2){
        digitalWrite(dirA, HIGH); 
        digitalWrite(dirB, HIGH); 
        analogWrite(pwmA, 255);
        analogWrite(pwmB, 180);
        delay(500);
    }

    coder[0] = 0; // clears data buffer in the array
    coder[1] = 0;
    timer = millis(); // updates current time
  }
  else {
    return;
  }
}
  
//counts encoder A interrupts
void leftwheelspeed() {
  coder[0] += 1; // increment left wheel speed by one
}

//counts encoder B interrupts
void rightwheelspeed(){
  coder[1] += 1; // increment right wheel speed by one
}



