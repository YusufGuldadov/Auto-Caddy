#include<math.h>

// The left motor is A, right motor is B
// Motor Connections (All must use PWM pins)
#define LEFT 6
#define RIGHT 9


// Function for setting the speed to a constant value
void setConstantSpeed(float speedVal) {
  // Constant speed going forward
  analogWrite(LEFT, speedVal);
  analogWrite(RIGHT, speedVal);
}

void stopMotors() {
  // Stop
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
}


void accelerateForward(float desiredSpeed, float delayVal) {
  for (int i = 0; i < desiredSpeed; i++) {
    analogWrite(LEFT, i);
    analogWrite(RIGHT, i);
    delay(delayVal);
  }
}

// Function for setting the speeds of each individual motor
// The left motor is A, right motor is B
void setMotorSpeeds(float leftSpeed, float rightSpeed) {
  analogWrite(LEFT, leftSpeed);
  analogWrite(RIGHT, rightSpeed);
}


int speedToPWM(int speed){
  return speed;
}

MotionController controller(0.3, 0.3, 0.5);


void moveCaddy(float speedValue, int ang) {
  // Serial.println("Angle: " + String(ang) + ", Speed: " + String(speedValue));
  // Serial.println("," + String(speedValue) + "," + String(ang));


  // auto [adjustedAngle, adjustedSpeed] = controller.getAdjustedValues(ang, speedValue);

  float speedPWM = 41 * speedValue;    // max value of 246 ( < 250 )
  // double angleRad = ang * M_PI / 180.0; // Convert degrees to radians
  // float decrement = abs(cos(angleRad)) * speedPWM;   // This is how much one wheel will slow down to turn
  // float decrement = 1/4 * (angleRad - M_PI/2)*(angleRad - M_PI/2);
  float decrement = ((-1.0/10000.0)*(ang-90)*(ang-90)) + 1;

  if (speedValue == 0) {
    setMotorSpeeds(0, 0);
  }
  else if (ang == 90) {
    setMotorSpeeds(speedPWM, speedPWM);
  }
  else if (ang < 90) {
    setMotorSpeeds(speedPWM, speedPWM * decrement);
  }
  else {
    setMotorSpeeds(speedPWM * decrement, speedPWM);
  }


  // else {
  //   switch(ang) {
  //     case 0:
  //       //speedPWM*=0.5;
  //       setMotorSpeeds(speedPWM, speedPWM * 0.5);
  //       break;

  //     case 30:
  //       //speedPWM*=0.7;
  //       setMotorSpeeds(speedPWM, speedPWM * 0.7);
  //       break;

  //     case 60:
  //       //speedPWM*=0.9;
  //       setMotorSpeeds(speedPWM, speedPWM * 0.8);
  //       break;

  //     case 90:
  //       setMotorSpeeds(speedPWM, speedPWM);
  //       break;

  //     case 120:
  //       //speedPWM*=0.9;
  //       setMotorSpeeds(speedPWM * 0.8, speedPWM);
  //       break;

  //     case 150:
  //       //speedPWM*=0.7;
  //       setMotorSpeeds(speedPWM * 0.7, speedPWM);
  //       break;

  //     case 180:
  //       //speedPWM*=0.5;
  //       setMotorSpeeds(speedPWM * 0.5, speedPWM);
  //       break;

  //     default:
  //       setMotorSpeeds(0, 0);
  //       break;

  //   }
  // }

}


