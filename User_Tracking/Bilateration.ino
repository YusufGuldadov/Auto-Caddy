#include <math.h>

void bilaterate(long d1, long d2) {
  //Serial.println(String(d1) + ", " + String(d2));

//  if((d1 - d2) > 30){
//    d1 = d2 + 30;
//  } else if ((d2 - d1) > 30){
//    d2 = d1 + 30;
//  }

//  if(abs(d1 - d2) > 30){
//    return;
//  }

    // Sensor positions
    const float x1 = -15.0;
    const float y1 = 0.0;
    const float x2 = 15.0;
    const float y2 = 0.0;

    // Bilateration calculations
    float A = 2 * (x2 - x1);
    float C = (d1 * d1) - (d2 * d2) - (x1 * x1) + (x2 * x2);

    if (A == 0) {
        return;
    }

    float x = C / A;
    float y_squared = (d1 * d1) - ((x - x1) * (x - x1));

    if (y_squared < 0) {
        return;
    }

    float y1_sol = sqrt(y_squared);

    // Calculate and print angle and distance for both solutions
    angle = atan2(y1_sol, x) * (180.0 / M_PI); // Convert to degrees
    distance = sqrt(x * x + y1_sol * y1_sol);

    //Serial.println(String(angle) + ", " + String(distance));
}

//void bilaterate(long d1, long d2) {
//  long numerator;
//  long denominator;
//
//  double alpha;
//  double y;
//  double x;
//
//  if (d1 > d2) {
//    numerator = (d2 * d2) - (d1 * d1) - (30 * 30);
//    denominator = -60 * d1;
//
//    alpha = acos((double)radians(numerator / denominator)); // Ensure proper division
//    y = d1 * sin(alpha);
//    x = d1 * sin(radians(90) - alpha) - 15;
//
//  } else {
//    numerator = (d1 * d1) - (d2 * d2) - (30 * 30);
//    denominator = -60 * d2;
//
//    alpha = acos((double)radians(numerator / denominator));
//    y = d2 * sin(alpha);
//    x = 15 - d2 * sin(radians(90) - alpha);
//  }
//
//  float distance = sqrt(x * x + y * y);
//  float angle = atan2(y, x) * (180.0 / M_PI); // Convert to degrees
//
//  Serial.println(String(angle) + ", " + String(distance));
//}

//
//void bilaterate(long d1, long d2) {
//  // Convert distances to double for floating-point math.
//  double r1 = (double)d1;
//  double r2 = (double)d2;
//  
//  // The two sensors are 30 units apart.
//  double d = 30.0;
//  
//  // Compute 'a' using the circle intersection formula.
//  // a is the distance from sensor 1 (at -15, 0) to the point directly below (or above) the target along the line connecting the sensors.
//  double a = (r1 * r1 - r2 * r2 + d * d) / (2.0 * d);
//  
//  // Compute the target's x-coordinate.
//  // Since sensor 1 is at (-15, 0), we add a to -15.
//  double x = -15.0 + a;
//  
//  // Compute the target's y-coordinate.
//  // If d1^2 - a^2 is negative (no intersection), we force y to 0.
//  double temp = r1 * r1 - a * a;
//  double y = (temp > 0) ? sqrt(temp) : 0.0;
//  
//  // Optionally, compute the overall distance and angle (in degrees) from the origin.
//  double distance = sqrt(x * x + y * y);
//  double angle = atan2(y, x) * (180.0 / M_PI);  // atan2 returns an angle in radians
//  
//  Serial.println(String(angle) + ", " + String(distance));
//}
