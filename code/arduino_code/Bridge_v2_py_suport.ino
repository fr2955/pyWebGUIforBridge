/*
   @Author Frank Ricker
   Made for the engeineering prodject to controll the bridge with servos
   New version to work with python aplett
*/

//Lybrarys to Include
#include <LiquidCrystal.h>
#include<Servo.h>
#include<SoftwareSerial.h>
//Int servos
Servo Side_a;
Servo Side_b;
int state = 0, adjH = 5000; //state = bridge state, oppen = 1, closed = 0, opening = 2, closing = 3, adjH changes hight timeout
String disUpdate = "Steel Strong Inc.";
String a;
const int rs = 12,
          en = 11,
          d4 = 5,
          d5 = 4,
          d6 = 3,
          d7 = 2;
//Sets up LCD pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //sets up lcd

//setup loop
void setup() {
  // set up pins
  pinMode(8, OUTPUT);//solinoid pin
  pinMode(6, INPUT); //button pin
  Side_a.attach(9);
  Side_b.attach(10);
  Side_a.write(90); Side_b.write(90); //Int servos
  lcd.begin(16, 2);
  lcd.print(String(disUpdate));
  lcd.setCursor(0, 1);
  lcd.write("BridgeControler 2");
  Serial.begin(9600);
  delay(1500);
  lcd.setCursor(0,1);
  lcd.write(" Bridge Closed   ");

}
//main loop
void loop() {
  // put your main code here, to run repeatedly:
  a = Serial.readString();
  if(a.startsWith("u"))
  {
    lcd.setCursor(1,0);
    disUpdate = "";
    for(int c = 1; c < 20; c++){
      disUpdate = disUpdate + a.charAt(c);
    }
    lcd.print(String(disUpdate));
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
  else if (digitalRead(6) == HIGH) {
    if (state == 0)
     { Oppen();}
    else if (state == 1)
      {Close();
    }
  }
   delay(10);
}
void Oppen() {
  if(state == 0){
    state = 2;
    Status();
    lcd.setCursor(0, 1);
    lcd.write("Bridge Opening  ");
    digitalWrite(8, HIGH);
    Side_a.write(180);
    Side_b.write(180);
    delay(1500);
    digitalWrite(8, LOW);//clsoe solinoid
    delay(adjH);
    Side_a.write(90);
    Side_b.write(90);
    lcd.setCursor(0, 1);
    lcd.write("  Bridge Open   ");
    state = 1;
    Status();
    }

}
void Close(){
    if(state == 1){
    state = 3;
    Status();
    lcd.setCursor(0, 1);
    lcd.write("Bridge Closing  ");
    digitalWrite(8, HIGH);
    Side_a.write(0);
    Side_b.write(0);
    delay(1500);
    digitalWrite(8, LOW);//clsoe solinoid
    delay(adjH);
    Side_a.write(90);
    Side_b.write(90);
    lcd.setCursor(0, 1);
    lcd.write(" Bridge Closed  ");
    state = 0;
    Status();
    }
}
void Status() {
Serial.println(state);
}