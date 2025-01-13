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

boolean distanceToHoleEntered = true;
int distanceToHole = 30;


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

    int distances[] = {
      driverDist,
      threeWoodDist,
      threeIronDist,
      fourIronDist,
      fiveIronDist,
      sixIronDist,
      sevenIronDist,
      eightIronDist,
      nineIronDist,
      pWedgeDist,
      gapWedgeDist,
      sandWedgeDist,
      lobWedgeDist
    };
    
 
    int clubSuggestion = findMinimum(distances, 13);
    

    if (clubSuggestion == driverDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("Driver: " + String(driver)); 
    }
    else if (clubSuggestion == threeWoodDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("3 Wood: " + String(threeWood)); 
    }
    else if (clubSuggestion == threeIronDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("3 Iron: " + String(threeIron)); 
    }
    else if (clubSuggestion == fourIronDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("4 Iron: " + String(fourIron)); 
    }
    else if (clubSuggestion == fiveIronDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("5 Iron: " + String(fiveIron)); 
    }
    else if (clubSuggestion == sixIronDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("6 Iron: " + String(sixIron)); 
    }
    else if (clubSuggestion == sevenIronDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("7 Iron: " + String(sevenIron)); 
    }
    else if (clubSuggestion == eightIronDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("8 Iron: " + String(eightIron)); 
    }
    else if (clubSuggestion == nineIronDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("9 Iron: " + String(nineIron)); 
    }
    else if (clubSuggestion == pWedgeDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("P Wedge: " + String(pWedge)); 
    }
    else if (clubSuggestion == gapWedgeDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("G Wedge: " + String(gapWedge)); 
    }
    else if (clubSuggestion == sandWedgeDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("S Wedge: " + String(sandWedge)); 
    }
    else if (clubSuggestion == lobWedgeDist) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suggestion:");
      lcd.setCursor(0,1);
      lcd.print("L Wedge: " + String(lobWedge)); 
    }



    delay(5000);
    distanceToHoleEntered = false;
    lcd.clear();
    
    
    
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Enter distance:");
    lcd.setCursor(0,1);
    lcd.blink();
  }

  delay(500); // prevent overheating
}


// Function for finding the min distance
int findMinimum(int values[], int size) {
    int minValue = values[0];
    for (int i = 1; i < size; i++) {
        if (values[i] < minValue) {
            minValue = values[i];
        }
    }
    return minValue;
}
