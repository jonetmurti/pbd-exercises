const int kNumOfLed = 8;
const int kNumOfPattern = 3;
int pinLedArr[kNumOfLed] = {2, 3, 4, 5, 6, 7, 8, 9};
int patterns[kNumOfPattern][kNumOfLed] = {
  {0, 1, 2, 3, 7, 6, 5, 4},
  {0, 7, 1, 6, 2, 5, 3, 4},
  {0, 4, 1, 5, 2, 6, 3, 7}
};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < kNumOfLed; i++) {
    pinMode(pinLedArr[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int j = 0; j < kNumOfPattern; j++) {
    for (int i = 0; i < kNumOfLed; i++) {
      digitalWrite(pinLedArr[patterns[j][i]], HIGH);
      delay(500);
    }
  
    for (int i = 0; i < kNumOfLed; i++) {
      digitalWrite(pinLedArr[patterns[j][i]], LOW);
      delay(500);
    }
  }
}
