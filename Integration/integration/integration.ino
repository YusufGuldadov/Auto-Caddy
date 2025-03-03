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

}

void loop() {
  // User tracking
  userTrackingTask();

  // Obstacle detection

  // motor code
  moveCaddy(speedVal, (int)angle);

}


void userTrackingSetup() {
  // Initalise Logs
  for(int anchorIdx = 0; anchorIdx < anchorCount; anchorIdx++){
    for(int dist : distLogs[anchorIdx]){
      dist = 100;
    }
  }

  // Set motor & enable connections as outputs
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);

  // Stop motors
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
  // digitalWrite(LEFT, LOW);
  // digitalWrite(RIGHT, LOW);

  Serial.println("Setup Complete (MOTORS)\n");
  pinMode(resetPin1, OUTPUT); // Configure the pin as an output
  digitalWrite(resetPin1, HIGH); // Ensure the pin is initially high (inactive)
  pinMode(resetPin2, OUTPUT); // Configure the pin as an output
  digitalWrite(resetPin2, HIGH); // Ensure the pin is initially high (inactive)
  resetDevice();

  delay(50);

  Serial.begin(115200);
  Serial2.begin(115200); // Anchor setup on Serial2
  Serial3.begin(115200); // Tag setup on Serial3

  Serial.println("Setup Start\n");
  delay(100);

  // Configure Anchor (Serial2)
  sendSerialData(Serial2, "AT+MODE=1\r\n"); // Set Anchor mode
  delay(200);
  sendSerialData(Serial2, "AT+NETWORKID=Autoca1\r\n"); // Set network ID
  delay(200);
  sendSerialData(Serial2, "AT+ADDRESS=ANCHOR01\r\n"); // Set Anchor address
  delay(200);
  sendSerialData(Serial2, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90\r\n"); // Set password
  delay(200);
  sendSerialData(Serial2, "AT+BANDWIDTH=1\r\n");
  delay(200);
  sendSerialData(Serial2, "AT+IPR=115200\r\n");
  delay(200);
  sendSerialData(Serial2, "AT+CHANNEL=9\r\n");
  delay(200);
  checkSerial(Serial2, message, 0);
  sendSerialData(Serial2, "AT+CAL=10\r\n");
  delay(200);
  checkSerial(Serial2, message, 0);
  delay(200);

//  // Configure Tag (Serial3)
//  sendSerialData(Serial3, "AT+MODE=0\r\n"); // Set Tag mode
//  delay(1000);
//  sendSerialData(Serial3, "AT+NETWORKID=Autoca1\r\n"); // Set network ID
//  delay(1000);
//  sendSerialData(Serial3, "AT+ADDRESS=TAG001\r\n"); // Set Tag address
//  delay(1000);
//  sendSerialData(Serial3, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90\r\n"); // Set password
//  delay(1000);
//  sendSerialData(Serial3, "AT+BANDWIDTH=1\r\n"); 
//  delay(1000);
//  sendSerialData(Serial3, "AT+IPR=115200\r\n");
//  delay(1000);

  sendSerialData(Serial3, "AT+MODE=1\r\n"); // Set Anchor mode
  delay(200);
  sendSerialData(Serial3, "AT+NETWORKID=Autoca1\r\n"); // Set network ID
  delay(200);
  sendSerialData(Serial3, "AT+ADDRESS=ANCHOR02\r\n"); // Set Anchor address
  delay(200);
  sendSerialData(Serial3, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90\r\n"); // Set password
  delay(200);
  sendSerialData(Serial3, "AT+BANDWIDTH=1\r\n"); 
  delay(200);
  sendSerialData(Serial3, "AT+IPR=115200\r\n");
  delay(200);
  sendSerialData(Serial3, "AT+CHANNEL=9\r\n");
  delay(200);
  checkSerial(Serial3, message, 0);
  sendSerialData(Serial3, "AT+CAL=10\r\n");
  delay(200);
  checkSerial(Serial3, message, 0);



  Serial.println("Setup Complete (UWB)\n");



  // Time variables
  lastSample = 0;
  currentTime = 0;

  Serial.println("Distance,Angle,Speed,Direction");
}

void userTrackingTask() {
  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial2, command);
  //delay(10);
  checkSerial(Serial2, message, 0);
  checkSerial(Serial2, message, 0);
  delay(80);

  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial3, command);
  //delay(10);
  checkSerial(Serial3, message, 1);
  checkSerial(Serial3, message, 1);
  delay(40);

//  // Print out the last three readings
//  Serial.println("PRINTING LAST THREE");
//  for (int i = 0; i < 2; i++) {
//    for (int j = 0; j < 5; j++) {
//      Serial.println(distLogs[i][j]);
//    }
//  }
//  Serial.println("DONE");

  // Calculate average of last three readings
  calculateAverage();

  // Serial.println(dists[0]);

  // Find distance and angle to target
  bilaterate(dists[0], dists[1]);



  if (abs(angle - prevAngle) < 60) {

    if(angle < 15) {
      angle = 0;
    } else if(angle < 45) {
      angle = 30;
    } else if(angle < 75) {
      angle = 60;
    } else if(angle < 105) {
      angle = 90;
    } else if(angle < 135) {
      angle = 120;
    } else if(angle < 165) {
      angle = 150;
    } else {
      angle = 180;
    } 


    // if (angle < 15) {
    //     angle = 0;
    // } else if (angle < 30) {
    //     angle = 15;
    // } else if (angle < 45) {
    //     angle = 30;
    // } else if (angle < 60) {
    //     angle = 45;
    // } else if (angle < 75) {
    //     angle = 60;
    // } else if (angle < 105) {  // Making 90° window equal to the others
    //     angle = 90;
    // } else if (angle < 120) {
    //     angle = 105;
    // } else if (angle < 135) {
    //     angle = 120;
    // } else if (angle < 150) {
    //     angle = 135;
    // } else if (angle < 165) {
    //     angle = 150;
    // } else {
    //     angle = 180;
    // }

    // if(angle > 70 && angle < 110){
    //   angle = 90;
    // }


    // if(angle < 15) {
    //   angle = 0;
    // } else if(angle < 60) {
    //   angle = 38;
    // } else if(angle < 120) {
    //   angle = 90;
    // } else if(angle < 165) {
    //   angle = 143;
    // } else {
    //   angle = 180;
    // } 

    // Update prevAngle
    prevAngle = angle;
    
  } else {
    float tmp = angle;
    angle = prevAngle;
    // prevAngle = tmp;
  }

  // Serial.print(String(distance) + "," + String(angle));


  // Convert distance to a speed
  currentTime = millis();
  if (distance > 100 && (currentTime - lastSample) < 1000) {
    // Start up boost
    if (distance < 150) {
      speedVal = 3;
    
    }
    else {
      speedVal = distance / 100;
    }

    if (speedVal > 4) {
      speedVal = 4;
    }
  }
  else {
    speedVal = 0;
  }
  

  // moveCaddyRemote();
  
  // Move toward target
  // moveCaddy(speedVal, (int)angle);
  // moveCaddy(4, (int)90);

}
