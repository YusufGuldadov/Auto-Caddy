#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20x4 display

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};   // R1, R2, R3, R4
byte colPins[COLS] = {8, 9, 10, 11}; // C1, C2, C3, C4
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Golf club distances
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

int distanceToHole = 0;               // Distance entered via keypad
boolean distanceToHoleEntered = false; // Flag to check if distance is entered
boolean suggestionDisplayed = false;  // Flag to check if suggestion is displayed

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Distance:");
}

void loop() {
  char key = keypad.getKey();

  if (!distanceToHoleEntered && !suggestionDisplayed) {
    // Handle distance input
    if (key) {
      if (key >= '0' && key <= '9') {
        // Append digit to distance
        distanceToHole = distanceToHole * 10 + (key - '0');
        lcd.setCursor(0, 1);
        lcd.print("Distance: ");
        lcd.print(distanceToHole);
      } else if (key == '#') {
        // Confirm input
        distanceToHoleEntered = true;
        lcd.clear();
        lcd.print("Calculating...");
        delay(1000);
        suggestClub();
      } else if (key == '*') {
        // Clear input and prompt to re-enter
        resetInput();
      }
    }
  } else if (suggestionDisplayed && key == '*') {
    // Reset when "*" is pressed after suggestion is displayed
    resetInput();
  }
}

// Function to reset input and prompt for a new distance
void resetInput() {
  distanceToHole = 0;
  distanceToHoleEntered = false;
  suggestionDisplayed = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Distance:");
}

// Function to suggest a club
void suggestClub() {
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
    driverDist, threeWoodDist, threeIronDist, fourIronDist,
    fiveIronDist, sixIronDist, sevenIronDist, eightIronDist,
    nineIronDist, pWedgeDist, gapWedgeDist, sandWedgeDist,
    lobWedgeDist
  };

  int clubSuggestion = findMinimum(distances, 13);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suggestion:");

  lcd.setCursor(0, 1);
  if (clubSuggestion == driverDist) lcd.print("Driver"), lcd.setCursor(0, 2), lcd.print("Dist: 300");
  else if (clubSuggestion == threeWoodDist) lcd.print("3 Wood"), lcd.setCursor(0, 2), lcd.print("Dist: 260");
  else if (clubSuggestion == threeIronDist) lcd.print("3 Iron"), lcd.setCursor(0, 2), lcd.print("Dist: 235");
  else if (clubSuggestion == fourIronDist) lcd.print("4 Iron"), lcd.setCursor(0, 2), lcd.print("Dist: 225");
  else if (clubSuggestion == fiveIronDist) lcd.print("5 Iron"), lcd.setCursor(0, 2), lcd.print("Dist: 215");
  else if (clubSuggestion == sixIronDist) lcd.print("6 Iron"), lcd.setCursor(0, 2), lcd.print("Dist: 200");
  else if (clubSuggestion == sevenIronDist) lcd.print("7 Iron"), lcd.setCursor(0, 2), lcd.print("Dist: 190");
  else if (clubSuggestion == eightIronDist) lcd.print("8 Iron"), lcd.setCursor(0, 2), lcd.print("Dist: 175");
  else if (clubSuggestion == nineIronDist) lcd.print("9 Iron"), lcd.setCursor(0, 2), lcd.print("Dist: 160");
  else if (clubSuggestion == pWedgeDist) lcd.print("P Wedge"), lcd.setCursor(0, 2), lcd.print("Dist: 150");
  else if (clubSuggestion == gapWedgeDist) lcd.print("G Wedge"), lcd.setCursor(0, 2), lcd.print("Dist: 135");
  else if (clubSuggestion == sandWedgeDist) lcd.print("S Wedge"), lcd.setCursor(0, 2), lcd.print("Dist: 125");
  else if (clubSuggestion == lobWedgeDist) lcd.print("L Wedge"), lcd.setCursor(0, 2), lcd.print("Dist: 110");

  suggestionDisplayed = true;
}

// Function to find the minimum distance
int findMinimum(int values[], int size) {
  int minValue = values[0];
  for (int i = 1; i < size; i++) {
    if (values[i] < minValue) {
      minValue = values[i];
    }
  }
  return minValue;
}

