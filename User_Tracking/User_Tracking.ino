
#include <string.h>

#define LEFT 6    // Motor 1 on driver
#define RIGHT 9   // Motor 2 on driver

float distance, angle, speedVal;
const float maxSpeed = 6;     // in km/hr
float prevAngle = 90;

const byte resetPin1 = 50;
const byte resetPin2 = 52;

long dists[] = {15, 15};
const int samples = 5;
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

void checkSerial(Stream &serialPort, String s, byte anchorNum) {

  if (serialPort.available()) {
    s = serialPort.readStringUntil('\n'); // read the string
    //Serial.println(s);

    if(s.startsWith("+ANCHOR_RCV")){
      //Serial.println(s);

      dists[anchorNum] = s.substring(s.lastIndexOf(',') + 1).toInt(); // Obtain the distance value

      if (anchorNum == 0) {
        // Ignore outliers and sensor fluctuation
        if (abs(s.substring(s.lastIndexOf(',') + 1).toInt() - lastReading0) < 100 || s.substring(s.lastIndexOf(',') + 1).toInt() > 0) {
          distLogs[anchorNum][oldestIndex0] = s.substring(s.lastIndexOf(',') + 1).toInt();
          lastReading0 = distLogs[anchorNum][oldestIndex0];
          oldestIndex0++;
          if (oldestIndex0 >= samples) {
            oldestIndex0 = 0;
          }
        }
        
      }
      else {
        // Ignore outliers and sensor fluctuation
        if (abs(s.substring(s.lastIndexOf(',') + 1).toInt() - lastReading1) < 100 || s.substring(s.lastIndexOf(',') + 1).toInt() > 0) {
          distLogs[anchorNum][oldestIndex1] = s.substring(s.lastIndexOf(',') + 1).toInt();
          lastReading1 = distLogs[anchorNum][oldestIndex1];
          oldestIndex1++;
          if (oldestIndex1 >= samples) {
            oldestIndex1 = 0;
          }
        }     
      }

      // Update last time reading
      lastSample = millis();
      
      
      //Serial.println(dists[anchorNum]);
    } else {
      // Serial.println(s);
    }
    
    
  }
}



void calculateAverage() {
  for (int axis = 0; axis < anchorCount; axis++) {
    float sum = 0, mean = 0;
    for (int i = 0; i < samples; i++) {
      sum += distLogs[axis][i];
    }
    mean = sum / samples;

    dists[axis] = mean;
  }
}

// void calculateAverage() {
//   for (int axis = 0; axis < 2; axis++) {
//     float sum = 0, mean = 0, sd = 0;
//     int validCount = 0;

//     // Step 1: Compute the mean
//     for (int i = 0; i < samples; i++) {
//       sum += distLogs[axis][i];
//     }
//     mean = sum / samples;

//     // Step 2: Compute standard deviation
//     sum = 0;
//     for (int i = 0; i < samples; i++) {
//       sum += (distLogs[axis][i] - mean) * (distLogs[axis][i] - mean);
//     }
//     sd = sqrt(sum / samples);

//     // Step 3: Filter out outliers (keep values within 2× SD of the mean)
//     sum = 0;
//     validCount = 0;
//     for (int i = 0; i < samples; i++) {
//       if (abs(distLogs[axis][i] - mean) <= 2 * sd) {
//         sum += distLogs[axis][i];
//         validCount++;
//       }
//     }

//     // Step 4: Compute new average (if no valid values, fallback to original mean)
//     dists[axis] = (validCount > 0) ? (sum / validCount) : mean;
//   }
// }








void sendSerialData(Stream &serialPort, String command) {
  serialPort.print(command);
}

void resetDevice() {
  digitalWrite(resetPin1, LOW);  // Set the pin low to trigger the resetPin1
  digitalWrite(resetPin2, LOW);  // Set the pin low to trigger the reset
  delay(100);                    // Wait for 100 ms (adjust as needed for your device)
  digitalWrite(resetPin1, HIGH); // Set the pin high to release the reset
  digitalWrite(resetPin2, HIGH); // Set the pin high to release the reset
}



void setup() {

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

}



void loop() {


  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial2, command);
  //delay(10);
  checkSerial(Serial2, message, 0);
  checkSerial(Serial2, message, 0);
  delay(70);

  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial3, command);
  //delay(10);
  checkSerial(Serial3, message, 1);
  checkSerial(Serial3, message, 1);
  delay(35);

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

    // Update prevAngle
    prevAngle = angle;
    
  } else {
    float tmp = angle;
    angle = prevAngle;
    //prevAngle = tmp;
  }


  // Convert distance to a speed
  currentTime = millis();
  if (distance > 100 && (currentTime - lastSample) < 2000) {
    speedVal = distance / 100;
  }
  else {
    speedVal = 0;
  }
  
  
  // Move toward target
  moveCaddy(speedVal, (int)angle);

}
