#include <LiquidCrystal.h>
#include <Keypad.h>

//make a lcd with pins
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

boolean flag = false;
char incomingByte;
int col = 0;
int row = 0;

void setup() {
  //shows to speed of exchanging of data with terminal 
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}
void loop() {
  //if it hasnt read anything make flag =true
  //read the incoming byte
  if (Serial.available() > 0 && !flag) {
    incomingByte = Serial.read();
    flag = true;
    col = 0;
    row = 0;
  }
  //clear lcd
  lcd.clear();
  //set the cursor place
  lcd.setCursor(col, row);
  //shows incoming byte
  lcd.print(incomingByte);
  //go between coloums if reached end go to first
  col++;
  if (col == 16) {
    col = 0;
  }
  //switch between lines
  row = 1 - row;
  delay(300);
}
