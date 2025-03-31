#define LEFT 6    // Motor 1 on driver
#define RIGHT 7   // Motor 2 on driver

#include <Keypad.h>
#include <Key.h>
#include <LiquidCrystal_I2C.h>
#include "globals.h"


///////////////////////////////////////////////////////////////////////////////////////////
// #include <Keypad.h>
// #include <LiquidCrystal_I2C.h>

// // LCD Configuration
// LiquidCrystal_I2C lcd(0x27, 20, 4);

// // Keypad Configuration
// const byte ROWS = 4;
// const byte COLS = 4;
// char keys[ROWS][COLS] = {
//   {'1', '2', '3', 'A'},
//   {'4', '5', '6', 'B'},
//   {'7', '8', '9', 'C'},
//   {'*', '0', '#', 'D'}
// };
// byte rowPins[ROWS] = {4, 5, 6, 7};
// byte colPins[COLS] = {8, 9, 10, 11};
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// // Golf Club Distances
// const int clubDistances[] = {300, 260, 235, 225, 215, 200, 190, 175, 160, 150, 135, 125, 110};
// const char* clubNames[] = {"Driver", "3 Wood", "3 Iron", "4 Iron", "5 Iron", "6 Iron", "7 Iron", "8 Iron", "9 Iron", "P Wedge", "G Wedge", "S Wedge", "L Wedge"};

// // State Variables
// int distanceToHole = 0;
// bool distanceToHoleEntered = false;
// bool suggestionDisplayed = false;

//////////////////////////////////////////////////////////////////////////////////////////////////


void obstacleAdjust(){
  if(angle < 45 || angle > 135){
    return;
  }


  int obstacleMap[5] = {right, front_right, front, front_left, left};

  int idx = angle / 36;


  if(obstacleMap[idx] == 1){
    for(int i = 0; i < 5; i++){

      if(obstacleMap[i] == 0){
        angle = i * 36;

        return;
      } 
    }
  } else return;


  speedVal = 0;


}


void setup() {
  // call user tracking stup
  userTrackingSetup();
  ObstacleDetectionsetup();

  // call ui advising setup
  // keypadLcdSetup();

}

void loop() {

  userTrackingTask();

  checkWithUltrasonic();
  
  obstacleAdjust();
  moveCaddy(speedVal, (int)angle);
  // Serial.println("Angle: " + String(angle) + ", Speed: " + String(speedVal));
  // moveCaddy(5, (int)90);

  //ui advising system
  // keypadLcdTask();

}





