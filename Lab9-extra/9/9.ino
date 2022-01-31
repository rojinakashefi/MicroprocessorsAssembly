#include "pitches.h"
#include "majorScales.h"
//#include "Ode.h"
//#include "mario.h"
//#include "mario underworld.h"
//#include "pirates.h"
#include <Keypad.h>

#define buttonPin  12
#define speakerPin 8

int button_state = 0;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {50, 51, 52, 53}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {49, 48, 47}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){}

void loop(){

  char key = keypad.getKey();
  if(key){
    if(key == '1'){
      for(int i = 0 ; i < sizeof(melody2)/sizeof(int) ; i++){
        button_state = digitalRead(buttonPin);
        if (button_state == HIGH) 
          noTone(speakerPin);
        else{
           int duration = 300/noteDurations2[i];
           tone(speakerPin,(int) melody2[i]*4, duration);
           delay((int) duration * 1.3);
        }
      }
    }

   

  }}
