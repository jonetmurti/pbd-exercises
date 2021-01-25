const int kNumOfLed = 8;

int pinLedArr[kNumOfLed] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < kNumOfLed; i++) {
    pinMode(pinLedArr[i], OUTPUT);
  }
}

void loop() {
  // pattern 1 
  for (int i = 0; i < kNumOfLed; i++) {
    digitalWrite(pinLedArr[i], HIGH);
    if (i > 0) digitalWrite(pinLedArr[i - 1], LOW);
    delay(100);
  }

  digitalWrite(pinLedArr[kNumOfLed - 1], LOW);
  delay(1000);

  // pattern 2
  for (int i = kNumOfLed - 1; i >= 0; i--) {
    digitalWrite(pinLedArr[i], HIGH);
    if (i < kNumOfLed - 1) digitalWrite(pinLedArr[i + 1], LOW);
    delay(100);
  }

  digitalWrite(pinLedArr[0], LOW);
  delay(1000);

  // pattern 3
  for (int i = kNumOfLed/2 - 1; i >= 0; i--) {
    digitalWrite(pinLedArr[i], HIGH);
    digitalWrite(pinLedArr[kNumOfLed - i - 1], HIGH);
    delay(100);
  }

  for (int i = kNumOfLed/2 - 1; i >= 0; i--) {
    digitalWrite(pinLedArr[i], LOW);
    digitalWrite(pinLedArr[kNumOfLed - i - 1], LOW);
    delay(100);
  }

  delay(1000);

  // pattern 4
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < kNumOfLed; j++) {
       digitalWrite(pinLedArr[j], HIGH);
    }
    delay(200);
    for (int j = 0; j < kNumOfLed; j++) {
       digitalWrite(pinLedArr[j], LOW);
    }
    delay(200);
  }

  delay(1000);
}
