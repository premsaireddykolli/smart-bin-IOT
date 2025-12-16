#include <Servo.h>
#include <LiquidCrystal_I2C.h>
 
const int trigPin = 9;
const int echoPin = 10;
 
const int rainSensorPin = A0;    
const int irSensorPin = 8;       
const int buzzerPin = 7;         
 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
 

Servo servo1;
Servo servo2;
 
void setup() {
   servo1.attach(3);  
  servo2.attach(6);   
  
  Serial.begin(9600);
 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  
  pinMode(irSensorPin, INPUT);
 
  pinMode(buzzerPin, OUTPUT);
 
 
  lcd.init(); 
  lcd.backlight();  
  lcd.print("Initializing...");
 
  servo1.write(0);     
  servo2.write(120);    
  
  digitalWrite(buzzerPin, LOW);   
 
  delay(2000); 
  lcd.clear();
}
 
void loop() {
  long duration, distance;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
 
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
 
  if (distance <= 10) {
    servo1.write(180);            
    digitalWrite(buzzerPin, HIGH);   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Thank You");         
  } else {
    servo1.write(0);                 
    digitalWrite(buzzerPin, LOW);    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Make India Clean");  
  }
 

  int rainValue = analogRead(rainSensorPin);
  int irValue = digitalRead(irSensorPin);  
  
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);
  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);
 
  
  if (irValue == 1) {           
    servo2.write(120);            
  } else if (rainValue > 800) {   
    servo2.write(180);              
  } else if (rainValue < 600) {   
    servo2.write(0);           
  } else {
    servo2.write(120);            
  }
 
  delay(500);  
}
