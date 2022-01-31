#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {25, 26, 27, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 23, 24}; //connect to the column pinouts of the keypad

const byte ledPins[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  for (byte i = 0; i < 9; i++)
    pinMode(ledPins[i], OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    for (byte i = 0; i < 9; i++)
      digitalWrite(ledPins[i], LOW);
    for (byte i = 0; i < key - '0'; i++)
      digitalWrite(ledPins[i], HIGH);
  }
}
