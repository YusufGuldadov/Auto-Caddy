#include <SoftwareSerial.h>
#include <string.h>

const int resetPin = 50;

unsigned long previousMillis = 0; // Store the last time the command was executed
const long interval = 100; // Interval to query distance (milliseconds)

void checkSerial(Stream &serialPort, String &s) {
  if (serialPort.available()) {
    s = serialPort.readString();

    if(s.startsWith("+OK\r\n+ANCHOR_RCV")){
      int dist = 0;
      parseDistance(s, dist);
      
      Serial.println(dist);
    } else {
      Serial.println(s);
    }
    
    
  }
}

void sendSerialData(Stream &serialPort, String &command) {
  serialPort.print(command);
}

void resetDevice() {
  digitalWrite(resetPin, LOW);  // Set the pin low to trigger the reset
  delay(50);                    // Wait for 50 ms (adjust as needed for your device)
  digitalWrite(resetPin, HIGH); // Set the pin high to release the reset
}


//void parseDistance(String &input, int &dist) {
//    // Find the position of the last comma
//    int lastComma = input.lastIndexOf(',');
//    
//    // If a valid comma is found
//    if (lastComma != -1) {
//        // Extract the substring after the last comma and remove " cm"
//        String distanceStr = input.substring(lastComma + 1);
//        distanceStr.trim(); // Remove any leading or trailing spaces
//        distanceStr.replace(" cm", ""); // Remove the " cm" suffix
//        
//        // Convert to integer
//        dist = distanceStr.toInt();
//    } 
//    else {
//        dist = -1; // Error value if parsing fails
//    }
//}


void parseDistance(const String &input, int &dist) {
  int len = input.length();
  int i = len - 1;

  // Skip any trailing whitespace.
  while (i >= 0 && isspace(input.charAt(i))) {
    i--;
  }

  // Check for and skip the "cm" suffix.
  // We expect a space before "cm" so the last 3 non-space characters should be " cm".
  if (i >= 2 && input.charAt(i-1) == 'c' && input.charAt(i) == 'm') {
    i -= 2; // Skip 'c' and 'm'
    // Skip any whitespace between the number and the "cm" suffix.
    while (i >= 0 && isspace(input.charAt(i))) {
      i--;
    }
  }

  // Now i is at the last digit of the number.
  int end = i;
  // Find the start of the digit sequence.
  while (i >= 0 && isDigit(input.charAt(i))) {
    i--;
  }
  int start = i + 1;

  // If no digit was found, return error.
  if (start > end) {
    dist = -1;
    return;
  }

  // Manually convert the digit characters into an integer.
  int number = 0;
  for (int j = start; j <= end; j++) {
    char c = input.charAt(j);
    if (!isDigit(c)) { // sanity check
      dist = -1;
      return;
    }
    number = number * 10 + (c - '0');
  }

  dist = number;
}


void setup() {
  pinMode(resetPin, OUTPUT); // Configure the pin as an output
  digitalWrite(resetPin, HIGH); // Ensure the pin is initially high (inactive)
  resetDevice();

  delay(50);

  Serial.begin(115200);
  Serial2.begin(115200); // Anchor setup on Serial2
  Serial3.begin(115200); // Tag setup on Serial3

  Serial.println("Setup Start\n");
  delay(100);

  // Configure Anchor (Serial2)
//  sendSerialData(Serial2, "AT+MODE=1"); // Set Anchor mode
//  delay(200);
//  sendSerialData(Serial2, "AT+NETWORKID=Autoca1"); // Set network ID
//  delay(200);
//  sendSerialData(Serial2, "AT+ADDRESS=ANCHOR01"); // Set Anchor address
//  delay(200);
//  sendSerialData(Serial2, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90"); // Set password
//  delay(200);
//  sendSerialData(Serial2, "AT+BANDWIDTH=1");
//  delay(200);
//  sendSerialData(Serial2, "AT+IPR=115200");
//  delay(200);

//  // Configure Tag (Serial3)
//  sendSerialData(Serial3, "AT+MODE=0"); // Set Tag mode
//  delay(1000);
//  sendSerialData(Serial3, "AT+NETWORKID=Autoca1"); // Set network ID
//  delay(1000);
//  sendSerialData(Serial3, "AT+ADDRESS=TAG001"); // Set Tag address
//  delay(1000);
//  sendSerialData(Serial3, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90"); // Set password
//  delay(1000);
//  sendSerialData(Serial3, "AT+BANDWIDTH=1"); 
//  delay(1000);
//  sendSerialData(Serial3, "AT+IPR=115200");
//  delay(1000);

//  sendSerialData(Serial3, "AT+MODE=1"); // Set Anchor mode
//  delay(200);
//  sendSerialData(Serial3, "AT+NETWORKID=Autoca1"); // Set network ID
//  delay(200);
//  sendSerialData(Serial3, "AT+ADDRESS=ANCHOR02"); // Set Anchor address
//  delay(200);
//  sendSerialData(Serial3, "AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90"); // Set password
//  delay(200);
//  sendSerialData(Serial3, "AT+BANDWIDTH=1"); 
//  delay(200);
//  sendSerialData(Serial3, "AT+IPR=115200");
//  delay(200);

  Serial.println("Setup Complete\n");
}

String message;
String command = "AT+ANCHOR_SEND=TAG001,1,T\r\n";

void loop() {


  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial2, command);
  delay(10);

  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial3, command);
  delay(20);

  // Check for incoming serial data
  checkSerial(Serial2, message);
  checkSerial(Serial3, message);

}
