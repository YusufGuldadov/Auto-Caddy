#include <math.h>

void bilaterate(long d1, long d2) {
  //Serial.println(String(d1) + ", " + String(d2));

    // Sensor positions
    const float x1 = -17.0;
    const float y1 = 0.0;
    const float x2 = 17.0;
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

