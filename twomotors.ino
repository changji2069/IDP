#include <AFMotor.h>               // include library for motor shield

AF_DCMotor blue_motor(3);          // creates object for blue motor on motor port 3
AF_DCMotor red_motor(4);           // creates object for red motor on motor port 4

int blue_speed = 155;              // speed for blue motor
int red_speed = 155;               // speed for red motor

void setup() {                     // function runs once when Arduino resets
}

void loop() {                      // function runs repeatedly indefinitely
  blue_motor.run(FORWARD);         // sets blue motor to run forwards
  red_motor.run(FORWARD);          // sets red motor to run forwards
  blue_motor.setSpeed(blue_speed); // sets speed of blue motor
  red_motor.setSpeed(red_speed);   // sets speed of red motor
  delay(100000);                   // waits 100 seconds for robot to finish
}
