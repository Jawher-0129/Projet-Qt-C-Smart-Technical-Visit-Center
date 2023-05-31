

/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

char data; 
int nb=5;
Servo myservo; 
int pos = 0;
LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
    lcd.init();
  lcd.backlight();
  lcd.clear();
  //lcd.begin(16,2);
  
  myservo.attach(10);   
  Serial.begin(9600);  
 lcd.setCursor(0,0);
 lcd.print("Nb_PLACE DISPO");
 lcd.setCursor(1,1);
 lcd.print(nb);
}
  
void loop(){
  char customKey = customKeypad.getKey();

  myservo.write(0);
   
  if (Serial.available())
  {     
     data=Serial.read();  

     if(nb>0)
     {
       if(data=='1') 
    {
     // Serial.write('1');
      myservo.write(90); 
      delay(5000);
      myservo.write(0);
      nb--;
          lcd.setCursor(1,1);
              lcd.print(nb);
     }  
      if(data=='0')
     {
         //Serial.write('0'); 
         myservo.write(0);
     }   
  }
  if(nb==0)
  {
    lcd.setCursor(0,0);
 lcd.print("PARKING COMPLET");
  }
  } 
  if (customKey){
    Serial.write(customKey);
  }
}
