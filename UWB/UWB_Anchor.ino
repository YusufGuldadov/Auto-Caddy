#include <SoftwareSerial.h>

const int resetPin = 50; // Pin for resetting the UWB module

unsigned long previousMillis = 0; // Store the last time the command was executed
const long interval = 100; // Interval to check for incoming data (milliseconds)

// Function prototype for driverCaddy
void driverCaddy(float speed, int angle);

void checkSerial(Stream &serialPort) {
  if (serialPort.available()) {
    String receivedData = serialPort.readStringUntil('\n');
    receivedData.trim(); // Remove any extra whitespace or newline characters

    // Check if the received data is from the tag
    if (receivedData.startsWith("AT+TAG_SEND=")) {
      // Extract the payload (hexadecimal string)
      String payloadHex = receivedData.substring(12);

      // Convert the hexadecimal payload to bytes
      byte payload[5];
      for (int i = 0; i < 5; i++) {
        payload[i] = (byte) strtol(payloadHex.substring(i * 2, i * 2 + 2).c_str(), NULL, 16);
      }

      // Extract joystick values from the payload
      int joystickX = (payload[0] << 8) | payload[1];  // Combine high and low bytes for X
      int joystickY = (payload[2] << 8) | payload[3];  // Combine high and low bytes for Y
      int joystickSW = payload[4];                     // Switch value

      // Map joystick values to speed (0 - 6) and angle (-90 to 90)
      float speed = map(joystickY, 0, 1023, 0, 6);      // Map Y-axis to speed
      int angle = map(joystickX, 0, 1023, -90, 90);     // Map X-axis to angle

      // Call the driverCaddy function with the calculated speed and angle
      driverCaddy(speed, angle);

      // Print the received data for debugging
      Serial.print("Received Payload: ");
      for (int i = 0; i < 5; i++) {
        Serial.print(payload[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      Serial.print("Speed: ");
      Serial.print(speed);
      Serial.print(", Angle: ");
      Serial.println(angle);
    }
  }
}

void sendSerialData(Stream &serialPort, String command) {
  command += "\r\n";
  char *buf = (char *)malloc(sizeof(char) * (command.length() + 1));
  command.toCharArray(buf, command.length() + 1);
  serialPort.write(buf);
  free(buf);
}

void resetDevice() {
  digitalWrite(resetPin, LOW);  // Set the pin low to trigger the reset
  delay(50);                    // Wait for 50 ms (adjust as needed for your device)
  digitalWrite(resetPin, HIGH); // Set the pin high to release the reset
}

void setup() {
  pinMode(resetPin, OUTPUT); // Configure the pin as an output
  digitalWrite(resetPin, HIGH); // Ensure the pin is initially high (inactive)
  resetDevice();

  delay(500);

  Serial.begin(115200);
  Serial2.begin(115200); // Anchor setup on Serial2

  Serial.println("Anchor Setup Start\n");
  delay(1000);

  // Configure Anchor (Serial2)
  sendSerialData(Serial2, "AT+MODE=1"); // Set Anchor mode
  delay(1000);
  sendSerialData(Serial2, "AT+NETWORKID=Autoca1"); // Set network ID
  delay(1000);
  sendSerialData(Serial2, "AT+ADDRESS=ANCHOR001"); // Set Anchor address
  delay(1000);
  sendSerialData(Serial2, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90"); // Set password
  delay(1000);

  Serial.println("Anchor Setup Complete\n");
}

void loop() {
  unsigned long currentMillis = millis();

  // Check for incoming data from the UWB module
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    checkSerial(Serial2); // Check for data from the anchor
  }

  // Pass-through: send commands from Serial Monitor to UWB module for debugging
  if (Serial.available()) {
    String content = Serial.readString();
    content.trim();
    sendSerialData(Serial2, content);
  }
}

// Function to control the driver caddy (implementation not provided)
void driverCaddy(float speed, int angle) {
  // Placeholder for the driverCaddy function implementation

  Serial.print("Driver Caddy - Speed: ");
  Serial.print(speed);
  Serial.print(", Angle: ");
  Serial.println(angle);
}