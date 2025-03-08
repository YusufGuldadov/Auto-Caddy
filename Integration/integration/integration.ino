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


// USER TRACKING GLOBALS ///////////////////////////////////////////////
float distance, angle, speedVal;
const float maxSpeed = 6;     // in km/hr
float prevAngle = 90;

const byte resetPin1 = 50;
const byte resetPin2 = 52;

long dists[] = {15, 15};
const int samples = 10;
const int anchorCount = 2;

unsigned long lastSample, currentTime;

String message;
String command = "AT+ANCHOR_SEND=TAG001,4,TEST\r\n";

// Keep track of the last ten readings
long distLogs[anchorCount][samples];// = {{100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, {100, 100, 100, 100, 100, 100, 100, 100, 100, 100}};
int oldestIndex0 = 0;
int oldestIndex1 = 0;
long lastReading0 = 100;
long lastReading1 = 100;

////////////////////////////////////////////////////////////////////////


void obstacleAdjust(){
  if(angle < 45 || angle > 135){
    return;
  }


  int map[5] = {left, front_left, front, front_right, right};

  int idx = (angle - 45) / 5;

  if(map[idx] == 1){
    for(int i = 0; i < 5; i++){

      if(map[i] == 0){
        angle = i*5 + 45;

        return;
      } 
    }
  }


  speedVal = 0;


}


void setup() {
  // call user tracking stup
  userTrackingSetup();
  // ObstacleDetectionsetup();

  // call ui advising setup
  // keypadLcdSetup();

}

void loop() {
  // userTrackingTask();
  // checkUltrasonic_front_left();
  // checkUltrasonic_front_right();

  userTrackingTask();
  // checkUltrasonic_front();

  // userTrackingTask();
  // checkUltrasonic_left();
  // checkUltrasonic_right();
  
  // obstacleAdjust();
  moveCaddy(speedVal, (int)angle);

  //ui advising system
  // keypadLcdTask();

}





