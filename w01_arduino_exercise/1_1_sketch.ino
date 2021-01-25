const int kPinLed = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(kPinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(kPinLed, HIGH);
  delay(500);
  digitalWrite(kPinLed, LOW);
  delay(1000);
}
