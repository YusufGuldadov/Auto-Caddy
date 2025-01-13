#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

boolean enteredDistances = true;

// club distances
int driver = 300;
int threeWood = 260;
int threeIron = 235;
int fourIron = 225;
int fiveIron = 215;
int sixIron = 200;
int sevenIron = 190;
int eightIron = 175;
int nineIron = 160;
int pWedge = 150;
int gapWedge = 135;
int sandWedge = 125;
int lobWedge = 110;

boolean distanceToHoleEntered = false;
int distanceToHole = 153;


void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

}


void loop()
{
  if (distanceToHoleEntered) {
    int driverDist = abs(driver - distanceToHole);
    int threeWoodDist = abs(threeWood - distanceToHole);
    int threeIronDist = abs(threeIron - distanceToHole);
    int fourIronDist = abs(fourIron - distanceToHole);
    int fiveIronDist = abs(fiveIron - distanceToHole);
    int sixIronDist = abs(sixIron - distanceToHole);
    int sevenIronDist = abs(sevenIron - distanceToHole);
    int eightIronDist = abs(eightIron - distanceToHole);
    int nineIronDist = abs(nineIron - distanceToHole);
    int pWedgeDist = abs(pWedge - distanceToHole);
    int gapWedgeDist = abs(gapWedge - distanceToHole);
    int sandWedgeDist = abs(sandWedge - distanceToHole);
    int lobWedgeDist = abs(lobWedge - distanceToHole);
    
    
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Enter distance:");
    lcd.setCursor(0,1);
    lcd.blink();
  }

  delay(500); // prevent overheating
}
