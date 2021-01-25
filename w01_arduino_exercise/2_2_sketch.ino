const int kPinLed = 13;
const int variation = 2;

int delayUnit[variation] = {1000, 500};

int currentVariation = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(kPinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 5; i++) {
    digitalWrite(kPinLed, HIGH);
    delay(delayUnit[currentVariation]);
    digitalWrite(kPinLed, LOW);
    delay(delayUnit[currentVariation]);
  }

  currentVariation = (currentVariation + 1)%variation;
}
