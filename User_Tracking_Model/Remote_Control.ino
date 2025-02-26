

int xJoyStick;
int yJoyStick;

void moveCaddyRemote() {

  xJoyStick = map(analogRead(A0), 0, 720, -200, 200);
  yJoyStick = map(analogRead(A1), 0, 720, -200, 200);


  int an = atan2(yJoyStick, xJoyStick) * (180.0 / M_PI); // Convert to degrees
  float dis = sqrt((long)xJoyStick * xJoyStick + (long)yJoyStick * yJoyStick);

  Serial.println(String(dis) + ", " + String(an));
  // Serial.println(String(xJoyStick) + ", " + String(yJoyStick));
  // Serial.println(String(analogRead(A0)) + ", " + String(analogRead(A1)));
  if (dis < 100) dis = 0;

  an = abs(an);

    if(an < 15) {
      an = 0;
    } else if(an < 45) {
      an = 30;
    } else if(an < 75) {
      an = 60;
    } else if(an < 105) {
      an = 90;
    } else if(an < 135) {
      an = 120;
    } else if(an < 165) {
      an = 150;
    } else {
      an = 180;
    } 


  moveCaddy(dis/100.0, an);
  // moveCaddy(2, 90);


}