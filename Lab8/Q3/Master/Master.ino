#include <SPI.h>

#define MESSAGE0   "Rojina kashefi!\r"
#define MESSAGE1   "Hello Rojina!\r"

//two slaves two slave select
const int SS0_PIN = 44, SS1_PIN = 45;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting master");

  pinMode(SS0_PIN, OUTPUT);
  digitalWrite(SS0_PIN, HIGH);

  pinMode(SS1_PIN, OUTPUT);
  digitalWrite(SS1_PIN, HIGH);

  SPI.begin();
}

//send messages char by char
void sendMessage(const char *message) {
  for (const char *p = message ; char c = *p; p++) {
    SPI.transfer(c);
    delay(5);
  }
}

void loop() {
  //write message0 on slave 1
  digitalWrite(SS0_PIN, LOW);
  sendMessage(MESSAGE0);
  digitalWrite(SS0_PIN, HIGH);
  //deay 1 sec
  delay(1000);
  //write message1 on slave 2
  digitalWrite(SS1_PIN, LOW);
  sendMessage(MESSAGE1);
  digitalWrite(SS1_PIN, HIGH);
  delay(1000);
}
