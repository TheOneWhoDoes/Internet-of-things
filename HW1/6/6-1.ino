int ldr = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ldr, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrValue = analogRead(ldr);
  float light = ldrValue * (100.0 / 1023);
  Serial.println(light);
  delay(1000);
}
