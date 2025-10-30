#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <DHT.h>
#define DHTPIN 4 
#define DHTTYPE DHT11 
#define A_1A 9 
#define A_1B 10 
#define B_1A 5 
#define B_1B 6  
#define SOIL_HUMI A0

LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht(DHTPIN, DHTTYPE); 

int cds_pin = A1; 
int cds_ledpin=3;
int soil, psoil; 
int val, ledval, pledval; 

void setup() { 
 lcd.init(); 
 lcd.clear();
 lcd.backlight(); 
 lcd.setCursor(0,0);  
 lcd.print("SmartFarm"); 
 lcd.setCursor (0,1); 
 lcd.print("   - smu arduino-  "); 
 Serial.begin(9600); 
 Serial.println("스마트팜 START!"); 
 delay(4000); 
 dht.begin(); 
 
 pinMode(A_1A, OUTPUT);
 pinMode(A_1B, OUTPUT);  
 digitalWrite(A_1A, LOW); 
 digitalWrite(A_1B, LOW);
 pinMode(B_1A, OUTPUT);
 pinMode(B_1B, OUTPUT);  
 digitalWrite(B_1A, LOW);
 digitalWrite(B_1B, LOW);
 pinMode(cds_ledpin, OUTPUT);
}
void loop() {  
 float h = dht.readHumidity(); 
 float t = dht.readTemperature(); 
 if (isnan(h) || isnan(t)){ 
  Serial.println("DHT센서 값 읽기 실패!"); 
  return; 
  }
 soil = analogRead(SOIL_HUMI); 
 psoil = map(soil, 1023, 0, 0, 100); 
 val = analogRead(cds_pin); 
 ledval = map(val,0, 1023, 250, 0); 
 pledval = ledval*0.4; 
 lcd.init(); 
 lcd.clear(); 
 lcd.backlight();
 lcd.display();
 lcd.setCursor(0,0);
 lcd.print("M: ");
 lcd.print(psoil);
 lcd.print("%");
 lcd.setCursor(8,0);
 lcd.print("D: ");
 lcd.print(pledval);  
 lcd.print("ph");
 lcd.setCursor(0,1);
 lcd.print("T: ");
 lcd.print(t,0);
 lcd.print("C");
 lcd.setCursor(8,1);
 lcd.print("H: ");
 lcd.print(h,0);  
 lcd.print("%");
 Serial.print("수분량: ");
 Serial.print(psoil);
 Serial.print("  조도: ");
 Serial.print(pledval);
 Serial.print("  온도: ");
  Serial.print(t);
  Serial.print("  습도: ");
  Serial.print(h);
  Serial.println();
  delay(1000); 

if(psoil < 40) { // 토양수분값
 analogWrite(A_1A, 220);
 digitalWrite(A_1B, LOW);
 delay(5000);
 digitalWrite(A_1A, LOW); 
 digitalWrite(A_1B, LOW);
 digitalWrite(B_1A, LOW); 
 digitalWrite(B_1B, LOW);
 }
 else{ 
 digitalWrite(A_1A, LOW);
 digitalWrite(A_1B, LOW);
} 
 delay(1000);
 
if(t >= 30 || h >= 65) { //온도 습도 값
delay(5000);
 analogWrite(B_1A, 220); 
 digitalWrite(B_1B, LOW);
 delay(5000);
 digitalWrite(B_1A, LOW);  
 digitalWrite(B_1B, LOW);
 digitalWrite(A_1A, LOW);
 digitalWrite(A_1B, LOW);
} 
else{ 
 digitalWrite(B_1A, LOW);
 digitalWrite(B_1B, LOW);
}
 delay(1000);
 
 if (pledval >50) { // 조도센서값
  analogWrite(cds_ledpin, ledval); 
 } 
  else{  
  analogWrite(cds_ledpin, LOW);    
 }
}
