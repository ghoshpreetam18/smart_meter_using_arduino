#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
double Amps=0;
double voltage=0; 
double power=0;
double energy=0;
//lcd.backlight();// To Power OFF the back light

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("SMART ENERGY");
  lcd.setCursor(5,1);
  lcd.print("METER");
  delay(1000);
}

void loop() {
lcd.setCursor(2,0);
  lcd.print("SMART ENERGY");
  lcd.setCursor(5,1);
  lcd.print("METER");
}

