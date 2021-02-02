const int kPinPhotoCell = A0;
const int kPinLed = 11;

void setup()
{
  pinMode(11, OUTPUT);
}

void loop()
{
  int photoValue = analogRead(kPinPhotoCell);
  int ledValue = map(photoValue, 0, 1023, 0, 255);
  analogWrite(kPinLed, ledValue);
}
