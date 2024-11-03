#include <Keypad.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ID_LENGTH = 11; // Maximum length for user IDs
const int MAX_IDS = 100;  // Maximum number of user IDs

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'/', '0', '-', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Function to save a new user ID in EEPROM
void saveUserID(String userID) {
  int address = findNextFreeAddress();
  if (address == -1) {
    lcd.clear();
    lcd.print("Memory full!");
    return;
  }
  
  for (int i = 0; i < userID.length(); i++) {
    EEPROM.write(address + i, userID[i]);
  }
  EEPROM.write(address + userID.length(), '\0'); // Null terminator
  Serial.println("User ID saved!");
}

// Function to check if the user ID is unique
bool isUniqueUserID(String userID) {
  for (int i = 0; i < MAX_IDS; i++) {
    int address = i * (ID_LENGTH + 1);
    String storedID = readUserID(address);
    if (storedID == userID) {
      return false; // ID already exists
    }
  }
  return true;
}

// Function to find the next free address in EEPROM
int findNextFreeAddress() {
  for (int i = 0; i < MAX_IDS; i++) {
    int address = i * (ID_LENGTH + 1);
    if (EEPROM.read(address) == 0xFF) { // Empty slot found
      return address;
    }
  }
  return -1; // No space left
}

// Function to read a user ID from EEPROM
String readUserID(int address) {
  String userID = "";
  for (int i = 0; i < ID_LENGTH; i++) {
    char ch = EEPROM.read(address + i);
    if (ch == '\0') break;
    userID += ch;
  }
  return userID;
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  String userID = "";
  lcd.clear();
  lcd.print("Enter User ID:");

  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == 'A') { // 'A' to submit
        break;
      } else if (key == 'B') { // 'B' to clear
        userID = "";
        lcd.setCursor(0, 1);
        lcd.print("            "); // Clear line
        lcd.setCursor(0, 1);
      } else {
        if (userID.length() < ID_LENGTH) { // Limit input length
          userID += key;
          lcd.setCursor(0, 1);
          lcd.print(userID); // Display ID input
        }
      }
    }
  }

  Serial.println("User ID Entered: " + userID);

  if (isUniqueUserID(userID)) {
    saveUserID(userID);
    lcd.clear();
    lcd.print("ID registered!");
  } else {
    lcd.clear();
    lcd.print("ID already exists!");
  }

  delay(2000); // Display message briefly
  lcd.clear();
}

    lcd.clear();
    lcd1.clear();
  }
}
