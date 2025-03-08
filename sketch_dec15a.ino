#include "globals.h"
// long duration; 

const int trigPin_front_left=22;
const int echoPin_front_left=13;
const int trigPin_front=24;
const int echoPin_front=12;
const int trigPin_front_right=26;
const int echoPin_front_right=11;


const int trigPin_left=28;
const int echoPin_left=10;

const int trigPin_right=30;
const int echoPin_right=9;

// const int trigPin_front_left_at_angle=32;
// const int echoPin_front_left_at_angle=8;
// const int trigPin_front_rigth_at_angle=32;
// const int echoPin_front_rigth_at_angle=8;


const int led_front_left = 43; // Define the LED pin
const int led_front = 41; // Define the LED pin
const int led_front_right = 35; // Define the LED pin
const int led_left=45;
const int led_right=37;

// const int temp = 44;



void setup() {
  Serial.begin(9600);  // Initialize Serial communication
  pinMode(trigPin_front_left, OUTPUT); // Set trigPin as output
  pinMode(echoPin_front_left, INPUT);  // Set echoPin as input
  pinMode(trigPin_front, OUTPUT); // Set trigPin as output
  pinMode(echoPin_front, INPUT);  // Set echoPin as input
  pinMode(trigPin_front_right, OUTPUT); // Set trigPin as output
  pinMode(echoPin_front_right, INPUT);  // Set echoPin as input

  pinMode(trigPin_left, OUTPUT); // Set trigPin as output
  pinMode(echoPin_left, INPUT);  // Set echoPin as input
  pinMode(trigPin_right, OUTPUT); // Set trigPin as output
  pinMode(echoPin_right, INPUT);  // Set echoPin as input
  // pinMode(trigPin_front_left_at_angle, OUTPUT); // Set trigPin as output
  // pinMode(echoPin_front_left_at_angle, INPUT);  // Set echoPin as input
  // pinMode(trigPin_front_rigth_at_angle, OUTPUT); // Set trigPin as output
  // pinMode(echoPin_front_rigth_at_angle, INPUT);  // Set echoPin as input


  pinMode(led_front, OUTPUT); // Set the LED pin as an output
  pinMode(led_front_left, OUTPUT); // Set the LED pin as an output
  pinMode(led_front_right, OUTPUT); // Set the LED pin as an output
  pinMode(led_left, OUTPUT); // Set the LED pin as an output
  pinMode(led_right, OUTPUT); // Set the LED pin as an output
  // pinMode(temp, OUTPUT); // Set the LED pin as an output
}

void loop() {

checkWithUltrasonic();

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
  // Serial.print("Distance: ");
  // Serial.println(distance);

  // Return the calculated distance
  return distance;
}



// Check if there are objects within the desired range
void checkWithUltrasonic() {

  float distance = detectObject(trigPin_front_left, echoPin_front_left); // Get distance from sensor
  if (distance > 0 && distance <= 140) {
      
      front_left=1;
      
      digitalWrite(led_front_left, HIGH); // Turn the LED on 

      // Serial.print("Object detected at distance: ");
      // Serial.println(distance);

    }
    else
    {
      front_left=0;
      digitalWrite(led_front_left, LOW); // Turn the LED off 
      // Serial.print("Object detected at distance: ");
      // Serial.println(distance);
    }

    delay(65); // Delay between scans

  

    
    
    
    distance = detectObject(trigPin_front, echoPin_front); // Get distance from sensor
    if (distance > 0 && distance <= 140) {
      front=1;
      
      digitalWrite(led_front, HIGH); // Turn the LED on 
      
      // Serial.print("Object detected at distance: ");
      // Serial.println(distance);
      
    }
    else
    {
      front=0;
      
      digitalWrite(led_front, LOW); // Turn the LED off 
    }
    
    delay(65); // Delay between scans
    
    
    
    
    distance = detectObject(trigPin_front_right, echoPin_front_right); // Get distance from sensor
    if (distance > 0 && distance <= 140) {
      
      front_right=1;
      
      digitalWrite(led_front_right, HIGH); // Turn the LED on 
      
      // Serial.print("Object detected at distance: ");
      // Serial.println(distance);
    }
    else
    {
      front_right=0;
      
      digitalWrite(led_front_right, LOW); // Turn the LED off
    }
    
    delay(65); // Delay between scans
    
    
    
    
    
    
    distance = detectObject(trigPin_left, echoPin_left); // Get distance from sensor
    if (distance > 0 && distance <= 140) {
      
      left=1;
      
      digitalWrite(led_left, HIGH); // Turn the LED on 
      
      // Serial.print("Object detected at distance: ");
      // Serial.println(distance);
    }
    else
    {
      left=0;
      
      digitalWrite(led_left, LOW); // Turn the LED off
    }
    
    delay(65); // Delay between scans
    
    


    distance = detectObject(trigPin_right, echoPin_right); // Get distance from sensor
    if (distance > 0 && distance <= 140) {
      
      right=1;
      
      digitalWrite(led_right, HIGH); // Turn the LED on 
      
      // Serial.print("Object detected at distance: ");
      // Serial.println(distance);
    }
    else
    {
      right=0;
      
      digitalWrite(led_right, LOW); // Turn the LED off
    }
    
    delay(65); // Delay between scans
    
  }