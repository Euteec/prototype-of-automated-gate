#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include<Servo.h>
int trig1=A0;
int echo1=A1;
int trig2=A2;
int echo2=A3;
int servopin=6;
int pos;
int distance1;
int distance2;
int duration1;
int duration2;
int buzzer=7;
int redpin=8;
int relay=5;
int greenpin=9;
Servo myservo; //creating an object


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
myservo.attach(servopin);
pinMode(trig1,OUTPUT);
pinMode(echo1,INPUT);
pinMode(trig2,OUTPUT);
pinMode(echo2,INPUT);
pinMode(relay,OUTPUT);
pinMode(buzzer,OUTPUT);

welcome_msg();
delay(5000);


}

void loop() {
 digitalWrite(trig1, LOW);
delayMicroseconds(5);
digitalWrite(trig1, HIGH);
delayMicroseconds(10);
digitalWrite(trig1, LOW);
pinMode(echo1, INPUT);
duration1= pulseIn(echo1, HIGH);
distance1 = (duration1/2) / 29.1;
Serial.println(distance1);
delay(50);

digitalWrite(trig2, LOW);
delayMicroseconds(5);
digitalWrite(trig2, HIGH);
delayMicroseconds(10);
digitalWrite(trig2, LOW);
pinMode(echo2, INPUT);
duration2= pulseIn(echo2, HIGH);
distance2 = (duration2/2) / 29.1;


if (distance1<=10){
 open_door();
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
}

if (distance2<=10){
 close_door();
}

if (distance1 &&distance2>10){
  default_display();
}
}
void close_door(){

   for(pos = 90; pos>=0; pos-=5)
        {
        myservo.write(pos); 
        delay(5); 
        }
   digitalWrite(greenpin,HIGH);
  delay(500);
  digitalWrite(greenpin,LOW);
   delay(500);
   digitalWrite(relay,LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("GATE CLOSED");
}

void open_door(){
   
   for(pos = 0; pos>=90; pos+=5)
        {
        myservo.write(pos); 
        delay(5); 
        }
      digitalWrite(redpin,HIGH);
        delay(500);
      digitalWrite(redpin,LOW);
         delay(500);
      digitalWrite(relay,HIGH);  
        
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("GATE OPEN");
        lcd.setCursor(0,1);
       lcd.print("WELCOME");

   
}

void welcome_msg(){
   lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TECH FRIDAY");
  lcd.setCursor(0,1);
  lcd.print("WELCOME ALL");

}

void default_display(){
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("AUTO GATE");
    lcd.setCursor(0,1);
   lcd.print("OPENING..PROJECT");
  
}


