#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Key.h>

// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad Configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Golf Club Distances
const int clubDistances[] = {300, 260, 235, 225, 215, 200, 190, 175, 160, 150, 135, 125, 110};
const char* clubNames[] = {"Driver", "3 Wood", "3 Iron", "4 Iron", "5 Iron", "6 Iron", "7 Iron", "8 Iron", "9 Iron", "P Wedge", "G Wedge", "S Wedge", "L Wedge"};

// State Variables
int distanceToHole = 0;
bool distanceToHoleEntered = false;
bool suggestionDisplayed = false;

void keypadLcdSetup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Distance:");
}

void keypadLcdTask() {
  char key = keypad.getKey();

  if (!distanceToHoleEntered && !suggestionDisplayed) {
    if (key) {
      if (key >= '0' && key <= '9') {
        distanceToHole = distanceToHole * 10 + (key - '0');
        lcd.setCursor(0, 1);
        lcd.print("Distance: ");
        lcd.print(distanceToHole);
      } else if (key == '#') {
        distanceToHoleEntered = true;
        lcd.clear();
        lcd.print("Calculating...");
        delay(1000);
        suggestClub();
      } else if (key == '*') {
        resetInput();
      }
    }
  } else if (suggestionDisplayed && key == '*') {
    resetInput();
  }
}

void resetInput() {
  distanceToHole = 0;
  distanceToHoleEntered = false;
  suggestionDisplayed = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Distance:");
}

void suggestClub() {
  int minDiff = abs(clubDistances[0] - distanceToHole);
  int bestIndex = 0;

  for (int i = 1; i < 13; i++) {
    int diff = abs(clubDistances[i] - distanceToHole);
    if (diff < minDiff) {
      minDiff = diff;
      bestIndex = i;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suggestion:");
  lcd.setCursor(0, 1);
  lcd.print(clubNames[bestIndex]);
  lcd.setCursor(0, 2);
  lcd.print("Dist: ");
  lcd.print(clubDistances[bestIndex]);

  suggestionDisplayed = true;
}
