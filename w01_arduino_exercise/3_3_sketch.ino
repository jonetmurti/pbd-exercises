const int kFromButton = 7;
const int kToButton = 8;
const int pot[3] = {A0, A1, A2};
const int rgbPin[3] = {11, 9, 10};
bool firstTime = true;

void setup() {
  pinMode(kFromButton, INPUT);
  digitalWrite(kFromButton, HIGH);
  pinMode(kToButton, INPUT);
  digitalWrite(kToButton, HIGH);
  for (int i = 0; i < 3; i++) {
    pinMode(rgbPin[i], OUTPUT);
  }
  Serial.begin(9600);
}

int fromRGB[3] = {0, 0, 0};
int toRGB[3] = {255, 255, 255};
int inc[3] = {1, 1, 1};
int intpltVal[3] = {0, 0, 0}; // 0-100

void loop() {
  if(digitalRead(kFromButton) == LOW) {
    for (int i = 0; i < 3; i++) {
      fromRGB[i] = map(analogRead(pot[i]), 0, 1023, 0, 255);
      firstTime = true;
    }
  } else if(digitalRead(kToButton) == LOW) {
    for (int i = 0; i < 3; i++) {
      toRGB[i] = map(analogRead(pot[i]), 0, 1023, 0, 255);
      firstTime = true;
    }
  } else {
    if (firstTime) {
      for (int i = 0; i < 3; i++) {
        if (fromRGB[i] < toRGB[i]) {
          inc[i] = 1;
          intpltVal[i] = 0;
        } else {
          inc[i] = -1;
          intpltVal[i] = 100;
        }
      }
      firstTime = false;
    }

    for (int i = 0; i < 3; i++) {
      int val = map(intpltVal[i], 0, 500, fromRGB[i], toRGB[i]);
      analogWrite(rgbPin[i], val);
      intpltVal[i] += inc[i];
      if (intpltVal[i] > 500) {
        intpltVal[i] = 500;
        inc[i] = -1;
      } else if (intpltVal[i] < 0) {
        intpltVal[i] = 0;
        inc[i] = 1;
      }
    }

    delay(10);
  }
}
