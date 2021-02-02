#define NOTE_B4 494

const int kPinTilt = 2;
const int kPinPiezo = 11;

void setup()
{
  pinMode(kPinTilt, INPUT);
  digitalWrite(kPinTilt, HIGH);
  pinMode(kPinPiezo, OUTPUT);
}

bool onTime = true;
int offTimer = millis();
const int interval = 300;

void loop()
{
  if (digitalRead(kPinTilt) == LOW) {
    alarm();
  } else {
    noTone(kPinPiezo);
    onTime = true;
  }
}

void alarm()
{
  if (onTime) {
    tone(kPinPiezo, NOTE_B4, interval);
    onTime = false;
    offTimer = millis();
  } else if (millis() - offTimer >= interval) {
    noTone(kPinPiezo);
  }

  onTime = !onTime && (millis() - offTimer >= interval*2);
}
