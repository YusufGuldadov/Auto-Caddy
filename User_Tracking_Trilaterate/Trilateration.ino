// Define anchor points
struct Point {
  float x;
  float y;
};


Point A = {17.0, 0.0};   // Anchor 1 (right)
Point B = {-17.0, 0.0};   // Anchor 2 (left)
Point C = {0.0, 17};   // Anchor 3 (middle)



// Trilateration function to compute distance and angle to target
void trilaterate(float r1, float r2, float r3) {
  float A_ = 2 * (B.x - A.x);
  float B_ = 2 * (B.y - A.y);
  float C_ = r1 * r1 - r2 * r2 - A.x * A.x + B.x * B.x - A.y * A.y + B.y * B.y;
  float D = 2 * (C.x - A.x);
  float E = 2 * (C.y - A.y);
  float F = r1 * r1 - r3 * r3 - A.x * A.x + C.x * C.x - A.y * A.y + C.y * C.y;

  float x = (C_ * E - F * B_) / (A_ * E - B_ * D);
  float y = (C_ * D - A_ * F) / (B_ * D - A_ * E);

  distance = sqrt(x * x + y * y);
  angle = atan2(y, x) * (180.0 / M_PI);

  // return {distance, angle};
}