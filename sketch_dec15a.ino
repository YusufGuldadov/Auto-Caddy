#include "globals.h"
long duration; 
// int distance;

const int trigPin_1=10;
const int echoPin_1=11;
const int trigPin_2=9;
const int echoPin_2=8;
const int trigPin_3=7;
const int echoPin_3=6;

const int ledRed = 2; // Define the LED pin
const int ledLeft = 3; // Define the LED pin
const int ledRight = 4; // Define the LED pin


// Filter parameters
const int REQUIRED_CONSISTENT_READINGS = 5; // Number of consistent readings required
const float MAX_VARIATION = 10;           // Maximum allowed variation in cm
const unsigned long MAX_TIME = 1500;       // Maximum time window in ms (1.5 seconds)





void setup() {
  Serial.begin(9600);  // Initialize Serial communication
  pinMode(trigPin_1, OUTPUT); // Set trigPin as output
  pinMode(echoPin_1, INPUT);  // Set echoPin as input
  pinMode(trigPin_2, OUTPUT); // Set trigPin as output
  pinMode(echoPin_2, INPUT);  // Set echoPin as input
  pinMode(trigPin_3, OUTPUT); // Set trigPin as output
  pinMode(echoPin_3, INPUT);  // Set echoPin as input


  // pinMode(ledRed, OUTPUT); // Set the LED pin as an output
  // pinMode(ledLeft, OUTPUT); // Set the LED pin as an output
  // pinMode(ledRight, OUTPUT); // Set the LED pin as an output
}

void loop() {


checkWithUltrasonic();

printStateArray();

delay(1000); // Delay between scans



}



// Task to collect distance from ultrasonic sensor
float detectObject(int trigPin, int echoPin) {
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

// digitalWrite(ledRight, HIGH); // Turn the LED on 

// Check if there are objects within the desired range
void checkWithUltrasonic() {

  float distance = detectObject(trigPin_1, echoPin_1); // Get distance from sensor
  if (distance > 0 && distance <= 144) {
      stateArray[1][0]=false;
      
      digitalWrite(ledLeft, HIGH); // Turn the LED on 

      Serial.print("Object detected at distance: ");
      Serial.println(distance);

    }
    else
    {
      stateArray[1][0]=true;
      digitalWrite(ledLeft, LOW); // Turn the LED off 
    }


  distance = detectObject(trigPin_2, echoPin_2); // Get distance from sensor
  if (distance > 0 && distance <= 144) {
      stateArray[2][0]=false;

      digitalWrite(ledRed, HIGH); // Turn the LED on 

      Serial.print("Object detected at distance: ");
      Serial.println(distance);

    }
  else
  {
    stateArray[2][0]=true;
    digitalWrite(ledRed, LOW); // Turn the LED off 
  }

  distance = detectObject(trigPin_3, echoPin_3); // Get distance from sensor
  if (distance > 0 && distance <= 144) {
      stateArray[3][0]=false;
      digitalWrite(ledRight, HIGH); // Turn the LED on 

      Serial.print("Object detected at distance: ");
      Serial.println(distance);
    }
  else
  {
    stateArray[3][0]=true;
    digitalWrite(ledRight, LOW); // Turn the LED on 
  }

    
}




void printStateArray() {
  Serial.println("State Array:");
  for (int i = 0; i < 5; i++) {
    Serial.print("Index ");
    Serial.print(i);
    Serial.print("): [");
    Serial.print(stateArray[i][0] ? "true" : "false"); // Print first entry
    Serial.print(", ");
    Serial.print(stateArray[i][1] ? "true" : "false"); // Print second entry
    Serial.println("]");
  }
  Serial.println();
}






// // Task to filter and return consistent distance
// float detectObjectFiltered() {
//   float lastDistance = -1;              // Previous reading
//   int consistentCount = 0;              // Count of consistent readings
//   unsigned long startTime = millis();   // Start time for the filter

//   while (millis() - startTime < MAX_TIME) {
//     float currentDistance = detectObject();  // Get the current distance

//     // Check if current distance is close enough to the last reading
//     if (abs(currentDistance - lastDistance) <= MAX_VARIATION) {
//       consistentCount++;
//     } else {
//       consistentCount = 1;  // Reset count if not consistent
//     }

//     lastDistance = currentDistance;

//     // If required consistent readings are met
//     if (consistentCount >= REQUIRED_CONSISTENT_READINGS) {
//       Serial.print("Filtered Distance: ");
//       Serial.println(currentDistance);
//       return currentDistance;
//     }

//     delay(100);  // Short delay between readings
//   }

//   return -1;  // Return -1 if no consistent readings found
// }

