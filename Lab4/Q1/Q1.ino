#include <Servo.h>

Servo servo;
void setup() {
  //pin of servo attached to bord
  servo.attach(2);
}

void loop() {
  //1000 means -180 degree
  //2000 means 180 degree
  //switches between 0 and 90
  //1500 means 0 degree
  //1750 means 90 degree
  servo.writeMicroseconds(1500);
  delay(500);
  servo.writeMicroseconds(1750);
  delay(500);
}
