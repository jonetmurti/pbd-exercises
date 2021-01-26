#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

const int kPinSpeaker = 3;
const int kPinButton1 = 7;
const int kPinButton2 = 8;

void setup() {
  pinMode(kPinSpeaker, OUTPUT);
  pinMode(kPinButton1, INPUT);
  digitalWrite(kPinButton1, HIGH);
  pinMode(kPinButton2, INPUT);
  digitalWrite(kPinButton2, HIGH);
}

void loop() {
  if (digitalRead(kPinButton1) == LOW) {
    tone(kPinSpeaker, NOTE_C4);
  } else if (digitalRead(kPinButton2) == LOW) {
    tone(kPinSpeaker, NOTE_C5);
  } else {
    noTone(kPinSpeaker);
  }
}
