#include <Servo.h>
#include "globals.h"
long duration; 
// int distance;

const int trigPin=10;
const int echoPin=11;

Servo myServo, myServo1;

unsigned long previousMillis = 0;
int currentPosition = 0; // 0, 90, 180
int stepIndex = 0;

// Filter parameters
const int REQUIRED_CONSISTENT_READINGS = 5; // Number of consistent readings required
const float MAX_VARIATION = 10;           // Maximum allowed variation in cm
const unsigned long MAX_TIME = 1500;       // Maximum time window in ms (1.5 seconds)


const int ledGreen = 13; // Define the LED pin
const int ledRed = 2; // Define the LED pin
const int ledLeft = 3; // Define the LED pin
const int ledRight = 4; // Define the LED pin


void setup() {
  Serial.begin(9600);  // Initialize Serial communication
  pinMode(trigPin, OUTPUT); // Set trigPin as output
  pinMode(echoPin, INPUT);  // Set echoPin as input
  myServo.attach(9);       // Attach the servo to pin 9

  // pinMode(ledGreen, OUTPUT); // Set the LED pin as an output
  // pinMode(ledRed, OUTPUT); // Set the LED pin as an output
  // pinMode(ledLeft, OUTPUT); // Set the LED pin as an output
  // pinMode(ledRight, OUTPUT); // Set the LED pin as an output
  myServo.write(90);        // Start with the servo at 90 degrees (center)
}

void loop() {


handleServoScanning(); // Handle the servo scanning logic

printStateArray();

delay(1000); // Delay between scans

 

}


// Map array index to degrees
float calculateDegree(int index) {
  
   int temp = (11 - index) * 15; // Index 11 = 0°, Index 5 = 90°, Index 0 = 180°
  
  return temp+7.5;
}

// Check if there are objects within the desired range
void checkWithUltrasonic(int targetIndex) {

int targetIndex_1;
int targetIndex_2;
  if(targetIndex==0)
  {
    targetIndex_1=targetIndex+1;
    targetIndex_2=targetIndex+2;
  }
  else if(targetIndex==11)
  {
    targetIndex_1=targetIndex-1;
    targetIndex_2=targetIndex-2;
  }
  else
  {
    targetIndex_1=targetIndex-1;
    targetIndex_2=targetIndex+1;
  }

  float targetDegree = calculateDegree(targetIndex);

  // Move servo to target degree
  myServo.write(targetDegree);
  delay(1750); // Wait for servo to stabilize

  // Scan around targetIndex (-1, targetIndex, +1)
  float distance = detectObject(); // Get distance from sensor
  if (distance > 0 && distance <= 144) {
      stateArray[targetIndex][0]=true;
      Serial.print("Object detected at degree: ");
      Serial.println(calculateDegree(targetDegree));
    }

 targetDegree = calculateDegree(targetIndex_1);

  // Move servo to target degree
  myServo.write(targetDegree);
  delay(1750); // Wait for servo to stabilize

  // Scan around targetIndex (-1, targetIndex, +1)
  distance = detectObject(); // Get distance from sensor
  if (distance > 0 && distance <= 144) {
      stateArray[targetIndex_1][0]=true;
      Serial.print("Object detected at degree: ");
      Serial.println(calculateDegree(targetIndex_1));
    }



 targetDegree = calculateDegree(targetIndex_2);

  // Move servo to target degree
  myServo.write(targetDegree);
  delay(1750); // Wait for servo to stabilize

  // Scan around targetIndex (-1, targetIndex, +1)
  distance = detectObject(); // Get distance from sensor
  if (distance > 0 && distance <= 144) {
      stateArray[targetIndex_2][0]=true;
      Serial.print("Object detected at degree: ");
      Serial.println(calculateDegree(targetIndex_2));
    }
    
}




// Task to handle servo scanning based on array
void handleServoScanning() {
  for (int i = 0; i < 12; i++) {
    if (stateArray[i][1]) { // If second array entry is true
      Serial.print("Turning to degree: ");
      Serial.println(calculateDegree(i));
      checkWithUltrasonic(i); // Check with ultrasonic sensor
      break; // Stop after the first valid entry
    }
  }
}

// Task to collect distance from ultrasonic sensor
float detectObject() {
  // Send a 10µs pulse to trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo pulse duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  float distance = (duration * 0.034) / 2;

  // Print the distance
  Serial.print("Distance: ");
  Serial.println(distance);

  // Return the calculated distance
  return distance;
}




void printStateArray() {
  Serial.println("State Array:");
  for (int i = 0; i < 12; i++) {
    Serial.print("Index ");
    Serial.print(i);
    Serial.print(" (Degree ");
    Serial.print((11 - i) * 15); // Calculate corresponding degree
    Serial.print("): [");
    Serial.print(stateArray[i][0] ? "true" : "false"); // Print first entry
    Serial.print(", ");
    Serial.print(stateArray[i][1] ? "true" : "false"); // Print second entry
    Serial.println("]");
  }
  Serial.println();
}






// Task to turn the servo motor left and right
void turnServo() {
  myServo.write(0);   // Move to 0 degrees (left)
  delay(1750);         // Wait for half a second
  myServo.write(180); // Move to 180 degrees (right)
  delay(1750);         // Wait for half a second
  myServo.write(90);  // Return to 90 degrees (center)
  delay(1000);         // Wait for half a second
}

void turnServo_scan() {
  myServo.write(75); // Move to 75 degrees (left)
  delay(250);          // Wait for a short delay

  myServo.write(105); // Move to 112.5 degrees (right)
  delay(250);           // Wait for a short delay

  myServo.write(90);   // Return to 90 degrees (center)
  delay(250);          // Wait for a short delay
}





// Task to turn the servo motor left and right
void turnServoToleft() {
  myServo.write(0);   // Move to 0 degrees (left)
  delay(500);         // Wait for half a second
  myServo.write(90);  // Return to 90 degrees (center)
  delay(250);         // Wait for half a second
}



// Task to turn the servo motor left and right
void turnServoToright() {
  myServo.write(180); // Move to 180 degrees (right)
  delay(250);         // Wait for half a second
  myServo.write(90);  // Return to 90 degrees (center)
  delay(250);
}




// Task to filter and return consistent distance
float detectObjectFiltered() {
  float lastDistance = -1;              // Previous reading
  int consistentCount = 0;              // Count of consistent readings
  unsigned long startTime = millis();   // Start time for the filter

  while (millis() - startTime < MAX_TIME) {
    float currentDistance = detectObject();  // Get the current distance

    // Check if current distance is close enough to the last reading
    if (abs(currentDistance - lastDistance) <= MAX_VARIATION) {
      consistentCount++;
    } else {
      consistentCount = 1;  // Reset count if not consistent
    }

    lastDistance = currentDistance;

    // If required consistent readings are met
    if (consistentCount >= REQUIRED_CONSISTENT_READINGS) {
      Serial.print("Filtered Distance: ");
      Serial.println(currentDistance);
      return currentDistance;
    }

    delay(100);  // Short delay between readings
  }

  return -1;  // Return -1 if no consistent readings found
}

