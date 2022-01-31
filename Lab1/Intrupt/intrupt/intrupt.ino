int num = strlen("rojina");

#define button1 18
#define button2 19
#define button3 20

volatile boolean on_1 = false;
volatile boolean on_2 = false;
volatile boolean on_3 = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  attachInterrupt(digitalPinToInterrupt(button1), intrupt1Pressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2), intrupt2Pressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(button3), intrupt3Pressed, FALLING);
}

void intrupt1Pressed() {
  on_1 = true;
}

void intrupt2Pressed() {
  on_2 = true;
}
void intrupt3Pressed() {
  on_3= true;

}


void loop() {
  // put your main code here, to run repeatedly:

  if (on_1) {
    for(int i=5;i>=0;i--){
    digitalWrite(i, HIGH);
    delay(250);
    }
     on_1 = false;
  }

  if (on_2) {
    for (int i = 0; i < num; i++) {
      digitalWrite(0, LOW);
      digitalWrite(1, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      delay(150);
      digitalWrite(0, HIGH);
      digitalWrite(1, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      delay(150);
    }

    on_2 = false;
  }
  if(on_3){
     for(int i=5;i>=0;i--){
      digitalWrite(i, LOW);
    }
    on_3=false;
  }
}
