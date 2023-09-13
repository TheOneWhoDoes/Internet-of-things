int buzzer = D8;
int ledRed = D6;
int ledGreen = D7;
int ldr = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrValue = analogRead(ldr);
  float light = ldrValue * (100.0 / 1023);
  Serial.println(light);
  if(light > 35.0){
    tone(buzzer, 1000);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  }else{
    noTone(buzzer);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
  }
  delay(100);
}
