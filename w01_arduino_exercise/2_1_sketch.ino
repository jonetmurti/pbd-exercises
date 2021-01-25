const int kPinLed = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(kPinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 10; i++) {
    digitalWrite(kPinLed, HIGH);
    delay(200);
    digitalWrite(kPinLed, LOW);
    delay(200);
  }
  delay(1000);
}
