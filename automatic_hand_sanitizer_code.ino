#include <LiquidCrystal.h>

#include<Servo.h>
Servo myservo;

int ledpin=2;
int trigger= 7;
int echo= 6;
int buzzer= 12;
int servoPin=13;
int count=0;

LiquidCrystal lcd (3,4,11,10,9,8);

float time=0, distance=0;

void setup ()
{
    Serial.begin(9600);
    lcd.begin(16,2);
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(ledpin, OUTPUT);
    lcd.print("   Wear Mask ");
    lcd.setCursor(0,1);
    lcd.print(" Keep Socialdistance ");
    delay(2000);
    myservo.attach(servoPin);
    myservo.write(0);

}
void loop() 
{
    lcd.clear();
    

    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);

    
    time=pulseIn(echo,HIGH);
    float original_time= time/2;
    float time_in_seconds= original_time/1000000;
    float distance_in_meter= 343.0*time_in_seconds;
    float distance_in_cm= distance_in_meter*100;
    Serial.print("d = ");
    Serial.print(distance_in_cm);
    Serial.println(" cm");

    if(distance_in_cm<200) 
    {
        digitalWrite(buzzer, HIGH);
        lcd.clear();
        lcd.print("     Please   ");
        lcd.setCursor(0,1);
        lcd.print("  use sanitizer");
        delay(2000);
      
        myservo.write(90);
  	    delay(200);
        myservo.write(0);
  	    delay(200);
    
        count=count+1;               
    }
  
    else if(distance_in_cm>200)
    {
        digitalWrite(buzzer, LOW);
        lcd.clear();
        lcd.print("   WELCOME   ");
        delay(500);
        myservo.write(0); 
    }
   Serial.print("c : ");
   Serial.println(count);
    
   if(count>=5) {
      digitalWrite(ledpin, HIGH);
      count=0;
   }
    else
      digitalWrite(ledpin, LOW);
  
    delay(1000);  

}
