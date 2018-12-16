/*
   @Author Frank Ricker
   Made for the engeineering prodject to controll the bridge with servos
   New version to work with python aplett
   V3
   Revamp to 12IC comunication on LCD
   V4
   Button Disabled
   New LED patternes
*/

//Lybrarys to Include
#include <Wire.h>  //New LCD, 12IC display
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include<Servo.h>
#include<SoftwareSerial.h>
//Int servos
Servo Side_a;
Servo Side_b;
int state = 0, adjH = 11000; //state = bridge state, oppen = 1, closed = 0, opening = 2, closing = 3, adjH changes hight timeout
String disUpdate = "Steel Strong Inc.";
String a;

//setup loop
void setup() {
  // set up pins
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  pinMode(8, OUTPUT);//led pin
  /*pinMode(6, INPUT); //button pin*/
  Side_a.attach(9);
  Side_b.attach(10);
  Side_a.write(90); Side_b.write(90); //Int servos
  lcd.print("Steel String INC");
  lcd.setCursor(0, 1);
  lcd.print("BridgeControler 3");
  Serial.begin(9600);
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print(" Bridge Closed   ");

}
//main loop
void loop() {
  // put your main code here, to run repeatedly:
  a = Serial.readString();
  if(a.startsWith("u"))
  {
    String disUpdate;
    lcd.clear();
    lcd.setCursor(0,0);
    for(int c = 1; c < a.length(); c++){
      disUpdate = disUpdate + a.charAt(c);
    }
    lcd.print(String(disUpdate));
    lcd.setCursor(0,1);
    if(state == 1)
      lcd.print("Bridge Open");
    else if(state == 0)
      lcd.print("Bridge Closed");
    else if(state == 2)
      lcd.print("Bridge Opening");
    else if(state == 3)
      lcd.print("Bridge Closing");
    Serial.println(disUpdate);
  }
  else if (a.startsWith("o"))
   { if(state == 0)
      Oppen();
   }
  else if (a.startsWith("c"))
    {if(state == 1)
      Close();
    }
  else if (a.startsWith("s"))
   { Status();}
  else if (a.startsWith("e"))
    {changeState();}
  /*
   *  Removed button
    else if (digitalRead(6) == HIGH) {
      if (state == 0)
       { Oppen();}
      else if (state == 1)
        {Close();
    }
   */
   delay(10);
}
void Oppen() {
  if(state == 0){
    state = 2;
    Status();
    lcd.setCursor(0, 1);
    lcd.print("Bridge Opening  ");
    ledOn();
    Side_a.write(180);
    Side_b.write(180);
    ledOff();
    delay(adjH);
    Side_a.write(90);
    Side_b.write(90);
    lcd.setCursor(0, 1);
    lcd.print("  Bridge Open   ");
    state = 1;
    Status();
    }
    
}
void Close(){
    if(state == 1){
    state = 3;
    Status();
    lcd.setCursor(0, 1);
    lcd.print("Bridge Closing  ");
    ledOn();
    Side_a.write(0);
    Side_b.write(0);
    delay((adjH-0));
    Side_a.write(90);
    Side_b.write(90);
    ledOff();
    lcd.setCursor(0, 1);
    lcd.print(" Bridge Closed  ");
    state = 0;
    Status();
    }
}
void Status() {
  Serial.println(state);
}
void changeState(){
  switch (state) {
  case 0:
    state = 1;
    Status();
    lcd.setCursor(0, 1);
    lcd.print("  Bridge Open   ");
    break;
  case 1:
    state = 0;
    Status();
    lcd.setCursor(0, 1);
    lcd.print(" Bridge Closed  ");
    break;
  default:
    // statements
    break;
    }
}
void ledOn(){
 digitalWrite(8, HIGH);
}
void ledOff(){
  digitalWrite(8, LOW);
}
