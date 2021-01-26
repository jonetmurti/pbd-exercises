const int kGasButton = 2;
const int kBreakButton = 4;
const int kPinLed = 7;

void setup() {
  pinMode(kGasButton, INPUT);
  digitalWrite(kGasButton, HIGH);
  pinMode(kBreakButton, INPUT);
  digitalWrite(kBreakButton, HIGH);
  pinMode(kPinLed, OUTPUT);
}

long lastTime = millis();
int duration = 0;
int currentValue = LOW;

void loop() {
  if (digitalRead(kGasButton) == LOW) {
    duration -= 10;
  } else if (digitalRead(kBreakButton) == LOW) {
    duration += 10;
  }

  duration = constrain(duration, 0, 1000);

  if (millis() - lastTime > duration) {
    if (currentValue == LOW) {
      currentValue = HIGH;
    } else {
      currentValue = LOW;
    }

    lastTime = millis();
    digitalWrite(kPinLed, currentValue);
  }

  delay(20);
}
