#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

# define NUM_NOTES 6

const int kPinSpeaker = 3;

const int notes[NUM_NOTES] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4
};

const int beats[NUM_NOTES] = {
  1, 1, 2, 2, 2, 4
};

const int beatValue = 300;

void setup() {
  pinMode(kPinSpeaker, OUTPUT);
}

void loop() {
  for (int i = 0; i < NUM_NOTES; i++) {
    if (notes[i] == 0) {
      delay(beats[i] * beatValue);
    }else {
      ourTone(notes[i], beats[i] * beatValue);
    }
    
    noTone(kPinSpeaker);
    delay(beatValue/2);
  }
}

void ourTone(int freq, int duration) {
  tone(kPinSpeaker, freq, duration);
  delay(duration);
}
