#define LEFT 6    // Motor 1 on driver
#define RIGHT 9   // Motor 2 on driver


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


void setup() {
  // call user tracking stup
  userTrackingSetup();

  // call ui advising setup
  keypadLcdSetup();

}

void loop() {
  // User tracking
  userTrackingTask();

  // Obstacle detection

  // motor code
  moveCaddy(speedVal, (int)angle);

  //ui advising system
  keypadLcdTask();

}





