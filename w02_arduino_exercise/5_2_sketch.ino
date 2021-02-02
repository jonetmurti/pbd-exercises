#include <LiquidCrystal.h>

const int kPinTemp = A0;

const int kRSPin = 12;
const int kRWPin = 11;
const int kEPin = 10;

const int kD4 = 5;
const int kD5 = 4;
const int kD6 = 3;
const int kD7 = 2;

LiquidCrystal lcd(kRSPin, kEPin, kD4, kD5, kD6, kD7);

void setup()
{
  lcd.begin(16, 2);
}

float maxTemp = -58.0;
float minTemp = 842.0;

void loop()
{
  // Temperature reading
  float voltage = getVoltage(analogRead(kPinTemp));
  float tempC = getTemperature(voltage);
  float tempF = celciusToFahrenheit(tempC);
  
  if (tempF < minTemp) {
    minTemp = tempF;
  }
  if (tempF > maxTemp) {
    maxTemp = tempF;
  }
  
  // Display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(tempF, 2);
  lcd.print(" F");
  lcd.setCursor(0,1);
  lcd.print("max: ");
  lcd.print(maxTemp, 2);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("min: ");
  lcd.print(minTemp, 2);
  delay(1000);
}

float getVoltage(int reading)
{
  return (5.0 * reading) / 1024;
}

float getTemperature(float voltage)
{
  return (voltage - 0.5) * 100;
}

float celciusToFahrenheit(float celcius)
{
  return (celcius * 9.0 / 5.0) + 32.0;
}
