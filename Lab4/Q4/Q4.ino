#include <Servo.h>

Servo servo;
//PIN of potonsiometer on arduino
const int potpin = A0;
int val;

void setup() {
  Serial.begin(9600);
  servo.attach(2);
}

void loop() {
  //value of potonsiometer
  val = analogRead(potpin);
  Serial.println(val);
  //and convert it within number 1000 to 2000 (in range of servo)
  servo.writeMicroseconds(float(val) / 1024 * 1000 + 1000);
  delay(15);
}
