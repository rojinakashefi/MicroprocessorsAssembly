
const byte ledPins[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};

byte incomingByte = 0;

void setup() {
  Serial.begin(9600);

  for (byte i = 0; i < 9; i++)
    pinMode(ledPins[i], OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.parseInt();
    if (incomingByte > 0) {
      Serial.println(incomingByte);
      if (incomingByte > 9)
        Serial.println("Invalid number");
      else {
        for (byte i = 0; i < 9; i++)
          digitalWrite(ledPins[i], LOW);
        for (byte i = 0; i < incomingByte ; i++)
          digitalWrite(ledPins[i], HIGH);
      }
    }
  }
}
