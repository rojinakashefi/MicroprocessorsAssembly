#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// pins of motor and servo motor
//servo for incline
//motor for speend
#define mup 3
#define mdown 4
#define sup 16
#define sdown 17

//% for incline
// = and + for speed

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '+'},
  {'4', '5', '6', '-'},
  {'1', '2', '3', '-'},
  {'#', '0', '*', '*'}
};
byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {23, 25, 27, 29};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


Servo servo;
int incline = 0;


int motor = 5;
int mspeed = 0;

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String number;

// lcd update
void editor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed:");
  lcd.print(mspeed);
  lcd.setCursor(0, 1);
  lcd.print("Incline:");
  lcd.print(incline);
}

void setup() {
  servo.attach(7);
  pinMode(motor, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  editor();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '+') {
      if (number.toInt() <= 45) {
        servo.writeMicroseconds(float(number.toInt()) / 360 * 1000 + 1500);
        incline = number.toInt();
        editor();
        number = "";
      }
    }
    else if (key == '*')
    {
      if (number.toInt() <= 255) {
        analogWrite(motor, number.toInt());
        mspeed = number.toInt();
        editor();
        number = "";
      }
    }
    else {
      number += key;
    }
  }
  // speed up
  // pull up when off
  // when on its 0
  if (digitalRead(mup) == 0) {
    if (mspeed <= 205) {
      mspeed = mspeed + 50;
      editor();
      analogWrite(motor, mspeed);
    }
    delay(250);
  }
  if (digitalRead(mdown) == 0) {
    if (mspeed >= 50) {
      mspeed = mspeed - 50;
      editor();
      analogWrite(motor, mspeed);
    }
    delay(250);
  }

  if (digitalRead(sup) == 0) {
    if (incline <= 40) {
      incline = incline + 5;
      editor();
      servo.writeMicroseconds(float(incline) / 360 * 1000 + 1500);
    }
    delay(250);
  }
  if (digitalRead(sdown) == 0) {
    if (incline >= 5) {
      incline = incline - 5;
      editor();
      servo.writeMicroseconds(float(incline) / 360 * 1000 + 1500);
    }
    delay(250);
  }
}
