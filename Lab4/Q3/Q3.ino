#include <Servo.h>

Servo servo;  // create servo object to control a servo

int degree;

void setup() {
  Serial.begin(9600);
   // attaches the servo on pin 2 to the servo object
  servo.attach(2); 
}

void loop() {
  //check if there is anything availavle on terminal
  if (Serial.available() > 0) {
    //convert to int 
    degree = Serial.parseInt();
    // the number must be bigger than 0
    // negative numbers == numbers bigger than 180
    if (degree > 0) {
      // read the current value + the new degree 
      // the value is negative the symmetry is positive
      if (degree > 180) {
        servo.writeMicroseconds(servo.readMicroseconds() + float(degree - 180) / 360 * 1000);
      }
      else {
        // devide to 360 because to see the degree between 0 to 360
        // multiply with 1000 to put it in range of 1000 till 2000
        // the value is positive the symmetry is negative
        servo.writeMicroseconds(servo.readMicroseconds() - float(degree) / 360 * 1000);
      }
      Serial.println(degree);
      degree = 0;
    }
  }
}
