#define CH1 8 
void setup() {
  Serial.begin(9600);
   pinMode(CH1, OUTPUT);
   digitalWrite(CH1,LOW);
   delay(2000); 
}

void loop() {
  digitalWrite(CH1, HIGH);
  Serial.println("Relay ON"); 
   delay(1000);
   digitalWrite(CH1, LOW);   
   Serial.println("Relay OFF");
   delay(1000);

}
