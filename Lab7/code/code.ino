#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>

#define DEVICE_ADDRESS 0b1010000

char keymap[4][4] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'O','0','=', '+'}
};

byte row[4] = {22, 24, 26, 28}; 
byte col[4] = {30, 32, 34, 36};
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const byte led[4] = {40, 41, 42, 43};

Keypad keypad = Keypad( makeKeymap(keymap), row, col, 4, 4 );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte state = 0 ; // 0:idle , 1:active , 2:paused , 3:finished , 4:change mode , 5:change time 
byte step_ = 0 ;
byte mode = 0 ;
byte step_change ;
String input = "";
byte mode_times[3][6] = {{2, 4, 4, 2},{2, 3, 2},{2, 4, 4, 3, 3, 2}};
bool en_time = false ;
float complite_step_time = mode_times[0][0];
float step_time = mode_times[0][0];
float lcd_time ;
long start = millis();
long last_save = millis();


void eeprom_write(uint16_t memory_address, uint8_t* data, int _size);
void eeprom_read(uint16_t memory_address, uint8_t* data, int _size);
void save();
void load();
void update_lcd();
void update_led();
void update_timer();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  
  uint8_t myData[3];
  uint8_t rdData[3];
  
  load();
  update_lcd();
  
}

void loop() {
  
  if (en_time) {
    long mill = millis();
    step_time = (float) complite_step_time - ((mill - start) / 1000.0);
    lcd_time = step_time;
    for (int j = step_+1 ; j < 6; j++){
      lcd_time += mode_times[mode][j];
    }
    if (step_time <= 0) {
      int tmp = 4;
      if(mode == 1)
        tmp = 3;
      if(mode == 2)
        tmp = 6;
        
      step_ = (step_ + 1) % tmp;
      if (step_ == 0) {
        en_time = false;
        state = 3 ; // finished
        for (int i = 0; i < 4; i++)
          digitalWrite(led[i], HIGH);
        update_lcd();
      }
      start = millis();
      complite_step_time = mode_times[mode][step_];
      update_led();
      step_time = 0;
    }
  }
  
  if ((millis() - last_save) > 100) {
    save();
    last_save = millis();
  }
  
  update_lcd();
  update_led();

  char key = keypad.getKey();
  if (key) {
    //    Serial.println(state);

    if (state == 3 && key == 'O') { //finished
      state = 0;
      for (int i = 0; i < 4; i++)
        digitalWrite(led[i], LOW);
      update_lcd();
    } else if (state == 0 && key == 'O') { //idle
      state = 1;
      step_ = 0;
      complite_step_time = mode_times[mode][0];
      en_time = true;
      start = millis();
      update_lcd();
    } else if (state == 0 && (key >= '1' && key <= '6')) { //idle
      state = 5;
      step_change = key -'0';
      input="";
      update_lcd();
    } else if (state == 5 && key == '=') { //change time 
      state = 0;
      mode_times[mode][step_change-1] = input.toInt();
      update_lcd();
    } else if (state == 0 && key == '/') { //idle
      state = 4;
      update_lcd();
    } else if (state == 4 && (key >= '1' && key <= '3')) { //change mode 
      state = 0;
      mode = key -'0'- 1;
      update_lcd();
    } else if (state == 1 && key == 'O') { //active
      state = 2;
      en_time = false;
      complite_step_time = step_time;
      update_lcd();
    } else if (state == 2 && key == 'O') { //paused
      state = 1;
      start = millis();
      en_time = true;
      complite_step_time = step_time;
      update_lcd();
    } else if (state == 5) {
      input += key;
    }
  }
  
  delay(100);
}

void update_led(){
  for (int i = 0; i < 4; i++)
    digitalWrite(led[i], LOW);
    
  if (state == 1) { // active
    en_time = true;
    if(mode != 2 || step_ < 3){
      digitalWrite(led[step_], HIGH);
    } else {
      digitalWrite(led[step_ - 2], HIGH);
    }
  } else if (state == 3) { //finished
    for (int i = 0; i < 4; i++)
      digitalWrite(led[i], HIGH);
  } else if (state == 2) {  //paused
    if(mode != 2 || step_ < 3){
      digitalWrite(led[step_], HIGH);
    } else {
      digitalWrite(led[step_ - 2], HIGH);
    }
  }

}

void update_lcd(){
  lcd.clear();
  lcd.setCursor(0, 0);
  String states[] = {"IDLE", "ACTIVE", "PAUSED", "FINISHED", "CHANGE MODE", "CHANGE TIME"};
  lcd.print(states[state]);
  if(state==0){
    int tmp2 = mode + 1;
    lcd.print(" - mode " +(String) tmp2 + " :");
    lcd.setCursor(0, 1);
    for (int j = 0; j < 6; j++){
      lcd.print((String)mode_times[mode][j]);
      if((mode==0 && j==3)||(mode==1 && j==2)||(mode==2 && j==5))
        break;
      lcd.print("-");
    }
  }
  if(state==2 || state==1){
    int tmp2 = step_ + 1;
    lcd.print(" - step: " +(String) tmp2);
    lcd.setCursor(0, 1);
    lcd.print("timer : " +(String) lcd_time);
  }
  if(state==4){
    int tmp2 = mode + 1;
    lcd.print(" " +(String) tmp2 + " :");
    lcd.setCursor(0, 1);
    lcd.print("new mode :");
  }
  if(state==5){
    lcd.setCursor(0, 1);
    lcd.print("step " +(String) step_change + " :" + input);
  }
 
}

void save() {
 uint8_t data[23] = {0};
  data[0] = (uint8_t) state;
  data[1] = (uint8_t) step_;
  data[2] = (uint8_t) mode;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 6; j++){
      data[((i*6)+j)+3] = (uint8_t) mode_times[i][j];
    }
  }
  data[21] = (uint8_t) step_time;
  int tmp = (int) (step_time*100)%100;
  data[22] = (uint8_t) tmp;

  eeprom_write(5, data, 23);
}

void load() {
  uint8_t data[23] = {0};
  eeprom_read(5, data, 23);
  if (data[0] != 255){
    state = data[0];
    step_ = data[1];
    mode = data[2];
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 6; j++){
        mode_times[i][j] = data[((i*6)+j)+3];
      }
    }
    step_time = data[21];
    float tmp = data[22] ;
    step_time += (float) (tmp/100);

    lcd_time = step_time;
    for (int j = step_+1 ; j < 6; j++){
      lcd_time += mode_times[mode][j];
    }

    update_led();
    
    complite_step_time =  mode_times[mode][step_]; 
    
    update_lcd();
  }
    
}

void eeprom_write(uint16_t memory_address, uint8_t* data, int _size) {
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write((uint8_t)((memory_address & 0xFF00) >> 8));
  Wire.write((uint8_t)((memory_address & 0x00FF) >> 0));
  for (int i = 0; i < _size; i++) {
    Wire.write(data[i]);
    //Serial.print("write: ");
    //Serial.println(data[i]);
  }
  Wire.endTransmission();
  delay(100);
}

void eeprom_read(uint16_t memory_address, uint8_t* data, int _size) {
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write((uint8_t)((memory_address & 0xFF00) >> 8));
  Wire.write((uint8_t)((memory_address & 0x00FF) >> 0));
  Wire.endTransmission();

  Wire.requestFrom(DEVICE_ADDRESS, _size);
  for (int i = 0; i < _size; i++) {
    data[i] = Wire.read();
    //Serial.print("read: ");
    //Serial.println((byte)data[i]);
  }
}
