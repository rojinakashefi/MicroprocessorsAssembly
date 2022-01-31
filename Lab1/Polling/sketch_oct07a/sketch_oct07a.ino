#define button1 10
#define button2 11
#define button3 12

int name = strlen("rojina");

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);


  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
}

void loop() {
  if (digitalRead(button1) == LOW) {
    for(int i=5;i>=0;i--){
      digitalWrite(i, HIGH);
      delay(250);
    }
  }
  if (digitalRead(button2) == LOW) {
    for(int j=0;j<name;j++){
      
        for(int i=0;i<name;i++){
          digitalWrite(i,LOW);
        }
          delay(150);
          
        for(int i=0;i<name;i++){
          digitalWrite(i,HIGH);
        }
          delay(150);
    }
    delay(150);
  }
  if (digitalRead(button3) == LOW) {
    for(int i=0;i<6;i++){
        digitalWrite(i,LOW);
      }
  }
}
