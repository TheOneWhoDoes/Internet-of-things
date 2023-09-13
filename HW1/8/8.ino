int ldr = A0;
int led = D1;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(ldr, INPUT);
  analogWriteRange(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrValue = analogRead(ldr);
  float light = ldrValue * (100.0 / 1023);
  Serial.println(ldr,light);
  delay(100);
}
