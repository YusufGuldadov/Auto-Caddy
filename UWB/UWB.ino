#include <SoftwareSerial.h>

const int resetPin = 50;

unsigned long previousMillis = 0; // Store the last time the command was executed
const long interval = 100; // Interval to query distance (milliseconds)

void checkSerial(Stream &serialPort) {
  if (serialPort.available()) {
    Serial.println(serialPort.readString());
  }
}

void sendSerialData(Stream &serialPort, String command) {
  command += "\r\n";
  char *buf = (char *)malloc(sizeof(char) * (command.length() + 1));
  command.toCharArray(buf, command.length() + 1);
  serialPort.write(buf);
  free(buf);

  checkSerial(serialPort);
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
  Serial3.begin(115200); // Tag setup on Serial3

  Serial.println("Setup Start\n");
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

  // Configure Tag (Serial3)
  sendSerialData(Serial3, "AT+MODE=0"); // Set Tag mode
  delay(1000);
  sendSerialData(Serial3, "AT+NETWORKID=Autoca1"); // Set network ID
  delay(1000);
  sendSerialData(Serial3, "AT+ADDRESS=TAG001"); // Set Tag address
  delay(1000);
  sendSerialData(Serial3, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90"); // Set password
  delay(1000);

  Serial.println("Setup Complete\n");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Send data from Anchor to Tag and request distance
    sendSerialData(Serial2, "AT+ANCHOR_SEND=TAG001,4,TEST");
  }

  // Check and print responses from Anchor (Serial2)
  checkSerial(Serial2);

  // Check and print responses from Tag (Serial3)
  checkSerial(Serial3);

  // Pass-through: send commands from Serial Monitor to UWB modules for debugging
  if (Serial.available()) {
    String content = Serial.readString();
    content.trim();
    sendSerialData(Serial2, content);
  }
}
