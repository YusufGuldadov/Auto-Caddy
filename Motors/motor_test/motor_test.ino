/*
  DBH-12 H-Bridge Demo
  dbh-12-demo.ino
  Demonstrates operation of DBH-12 Dual H-Bridge Motor Driver

  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

#include<math.h>

// Motor Connections (All must use PWM pins)
#define IN1A 3
#define IN1B 5
#define IN2A 6
#define IN2B 9

// Define a fixed speed - do not exceed 250
int fixedSpeed = 80;
float speedValue = 0;   // in km/hr
const float maxSpeed = 6;     // in km/hr
int angle = 0;    // angle to where user is located

void setup() {

  Serial.begin(9600);

  // Set motor & enable connections as outputs
  pinMode(IN1A, OUTPUT);
  pinMode(IN1B, OUTPUT);
  pinMode(IN2A, OUTPUT);
  pinMode(IN2B, OUTPUT);

  // Stop motors
  analogWrite(IN1A, 0);
  analogWrite(IN1B, 0);
  analogWrite(IN2A, 0);
  analogWrite(IN2B, 0);
}

// Function for setting the speed to a constant value
void setConstantSpeed(float speedVal) {
  // Constant speed going forward
  digitalWrite(IN1A, LOW);
  digitalWrite(IN1B, LOW);
  analogWrite(IN2A, speedVal);
  analogWrite(IN2B, speedVal);
}

void stopMotors() {
  // Stop
  analogWrite(IN1A, 0);
  analogWrite(IN1B, 0);
  analogWrite(IN2A, 0);
  analogWrite(IN2B, 0);
}


void accelerateForward(float desiredSpeed, float delayVal) {
  digitalWrite(IN1A, LOW);
  digitalWrite(IN1B, LOW);
  for (int i = 0; i < desiredSpeed; i++) {
    analogWrite(IN2A, i);
    analogWrite(IN2B, i);
    delay(delayVal);
  }
}

// Function for setting the speeds of each individual motor
// The left motor is A, right motor is B
void setMotorSpeeds(float leftSpeed, float rightSpeed) {
  digitalWrite(IN1A, LOW);
  digitalWrite(IN1B, LOW);
  analogWrite(IN2A, leftSpeed);
  analogWrite(IN2B, rightSpeed);
}



void moveCaddy() {
  float speedRPM = 50 * speedValue;    // 167 RPM / 1 km/hr
  double angleRad = angle * M_PI / 180.0; // Convert degrees to radians
  float decrement = sin(abs(angleRad)) * speedRPM;   // This is how much one wheel will slow down to turn
  

  if (angle == 0) {
    setMotorSpeeds(speedRPM, speedRPM);
  }
  else if (angle < 0) {
    setMotorSpeeds(speedRPM - decrement, speedRPM);
  }
  else {
    setMotorSpeeds(speedRPM, speedRPM - decrement);
  }

}















void loop() {

  
  for (int i = -90; i < 90; i++) {
    Serial.print(i);
    
    speedValue = 1;
    angle = i;
    moveCaddy();
    delay(20);
    
  }
//  delay(3000);/

//    // Constant speed going forward
//    digitalWrite(IN1A, LOW);
//    digitalWrite(IN1B, LOW);
//    analogWrite(IN2A, 50);
//    analogWrite(IN2B, 50);
//    delay(20);
//
//    // Accelerate both forward
//    digitalWrite(IN1A, LOW);
//    digitalWrite(IN1B, LOW);
//    for (int i = 0; i < 200; i++) {
//      analogWrite(IN2A, i);
//      analogWrite(IN2B, i);
//      delay(20);
//    }
//  
//    delay(500);
//  
//    // Decelerate both forward
//    for (int i = 200; i >= 0; i--) {
//      analogWrite(IN2A, i);
//      analogWrite(IN2B, i);
//      delay(20);
//    }
//  
//    delay(500);
//  
//    // Accelerate both reverse
//    digitalWrite(IN2A, LOW);
//    digitalWrite(IN2B, LOW);
//    for (int i = 0; i < 200; i++) {
//      analogWrite(IN1A, i);
//      analogWrite(IN1B, i);
//      delay(20);
//    }
//  
//    delay(500);
//  
//    // Decelerate both reverse
//    for (int i = 200; i >= 0; i--) {
//      analogWrite(IN1A, i);
//      analogWrite(IN1B, i);
//      delay(20);
//    }
//  
//    delay(500);
//  
//    // Move in opposite directions at fixed speed
//    digitalWrite(IN1A, LOW);
//    digitalWrite(IN2B, LOW);
//    analogWrite(IN1B, fixedSpeed);
//    analogWrite(IN2A, fixedSpeed);
//  
//    delay(3000);
//  
//    // Stop
//    analogWrite(IN1A, 0);
//    analogWrite(IN1B, 0);
//    analogWrite(IN2A, 0);
//    analogWrite(IN2B, 0);
//  
//    delay(2000);
}
