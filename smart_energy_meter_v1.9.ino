#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FastIO.h>
#define CH1 8 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

float energy=0;
float power;
const int CsensorIn = A0;
const int VsensorIn = A1;
int mVperAmp = 66; 
double voltage=0;
double Vol = 0;
double VRMS = 0;
double Amps = 0;
float pf=0.9;
double undervoltage=150;
double overvoltage=245;
double overcurrent=5;
double bill=0;
double unit_cost=4;
unsigned long run_time=0;
void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(CsensorIn,INPUT);
  pinMode(VsensorIn,INPUT);
  pinMode(CH1, OUTPUT);
  digitalWrite(CH1,LOW);
  delay(1000);
  lcd.setCursor(2,0);
  lcd.print("SMART ENERGY");
  lcd.setCursor(5,1);
  lcd.print("METER");
  delay(1000);
 }

void loop()

 {
  Serial.begin(9600);
  Vol = getVPP();
  VRMS = (Vol/2.0) *0.707; 
  Amps = (VRMS * 1000)/mVperAmp;
  voltage=getvol();
  Serial.print(Amps);
  Serial.println(" Amps ");
  Serial.print(voltage);
  Serial.println(" volts ");
  power=(Amps*voltage*pf)/1000;
  energy = (power/3600) + energy;
  if((voltage>overvoltage)||(voltage<undervoltage)||(Amps>overcurrent))
  {
   digitalWrite(CH1, HIGH);
   delay(1000);
   digitalWrite(CH1,LOW);
  }
  lcd.clear();
  lcd.print("A= ");
  lcd.print(Amps);
  lcd.setCursor(8,0);
  lcd.print(" P= ");
  lcd.print(power);
  lcd.setCursor(0,1);
  lcd.print("V= ");
  lcd.print(voltage);
  lcd.setCursor(8,1);
  lcd.print(" E= ");
  lcd.print(3*energy);
  lcd.setCursor(0,0);
  delay(1000);
  run_time = millis();
  bill = 3*energy*unit_cost;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Bill = ");
  lcd.print("RS ");
  lcd.print(bill);
  lcd.setCursor(0,1);
  lcd.print(" Time = ");
  lcd.print(run_time/1000);
  lcd.print("sec");
  delay(1000);
 }
float getVPP()
 {
  float result;
  
  int readValue;             
  int maxValue = 0;        
  int minValue = 1024;          
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) 
   {
       readValue = analogRead(CsensorIn);
       
       if (readValue > maxValue) 
       {
        
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
          
           minValue = readValue;
       }
   }
   
   
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
 float getvol()
 {
  int readVal;
  float value;

  readVal= analogRead(VsensorIn);
  value = readVal* (240.0 / 1023.0);
  if (value<15)
  {
   value = 0; 
  }
  return value;
 }

