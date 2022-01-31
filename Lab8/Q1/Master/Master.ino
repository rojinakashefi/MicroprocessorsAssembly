#include <SPI.h>

#define MESSAGE "Rojina kashefi 9831118\r"

//slave select pin
const int SS_PIN = 45;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting master");
  // set slave select as output
  pinMode(SS_PIN, OUTPUT);
  // slave select is pull up
  digitalWrite(SS_PIN, HIGH);
  //the portocolstarts and initialize registers
  SPI.begin();
}

void loop() {
  // when slave selects its active low
  digitalWrite(SS_PIN, LOW);
  delay(10);
  // send a message char by char
  for (const char *p = MESSAGE ; char c = *p; p++) {
    SPI.transfer(c);
    Serial.print(c);
    delay(5);
  }
  Serial.println();
  // after sending make slave select high
  digitalWrite(SS_PIN, HIGH);
  delay(1000);
}
