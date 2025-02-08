
#include <string.h>

const byte resetPin = 50;

long dists[] = {15, 15};

// Keep track of the last five readings
long distLogs[][5] = {{100, 100, 100, 100, 100}, {100, 100, 100, 100, 100}};
int oldestIndex0 = 0;
int oldestIndex1 = 0;
long lastReading0 = 100;
long lastReading1 = 100;

void checkSerial(Stream &serialPort, String &s, byte anchorNum) {

  if (serialPort.available()) {
    s = serialPort.readStringUntil('\n'); // read the string
    //Serial.println(s);

    if(s.startsWith("+ANCHOR_RCV")){
      //Serial.println(s);

      dists[anchorNum] = s.substring(s.lastIndexOf(',') + 1).toInt(); // Obtain the distance value
//
//      if (anchorNum == 0) {
//        // Ignore outliers and sensor fluctuation
//        if (abs(s.substring(s.lastIndexOf(',') + 1).toInt() - lastReading0) < 100 || s.substring(s.lastIndexOf(',') + 1).toInt() > 0) {
//          distLogs[anchorNum][oldestIndex0] = s.substring(s.lastIndexOf(',') + 1).toInt();
//          lastReading0 = distLogs[anchorNum][oldestIndex0];
//          oldestIndex0++;
//          if (oldestIndex0 >= 5) {
//            oldestIndex0 = 0;
//          }
//        }
//        
//      }
//      else {
//        // Ignore outliers and sensor fluctuation
//        if (abs(s.substring(s.lastIndexOf(',') + 1).toInt() - lastReading1) < 100 || s.substring(s.lastIndexOf(',') + 1).toInt() > 0) {
//          distLogs[anchorNum][oldestIndex1] = s.substring(s.lastIndexOf(',') + 1).toInt();
//          lastReading1 = distLogs[anchorNum][oldestIndex1];
//          oldestIndex1++;
//          if (oldestIndex1 >= 5) {
//            oldestIndex1 = 0;
//          }
//        }     
//      }
      
      
      //Serial.println(dists[anchorNum]);
    } else {
      //Serial.println(s);
    }
    
    
  }
}

void calculateAverage() {
  dists[0] = (distLogs[0][0] + distLogs[0][1] + distLogs[0][2] + distLogs[0][3] + distLogs[0][4])/5;
  dists[1] = (distLogs[1][0] + distLogs[1][1] + distLogs[1][2] + distLogs[1][3] + distLogs[1][4])/5;
  
}




void sendSerialData(Stream &serialPort, String &command) {
  serialPort.print(command);
}

void resetDevice() {
  digitalWrite(resetPin, LOW);  // Set the pin low to trigger the reset
  delay(100);                    // Wait for 50 ms (adjust as needed for your device)
  digitalWrite(resetPin, HIGH); // Set the pin high to release the reset
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
String command = "AT+ANCHOR_SEND=TAG001,4,TEST\r\n";

void loop() {


  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial2, command);
  //delay(10);
  checkSerial(Serial2, message, 0);
  checkSerial(Serial2, message, 0);
  delay(50);

  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial3, command);
  //delay(10);
  checkSerial(Serial3, message, 1);
  checkSerial(Serial3, message, 1);
  delay(100);

//  // Print out the last three readings
//  Serial.println("PRINTING LAST THREE");
//  for (int i = 0; i < 2; i++) {
//    for (int j = 0; j < 5; j++) {
//      Serial.println(distLogs[i][j]);
//    }
//  }
//  Serial.println("DONE");

  // Calculate average of last three readings
//  calculateAverage();/

  bilaterate(dists[0], dists[1]);

}
