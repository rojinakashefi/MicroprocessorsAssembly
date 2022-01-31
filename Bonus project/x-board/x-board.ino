#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;
byte rowPins[ROWS] = {27, 29, 31, 33};
byte colPins[COLS] = {22, 23, 25};
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char board[9];
boolean x_turn = true ;

void setup() {
  set_lcd();
  set_board();
  print_board();
  
}

void loop(){
  if(Serial.available()){
        char input_c = Serial.read();
        x_turn = is_gamecontinued(input_c);
        if (!x_turn){
          print_winner(input_c);
        }
        else{
          set_o_character(input_c - '0');
        }
        
  }                 
   if(x_turn){
        char x_place = keypad.getKey();  
            if (x_place){
                  if(x_place >= 1 && 9 <=x_place){
                     set_x_character(x_place - '0');
                     x_turn=false;
                     Serial.write(x_place); 
                     print_winner(check_win());
                          
                   }
             }      
    }
}

  
void set_lcd(){
  Serial.begin(9600);
  lcd.begin(16, 4);
  lcd.clear();
}

void set_board(){
  for (int i =0 ; i <9 ; i ++ ){
    board[i]='_';
    }
}

void print_board() {
    lcd.clear();
    lcd.setCursor(0 , 0);
    lcd.print("Player X: ");
    int cursor_j = 1;
    int cursor_i = 6;
    for(int i=0; i<9 ; i++){
        if ( (i!=0) && ((i%3) == 0 )) {
                cursor_i = 6 ;
                cursor_j = cursor_j + 1 ;
        }
        lcd.setCursor(cursor_i,cursor_j);
        lcd.write(board[i]);
        cursor_i =  cursor_i + 1 ;
    }
}

boolean is_gamecontinued(char input){
    if (input == 'e'){
      return false;
    }
    if (input == 'x'){
      return false;
    }
    if (input == 'o'){
      return false;
    }
     return true;
    
}


void print_winner(char input){
  lcd.setCursor(9 , 0);
  if(input == 'e'){
    lcd.print("Equal");
    Serial.write('e');
  }
  else if(input == 'x'){
    lcd.print("X won");
    Serial.write('x');
  }
  else if (input == 'o'){
    lcd.print("O won"); 
    Serial.write('o');  
  }    
}


void set_x_character(int i){
    if(board[i - 1]=='_'){
        board[i - 1]= 'x';
        print_board();
    }
}


void set_o_character(int i){
    if(board[i - 1]=='_'){
        board[i - 1]= 'o';
        print_board();
    }
}


char  check_win(){
  char winner_is ='?' ;
  boolean win =false;
   if( board[0]!= '_' &&  board[1]!='_' && board[2]!='_'){
    if(board[0]== board[1] && board[1]== board[2]){
        winner_is = board[0];
        win = true;
      
      }
   }
   if(board[3]!='_' && board[4]!='_' &&  board[5]!='_'){
    if(board[3]== board[4] && board[4]== board[5]){
        winner_is= board[3];
        win = true;
      }
   }
   if(board[6]!='_' && board[7]!='_' && board[8]!='_'){
     if(board[6]==board[7] && board[7]== board[8]){
          winner_is = board[6];
          win =true;
      
      }
   }
   if(board[0]!='_' && board[3]!='_' && board[6]!='_'){
      if(board[0]== board[3] && board[3]==board[6] ){
        winner_is = board[0];
        win =true;
      }
   }
 
  if(board[1]!='_' &&  board[4]!='_' &&  board[7]!='_'){
    if(board[1]==board[4] && board[4]==board[7] ){
      winner_is=board[1];
      win=true;
    }
  }
  
   if(board[5]!='_' && board[8]!='_' && board[2]!='_'){
    if(board[2]== board[5] && board[5]==board[8] ){
       winner_is = board[2];
        win = true;
    
    }
   }
   
   if(board[0]!='_' && board[4]!='_' && board[8]!='_'){
    if(board[0]== board[4] && board[4]== board[8]){
      winner_is=board[0];
       win=true;
      }
   }
   
   if(board[4]!='_' && board[6]!='_' && board[2]!='_'){
    if(board[2]==board[4] && board[4]==board[6] ){
       winner_is=board[2];
       win =true;
    
    }
   }
   if(board[0]!='_'  && board[1]!='_'  && board[2]!='_' && board[3]!='_' && board[4]!='_' && board[5]!='_' && board[6]!='_' && board[7]!='_' && board[8]!='_'){
         if(!win){
              winner_is='e';      
         }
    }
  return winner_is;
}


  
