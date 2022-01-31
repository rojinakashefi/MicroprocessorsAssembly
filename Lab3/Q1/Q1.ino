#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
//define a lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte col = 0;
byte row = 0;

void setup() {
  //begin lcd with size of 16x2
  lcd.begin(16, 2);
  //clear lcd screen
  lcd.clear();
}

void loop() {
  lcd.clear();
  //define where the cursor should start
  lcd.setCursor(col, row);
  //print a text
  lcd.print("Rojina kashefi");
  //increase in line
  col++;
  //if we have iterated all coloums
  if (col == 16)
  {
    //make coloum 0
    col = 0;
    //switch between rows
    //if row 0 then row 1
    //if row 1 then row 0
    row = 1 - row;
  }
  delay(100);

}
