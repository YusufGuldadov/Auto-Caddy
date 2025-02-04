#include <SoftwareSerial.h>

// Define the pins for the Sunfounder Joystick Module
const int joystickXPin = A0;  // X-axis analog pin
const int joystickYPin = A1;  // Y-axis analog pin
const int joystickSWPin = 2;  // Switch (button) digital pin


void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);

  // Initialize the SoftwareSerial for UWB communication
  Serial.begin(115200);

  sendSerialData(Serial, "AT+MODE=0"); // Set Tag mode
  delay(1000);
  sendSerialData(Serial, "AT+NETWORKID=Autoca1"); // Set network ID
  delay(1000);
  sendSerialData(Serial, "AT+ADDRESS=TAG001"); // Set Tag address
  delay(1000);
  sendSerialData(Serial, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90"); // Set password
  delay(1000);

  // Set the joystick switch pin as input with pull-up resistor
  pinMode(joystickSWPin, INPUT_PULLUP);
}

void loop() {
  // Read the joystick values
  int joystickX = analogRead(joystickXPin);
  int joystickY = analogRead(joystickYPin);
  int joystickSW = digitalRead(joystickSWPin);

  // Convert the joystick values to bytes
  byte xHigh = highByte(joystickX);
  byte xLow = lowByte(joystickX);
  byte yHigh = highByte(joystickY);
  byte yLow = lowByte(joystickY);
  byte sw = joystickSW;

  // Create the payload (5 bytes: X, Y, SW)
  byte payload[5] = {xHigh, xLow, yHigh, yLow, sw};

  // Send the payload using the AT+TAG_SEND command
  sendPayload(payload, sizeof(payload));

  // Delay before sending the next payload
  delay(100);
}

void sendPayload(byte* payload, int payloadLength) {
  // Start the AT command
  Serial.print("AT+TAG_SEND=");

  // Send each byte of the payload
  for (int i = 0; i < payloadLength; i++) {
    if (payload[i] < 0x10) {
      Serial.print("0");  // Add leading zero for single-digit hex values
    }
    Serial.print(payload[i], HEX);
  }

  // End the AT command
  Serial.print("\r\n");

  // Print the payload to the Serial Monitor for debugging
  Serial.print("Sent Payload: ");
  for (int i = 0; i < payloadLength; i++) {
    Serial.print(payload[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}