#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

const int kPinSpeaker = 3;

void setup() {
  pinMode(kPinSpeaker, OUTPUT);
}

void loop() {
  ourTone(NOTE_C4, 500);
  ourTone(NOTE_D4, 500);
  ourTone(NOTE_E4, 500);
  ourTone(NOTE_F4, 500);
  ourTone(NOTE_G4, 500);
  ourTone(NOTE_A4, 500);
  ourTone(NOTE_B4, 500);
  ourTone(NOTE_C5, 500);

  delay(2000);
}

void ourTone(int freq, int duration) {
  int timeDelay = (int)((((float)1)/(2*freq))*1000000);
  long startTime = millis();
  Serial.println(timeDelay);
  while(millis() - startTime < duration) {
    digitalWrite(kPinSpeaker, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(kPinSpeaker, LOW);
    delayMicroseconds(timeDelay); 
  }
}
