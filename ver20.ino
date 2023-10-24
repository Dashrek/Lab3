#include <Servo.h>
#include  <LiquidCrystal_I2C.h>  // standardowa biblioteka Arduino
//#include  // dolaczenie pobranej biblioteki I2C dla LCD
LiquidCrystal_I2C lcd(0x27, 16,2);  // Ustawienie adresu ukladu na 0x27
Servo servo;
int angle = 0;
int b=1;//flaga dla open i close
int poprzedni=0;//flaga informujaca o poprzednim stanie przycisku
void setup() {
  lcd.init();
  lcd.backlight();
  servo.attach(3);
  servo.write(angle);
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  angle=servo.read();
  lcd.print((angle>=170 ? "Drzwi na osciez  " : (angle<170 && angle >15 ? "Drzwi otwarte"+String(angle) :"Drzwi zamkniete ")));
}


void loop() 
{ 
  angle=servo.read();
  if (poprzedni==0 && digitalRead(2)==0){
    poprzedni=1;
    b*=-1;
    }
  else if(poprzedni==1 && digitalRead(2)==1){
    poprzedni=0;
    }
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print((angle>=85 ? "Open" : "Closed"));
    lcd.setCursor(0,1);
    lcd.print((b==-1 ? "Blocked " : "Unblocked ")+String(poprzedni));

  if(Serial.available()>0){
  switch(Serial.read()){
    case 'o':
    if(b==1){
      if (angle<85){
        while(angle<85) 
  {                                  
    servo.write(angle+1);               
    delay(15);
    angle=servo.read()       ;             
  }}    else{
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("Already Open");
      delay(3000);
      } }break;
  case 'c':
    if(b==1){
    if(angle>10){
        while(angle>10)  
  {                                
    servo.write(angle-1);   
            
    delay(15);
    angle=servo.read();      
  } 
    }
    else{
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("Already Closed");
      delay(3000);
      }
    }break;
    default: lcd.setCursor(0,0);lcd.print("Wrong Cmd");
    delay(3000);
    
  } }
}
