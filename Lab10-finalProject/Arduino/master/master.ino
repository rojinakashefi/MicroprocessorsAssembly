#include <LiquidCrystal.h>
#include <Wire.h>
#define DEVICE_ADDRESS 0b1010000
#define MODE_MEMORY_ADDR 100
#define BUZZER 49

boolean voted = false;

//LCD
const int rs = 27, en = 28;
const int  d4 = 29, d5 = 30, d6 = 31, d7 =32;
//question length Between 0 and 16
String question = "Choose A Number: ";
//AS1&answer2 length Between 0 and 6
String answer1 = "1.One";
String answer2 = "2.Two";
String v[4] = {"", "", "", ""};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  
  Wire.begin();
  
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(BUZZER, OUTPUT);
  readVotes();
  sendQandA();
}

void readVotes(){
  uint8_t data_saved[4];
  eepromRead(MODE_MEMORY_ADDR, data_saved, 4);
  int vote1 = 0;
  int vote2 =0;
  for(int i=0; i<4; i++){
     if(data_saved[i] <= '2'){
          v[i] += data_saved[i];
          vote2++;
      }
     else if(data_saved[i] == '1'){
        vote1++;
        v[i] += data_saved[i];
      }
  }
  rewriteLCD("Total Votes:", 0);
  lcd.print(String(vote1+vote2));
  rewriteLCD(answer1 + ":", 1);
  lcd.print(String(vote1));
  lcd.print(" "+answer2+":");
  lcd.print(String(vote2));
}

void setVote(char temp[]){
  int index =0;
  for(int i=0; i<question.length(); i++){
    temp[index] = question[i];
    index+=1;
  }
  temp[index]='\n';
  index+=1;

  for(int i=0; i<answer1.length(); i++){
    temp[index] = answer1[i];
    index+=1;
  }
  temp[index]='\n';
  index+=1;
  
  for(int i=0; i<answer2.length(); i++){
    temp[index] = answer2[i];
    index+=1;
  }
  temp[index]='\n';
  index+=1;
}

void sendQandA(){
  char temp[question.length() + answer1.length() + answer2.length() + 3];
  setVote(temp);
  char votedMsg[] = {'v','o','t','e','d','\n',' ','\n',' ','\n'};
  delay(50);
  if(v[1] == "")
    Serial1.write(temp);  
  else
    Serial1.write(votedMsg);  
  Serial1.flush();
  delay(10);
  
  if(v[2] == "")
    Serial2.write(temp);  
  else
    Serial2.write(votedMsg);  
  Serial2.flush();
  delay(10);

  if(v[3] == "")
    Serial3.write(temp);  
  else
    Serial3.write(votedMsg);  
  Serial3.flush();
  delay(10);

  if(v[0] == "")
    Serial.write(temp);  
  else
    Serial.write(votedMsg);  
  Serial.flush();
  delay(10);
}

void rewriteLCD(String s, int row){
  lcd.setCursor(0, row);
  lcd.print("                ");
  lcd.setCursor(0, row);
  lcd.print(s);
}
void eepromWrite(uint8_t memory_address, uint8_t data){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(memory_address);
  Wire.write(data);
  Wire.endTransmission();
}

void eepromRead(uint8_t memory_address, uint8_t *data, uint8_t _size){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(memory_address);
  Wire.endTransmission();
  Wire.requestFrom(DEVICE_ADDRESS, _size);
  for(int i=0; i<_size; i++){
    data[i] = Wire.read();
  }
}
void loop() {
  if(Serial.available() && v[0] == ""){
    char ch = (char) Serial.read();
    v[0] += ch;
    rewriteLCD("Device4:", 0);
    rewriteLCD(v[0], 1);

    uint8_t tempData = ch;
    eepromWrite(MODE_MEMORY_ADDR, tempData);
    tone(BUZZER, 400);
    voted = true;
  } 
  if(Serial1.available() && v[1] == ""){
    char ch1 = (char) Serial1.read();
    v[1] += ch1;
    rewriteLCD("Device1:", 0);
    rewriteLCD(v[1], 1);

    uint8_t tempData = ch1;
    eepromWrite(MODE_MEMORY_ADDR + 1, tempData);
    tone(BUZZER, 400);
    voted = true;
  }
  if(Serial2.available() && v[2] == ""){
    char ch2 = (char) Serial2.read();
    v[2] += ch2;
    rewriteLCD("Device2:", 0);
    rewriteLCD(v[2], 1);

    uint8_t tempData = ch2;
    eepromWrite(MODE_MEMORY_ADDR + 2, tempData);
    tone(BUZZER, 400);
    voted = true;
  }
  if(Serial3.available() && v[3] == ""){
    char ch3 = (char) Serial3.read();
    v[3] += ch3;
    rewriteLCD("Device3:", 0);
    rewriteLCD(v[3], 1);

    uint8_t tempData = ch3;
    eepromWrite(MODE_MEMORY_ADDR + 3, tempData);
    tone(BUZZER, 400);
    voted = true;
  }
  if(voted){
    delay(300);
    readVotes();
    voted = false;
  }
}
