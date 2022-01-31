#include <Keypad.h>
#include <Servo.h>

//our keypad has 4 row and 4 col
//write value of each key in matrix

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '*'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '*'},
  {'o', '0', '*', '*'}
};
//row and col pins
byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {23, 25, 27, 29};
//initialize keypad
//initialize servo
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Servo servo;
String degree;
//attach pin of servo
void setup() {
  servo.attach(2);
}

void loop() {
  //get a key from keypad
  char key = keypad.getKey();
  //if there was a key 
  if (key) {
    //* means to change servo 
    if (key == '*')
    {
      //if degree bigger than 180 it means its between 0 till -180
      if (degree.toInt() > 180) {
        // first we reduce 180 degree
        //asume it is between 0 and 180
        //devide it to 360 to fits in 0 till 360 degree
        // * 1000 to fits between 1000 till 2000
        // * -1 to reduce it from 1500 and put it between begative range (-180 to 0 )
        //then we multiply it * -1
        servo.writeMicroseconds(-(float(degree.toInt() - 180) / 360 * 1000) + 1500);
      }
      //if smaller than 180 it means its between 0 till 180 
      else {
        //we should devide it to 360 to fit it in scale of servo 
        //* 1000 to give a number which we add with 1500 its between 1500 till 2000 ( positive numbers 0 till 180)
        servo.writeMicroseconds(float(degree.toInt()) / 360 * 1000 + 1500);
      }
      degree = "";
    }
    //if it was a number it means we are saying what degree we want to change
    else if (key >= '0' && key <= '9')
    {
      degree += key;
    }
  }
}
