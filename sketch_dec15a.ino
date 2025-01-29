long duration; 
int distance;

const int trigPin=10;
const int echoPin=11;


#include <Servo.h>

Servo myServo;
unsigned long previousMillis = 0;
int currentPosition = 0; // 0, 90, 180
int stepIndex = 0;

// Filter parameters
const int REQUIRED_CONSISTENT_READINGS = 5; // Number of consistent readings required
const float MAX_VARIATION = 0.5;           // Maximum allowed variation in cm
const unsigned long MAX_TIME = 1500;       // Maximum time window in ms (1.5 seconds)


const int ledGreen = 13; // Define the LED pin
const int ledRed = 2; // Define the LED pin
const int ledLeft = 3; // Define the LED pin
const int ledRight = 4; // Define the LED pin


void setup() {
  Serial.begin(9600);  // Initialize Serial communication
  pinMode(trigPin, OUTPUT); // Set trigPin as output
  pinMode(echoPin, INPUT);  // Set echoPin as input
  myServo.attach(9);       // Attach the servo to pin 11
  pinMode(ledGreen, OUTPUT); // Set the LED pin as an output
  pinMode(ledRed, OUTPUT); // Set the LED pin as an output
  pinMode(ledLeft, OUTPUT); // Set the LED pin as an output
  pinMode(ledRight, OUTPUT); // Set the LED pin as an output
  myServo.write(90);        // Start with the servo at 90 degrees (center)
}

void loop() {

  // digitalWrite(ledGreen, HIGH); // Turn the LED on
  // delay(100);
  // digitalWrite(ledRed, HIGH); // Turn the LED on  
  // delay(100);

  // digitalWrite(ledLeft, HIGH); // Turn the LED on  
  // delay(100);

  // digitalWrite(ledRight, HIGH); // Turn the LED on   
  // delay(100);

  // digitalWrite(ledGreen, LOW);  // Turn the LED off
  // delay(100);
  // digitalWrite(ledRed, LOW); // Turn the LED off
  // delay(100);

  // digitalWrite(ledLeft, LOW); // Turn the LED off
  // delay(100);

  // digitalWrite(ledRight, LOW); // Turn the LED off
  // delay(100);


  // if ( (detectObjectFiltered() > 0) && (detectObjectFiltered() <= 30)) {  // Check if the object is within range
  //   Serial.println("Object detected within range! Moving servo...");
  //   turnServoToleft();  // Call the function to turn the servo
  // }
  // delay(10);  // Delay for stability

  turnServo_scan();
  // turnServo();
  
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

// Task to turn the servo motor left and right
void turnServo() {
  myServo.write(0);   // Move to 0 degrees (left)
  delay(750);         // Wait for half a second
  myServo.write(180); // Move to 180 degrees (right)
  delay(750);         // Wait for half a second
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

// void turnServo_scan() {
//   // Move smoothly from 90 degrees to 67.5 degrees
//   for (int pos = 90; pos >= 67.5; pos -= 1) {
//     myServo.write(pos);
//     delay(15); // Adjust delay for smoothness (lower for smoother motion)
//   }

//   // Move smoothly from 67.5 degrees to 112.5 degrees
//   for (int pos = 67.5; pos <= 112.5; pos += 1) {
//     myServo.write(pos);
//     delay(15); // Adjust delay for smoothness
//   }

//   // Move smoothly back to 90 degrees
//   for (int pos = 112.5; pos >= 90; pos -= 1) {
//     myServo.write(pos);
//     delay(15); // Adjust delay for smoothness
//   }
// }



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


