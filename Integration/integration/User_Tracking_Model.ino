
#include <string.h>





void checkSerial(Stream &serialPort, String s, byte anchorNum) {

  if (serialPort.available()) {
    s = serialPort.readStringUntil('\n'); // read the string
    //Serial.println(s);

    if(s.startsWith("+ANCHOR_RCV")){
      //Serial.println(s);

      dists[anchorNum] = s.substring(s.lastIndexOf(',') + 1).toInt(); // Obtain the distance value

      if (anchorNum == 0) {
        // Ignore outliers and sensor fluctuation
        if (abs(s.substring(s.lastIndexOf(',') + 1).toInt() - lastReading0) < 100 || s.substring(s.lastIndexOf(',') + 1).toInt() > 0) {
          distLogs[anchorNum][oldestIndex0] = s.substring(s.lastIndexOf(',') + 1).toInt();
          lastReading0 = distLogs[anchorNum][oldestIndex0];
          oldestIndex0++;
          if (oldestIndex0 >= samples) {
            oldestIndex0 = 0;
          }
        }
        
      }
      else {
        // Ignore outliers and sensor fluctuation
        if (abs(s.substring(s.lastIndexOf(',') + 1).toInt() - lastReading1) < 100 || s.substring(s.lastIndexOf(',') + 1).toInt() > 0) {
          distLogs[anchorNum][oldestIndex1] = s.substring(s.lastIndexOf(',') + 1).toInt();
          lastReading1 = distLogs[anchorNum][oldestIndex1];
          oldestIndex1++;
          if (oldestIndex1 >= samples) {
            oldestIndex1 = 0;
          }
        }     
      }

      // Update last time reading
      lastSample = millis();
      
      
      //Serial.println(dists[anchorNum]);
    } else {
      // Serial.println(s);
    }
    
    
  }
}



// void calculateAverage() {
//   for (int axis = 0; axis < anchorCount; axis++) {
//     float sum = 0, mean = 0;
//     for (int i = 0; i < samples; i++) {
//       sum += distLogs[axis][i];
//     }
//     mean = sum / samples;

//     dists[axis] = mean;
//   }
// }

void calculateAverage() {
  for (int axis = 0; axis < 2; axis++) {
    float sum = 0, mean = 0, sd = 0;
    int validCount = 0;

    // Step 1: Compute the mean
    for (int i = 0; i < samples; i++) {
      sum += distLogs[axis][i];
    }
    mean = sum / samples;

    // Step 2: Compute standard deviation
    sum = 0;
    for (int i = 0; i < samples; i++) {
      sum += (distLogs[axis][i] - mean) * (distLogs[axis][i] - mean);
    }
    sd = sqrt(sum / samples);

    // Step 3: Filter out outliers (keep values within 2× SD of the mean)
    sum = 0;
    validCount = 0;
    for (int i = 0; i < samples; i++) {
      if (abs(distLogs[axis][i] - mean) <= 2 * sd) {
        sum += distLogs[axis][i];
        validCount++;
      }
    }

    // Step 4: Compute new average (if no valid values, fallback to original mean)
    dists[axis] = (validCount > 0) ? (sum / validCount) : mean;
  }
}








void sendSerialData(Stream &serialPort, String command) {
  serialPort.print(command);
}

void resetDevice() {
  digitalWrite(resetPin1, LOW);  // Set the pin low to trigger the resetPin1
  digitalWrite(resetPin2, LOW);  // Set the pin low to trigger the reset
  delay(100);                    // Wait for 100 ms (adjust as needed for your device)
  digitalWrite(resetPin1, HIGH); // Set the pin high to release the reset
  digitalWrite(resetPin2, HIGH); // Set the pin high to release the reset
}


