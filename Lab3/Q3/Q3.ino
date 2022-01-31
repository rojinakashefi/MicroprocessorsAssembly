#include <LiquidCrystal.h>
#include <Keypad.h>
//define how many rows and coloums our keypad has
const byte ROWS = 4;
const byte COLS = 4;
//define values of keys on matrix
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'o', '0', '=', '+'}
};

byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

//make a keypad and lcd based on the pins
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//for calculation we need to operation
String op1, op2;
//operand we want to calculate
char op;
boolean op_entered = false;

//initialize lcd size 
//clear lcd
//put in first place
void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    lcd.print(key);
    //use o key for clearing all operations
    if (key == 'o')
    {
      op1 = "";
      op2 = "";
      op_entered = false;
      lcd.clear();
      lcd.setCursor(0, 0);
    }
    //use for calculate operation
    else if (key == '=')
    {
      int a = op1.toInt();
      int b = op2.toInt();
      //put in cursor in next row
      lcd.setCursor(0, 1);
      //based on operand do the calculation
      switch (op)
      {
        case '+':
          lcd.print(a + b);
          break;
        case '-':
          lcd.print(a - b);
          break;
        case '*':
          lcd.print(a * b);
          break;
        case '/':
          lcd.print((float)a / b);
          break;
      }
    }
    //write operand + - * /
    else if (!op_entered && (key == '+' || key == '-' || key == '*' || key == '/'))
    {
      op = key;
      op_entered = true;
    }
    //if there is no operand enterned it means it is the first number
    else if (! op_entered)
    {
      op1 += key;
    }
    //if operand has been enterd it is the second number
    else
    {
      op2 += key;
    }
  }
}
