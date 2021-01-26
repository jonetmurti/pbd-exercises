const int kPinButton = 8;
const int kPotInput = A0;
const int kPinLed = 7;

void setup() {
  pinMode(kPinButton, INPUT);
  digitalWrite(kPinButton, HIGH);
  pinMode(kPinLed, OUTPUT);
}

int duration = 1023;
long lastTime = millis();
int currentValue = LOW;

void loop() {
  if (digitalRead(kPinButton) == LOW) {
    duration = analogRead(kPotInput);    
  }

  if (millis() - lastTime > duration) {
    if (currentValue == LOW) {
      currentValue = HIGH;
    } else {
      currentValue = LOW;
    }

    lastTime = millis();
    digitalWrite(kPinLed, currentValue);
  }
}
