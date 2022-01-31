#include <Servo.h>

Servo servo;  // create servo object to control a servo

int degree;

void setup() {
  Serial.begin(9600);
  servo.attach(2);  // attaches the servo on pin 2 to the servo object
}

//flag for when we write -
boolean flag = false;
// finish to say stop reading
boolean finish = false;
// the number we write
String number = "";
int num = 0;
void loop() {
  // while we are still reading
  if (! finish) {
    if (Serial.available() > 0) {
      char string = Serial.read();
      // if we have - make flag ture
      // the number is negative
      if (string == '-') {
        flag = true;
        // if we enter s 
        // means stop reading
      } else if (string == 's') {
        finish = true;
      } else {
        // add the char we are reading to number
        number = number + string;
      }
    }
  } else if (num == 0) {
    num = number.toInt();
    // convert our number to int
    // if we have -
    // make the number positve to negative
    if (! flag) {
      num = num * -1;
    }
    //sum the number with current value
    //devide to 360 to make it between 0 and 3600
    servo.writeMicroseconds(servo.readMicroseconds() + float(num) / 360 * 1000);
    finish = false;
    flag = false;
    number = "";
    num = 0;
  }
}
