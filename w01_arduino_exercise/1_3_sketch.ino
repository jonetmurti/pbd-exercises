  const int kNumOfLed = 8;
  int pinLedArr[kNumOfLed] = {2, 3, 4, 5, 6, 7, 8, 9};
  
  void setup() {
    // put your setup code here, to run once:
    for (int i = 0; i < kNumOfLed; i++) {
      pinMode(pinLedArr[i], OUTPUT);
    }
  }
  
  void loop() {
    // put your main code here, to run repeatedly:
    for (int i = 0; i < kNumOfLed; i++) {
      digitalWrite(pinLedArr[i], HIGH);
      delay(100);
    }
  
    for (int i = 0; i < kNumOfLed; i++) {
      digitalWrite(pinLedArr[i], LOW);
      delay(100);
    }
  }
