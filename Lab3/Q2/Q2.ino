#include <LiquidCrystal.h>
#include <Keypad.h>

//define row sizes keypad
const byte ROWS = 4; 

//define col sizes of keypad 
const byte COLS = 4;

//define keypad values
//we only use # for clearing
//and numbers for writing passwords
//and * to check if password is correct or not
//we dont do operations
char keys[ROWS][COLS] = {
  {'7', '8', '9', '*'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '*'},
  {'#', '0', '*', '*'}
};

//define pins of rows
byte rowPins[ROWS] = {31, 33, 35, 37};

//define pins of cols
byte colPins[COLS] = {23, 25, 27, 29};
//define lcd pins
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

//creating keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//creating an lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//show which col we are
byte col = 0;
//password we want to check its value we wirte on lcd
String password;

void setup() {
  //start lcd work with size of 16x2
  lcd.begin(16, 2);
  //clear lcd page
  lcd.clear();
}

void loop() {
  //we will set the cursor wherever our col
  //increase col,character by character
  lcd.setCursor(col, 0);
  //get key value which is pressed
  char key = keypad.getKey();
  if (key) {
    //use to clear page and set password to nothing
    if (key == '#') {
      lcd.clear();
      col = 0;
      password = "";
    }
    //check password
    else if (key == '*')
    {
      //put cursor in a new line
      //to print in a new line
      lcd.setCursor(0, 1);
      if (password == "9831118") {
        lcd.print("Correct password");
        password = "";
      } else {
        lcd.print("Wrong password");
        password = "";
      }
    } else {
      //write key on lcd
      lcd.print(key);
      //add each key to end of password
      password += key;
      //increase col
      col++;
    }
  }
}
