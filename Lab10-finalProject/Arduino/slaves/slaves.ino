#include <LiquidCrystal.h>
#include <Keypad.h>
//Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'O','0','=','+'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//LCD
const int rs = 24, en = 26, d4 = 32, d5 = 33, d6 = 34, d7 =35;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//LED
const uint8_t LED_PINS[] = {41, 42};
//Vars
String Question = "";
String answers1 = "";
String answers2 = "";
String temp = "";
bool isQuestionAndAnswerSet = false;
bool hasSubmitted = false;
void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();

  for(int i=0; i<2; i++){
    pinMode(LED_PINS[i], OUTPUT);  
  }
}
void updateLCD(bool hasAnswer = true){
  lcd.setCursor(0, 0);
  lcd.print(Question);
  if(hasAnswer){
    lcd.setCursor(0, 1);
    String s = answers1 + answers2;
    lcd.print(s);
  }
}
void setQuestionAndAnswer(){
  if(Serial.available()){
    char ch = (char) Serial.read();
    Serial3.print(ch);
    if(ch == '\n'){
      if(Question == "")
        Question = temp;
      else if(answers1 == "")
        answers1 = temp;
      else{
        answers2 = temp;
        isQuestionAndAnswerSet = true;    
        if(Question == "voted"){
          hasSubmitted = true;
          Serial.end();
          updateLCD(false);
          return;
        }
        updateLCD();
        Serial3.println();
      }
      temp = "";
    }else
      temp += ch;
  }
}


bool isKeyNumber(char key){
  int keyAsciiCode = (int)key;
  return keyAsciiCode >= (int)'1' && keyAsciiCode <= (int)'9';
}

void readKeypad(){
  char key = keypad.getKey();
  if(key){
    Serial3.println(key);
    static int keyNum;
    if(isKeyNumber(key)){
      keyNum = (int) key;
      keyNum -= (int)'0';
    }else if(key == '*'){
      if(keyNum>=1 && keyNum <= 2){
        //turn on LED
        digitalWrite(LED_PINS[keyNum-1], HIGH);
        delay(500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("voted");
        saveVote(keyNum);
        Serial3.print("Vote submitted: ");
        Serial3.println(keyNum);
        hasSubmitted = true;
      }else{
        Serial3.println("Choose between 1 and 2");  
      }
    }
  }
}
void saveVote(int vote){ 
  char v[] = {(int)'0' + vote};  
  delay(50);
  Serial.write(v);
  Serial.flush();
  delay(10);
  Serial.end();
  Serial3.println("Sent!");
}
void loop() {
  if(!isQuestionAndAnswerSet){
    setQuestionAndAnswer();  
  }
  else if(!hasSubmitted){
    readKeypad(); 
  }
}
