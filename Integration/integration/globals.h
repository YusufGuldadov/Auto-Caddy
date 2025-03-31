
#ifndef GLOBALS_H
#define GLOBALS_H

extern int front;
extern int front_left;
extern int front_right;
extern int left;
extern int right;
extern int front_left_at_angle;
extern int front_rigth_at_angle;



// long duration; 

const int trigPin_front_left=22;
const int echoPin_front_left=13;
const int trigPin_front=24;
const int echoPin_front=12;
const int trigPin_front_right=26;
const int echoPin_front_right=11;


const int trigPin_right=5;
const int echoPin_right=10;

const int trigPin_left=8;
const int echoPin_left=9;
// const int trigPin_front_left_at_angle=32;
// const int echoPin_front_left_at_angle=8;
// const int trigPin_front_rigth_at_angle=32;
// const int echoPin_front_rigth_at_angle=8;


const int led_front_left = 32; // Define the LED pin
const int led_front = 2; // Define the LED pin
const int led_front_right = 3; // Define the LED pin
const int led_left=28;
const int led_right=30;

// const int temp = 44;



// USER TRACKING GLOBALS ///////////////////////////////////////////////
float distance, angle, rawAngle, speedVal;
const float maxSpeed = 6;     // in km/hr
float prevAngle = 90;

const byte resetPin1 = 50;
const byte resetPin2 = 48;

long dists[] = {15, 15};
const int samples = 10;
const int anchorCount = 2;

unsigned long lastSample, currentTime;

String message;
String command = "AT+ANCHOR_SEND=TAG002,4,TEST\r\n";

// Keep track of the last ten readings
long distLogs[anchorCount][samples];// = {{100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, {100, 100, 100, 100, 100, 100, 100, 100, 100, 100}};
long bilaterateAngles[samples];
int bilaterateIndex = 0;
int oldestIndex0 = 0;
int oldestIndex1 = 0;
long lastReading0 = 100;
long lastReading1 = 100;

////////////////////////////////////////////////////////////////////////

#endif
