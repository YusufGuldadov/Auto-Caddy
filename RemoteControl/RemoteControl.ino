#include <SoftwareSerial.h>

const byte rx = 2;
const byte tx = 3;
const byte resetPin = 5;

SoftwareSerial UWBTag(rx, tx);


void checkSerial(Stream &serialPort) {

  if (serialPort.available()) {
    String s = serialPort.readStringUntil('\n'); // read the string
    Serial.println(s);
  }
}


void sendSerialData(Stream &serialPort, String command) {
  serialPort.print(command);
}



void setup() {
  Serial.begin(9600);//enable serial monitor
  UWBTag.begin(115200);
}
void loop() {
  unsigned int joy = analogRead(A0);  // Get analog value (0-1024)
  unsigned int joy1 = analogRead(A1); // Get analog value (0-1024)

  // Construct payload with comma separation
  String payload = String(joy) + String(joy1);

  // Calculate payload length dynamically
  int payloadLength = payload.length();

  String msg = "AT+TAG_SEND=" + String(payloadLength) + "," + payload + "\r\n";

  checkSerial(UWBTag);
  checkSerial(UWBTag);

  // Construct and send the full AT command
  sendSerialData(UWBTag, msg);

  Serial.println(msg);

  // for(int i = 0; i < 4; i++){
  //   Serial.print(String(i)+": " + buff[i]);//space
  // }

  // Serial.println("");

  checkSerial(UWBTag);
  



  delay(100);//delay
}