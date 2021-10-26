#include <Servo.h>
#include  <LiquidCrystal_I2C.h>  // standardowa biblioteka Arduino
//#include  // dolaczenie pobranej biblioteki I2C dla LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27
Servo servo;
int angle = 0;

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  servo.attach(8);
  servo.write(angle);
  Serial.begin(9600);
  angle=servo.read();
  lcd.print((angle>=170 ? "Drzwi na osciez  " : (angle<170 && angle >15 ? "Drzwi otwarte"+String(angle) :"Drzwi zamkniete ")));
}

int a=1;
void loop() 
{ 
  angle=servo.read();
  if (a==1){
      lcd.setCursor(0,0);lcd.print(((angle>=170 ? "Drzwi na osciez *   " : (angle<170 && angle >15 ? "Drzwi otwarte"+String(angle) :"Drzwi zamkniete*   "))));
      a=0;
  }
  if(Serial.available()>0){
  switch(Serial.read()){
    case 'o':
      if (angle<170){
        while(angle<170) 
  {                                  
    servo.write(angle+1);               
    delay(15);
    angle=servo.read()       ;             
  }} a=1;break;
  case 'z':

    if(angle>10){
        while(angle>10)  
  {                                
    servo.write(angle-1);   
            
    delay(15);
    angle=servo.read();      
  } 
    }a=1;break;
    default: lcd.setCursor(0,0);lcd.print("bledne polecenie");
    
  } }
}
