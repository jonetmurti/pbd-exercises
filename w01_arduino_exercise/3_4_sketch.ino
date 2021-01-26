long startTime;
long endTime;
bool firstRun = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  endTime = micros();

  if (!firstRun) {
    Serial.print("Time between loop (in microseconds): ");
    Serial.println(endTime - startTime);
  }
  firstRun = false;

  startTime = micros();
}
