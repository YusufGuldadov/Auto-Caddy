
#include <string.h>

const byte resetPin = 50;

long dists[] = {15, 15};

void checkSerial(Stream &serialPort, String &s, byte anchorNum) {

  if (serialPort.available()) {
    s = serialPort.readStringUntil('\n'); // Leer la respuesta del módulo
    //Serial.println(s);

    if(s.startsWith("+ANCHOR_RCV")){
      //Serial.println(s);

      dists[anchorNum] = s.substring(s.lastIndexOf(',') + 1).toInt(); // Obtener la distancia
      
      //Serial.println(dists[anchorNum]);
    } else {
      //Serial.println(s);
    }
    
    
  }
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
  delay(10);
  checkSerial(Serial2, message, 0);
  delay(20);

  // Send data from Anchor to Tag and request distance
  sendSerialData(Serial3, command);
  delay(10);
  checkSerial(Serial3, message, 1);
  delay(90);

  bilaterate(dists[0], dists[1]);

}
