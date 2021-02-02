/*
 * 
 * COUNTDOWN TIMER 
 * 
 * Program ini merupakan program arduino yang akan menghitung mundur
 * waktu dari sebuah waktu yang telah disimpan sebelumnya. Ketika waktu 
 * telah habis, piezo yang terpasang pada perangkat akan mengeluarkan 
 * suara. Waktu maksimal yang dapat diatur pada program adalah 100 "jam".
 * Timer yang diimplementasi pada program ini bukan timer yang presisi,
 * yaitu 1 detik pada timer tidak sama dengan 1 detik yang sebenernya.
 * 
 * Cara mengoperasikan :
 * - Terdapat 5 tombol untuk mengoperasikan timer
 * - Dari kiri ke kanan, nama tombol-tombol tersebut adalah : set_timer/reset, hour, minute, second, start/stop
 * - Tombol set_timer/reset dapat digunakan untuk mengubah state program dari state awal menjadi set_timer
 * - Tombol set_timer/reset juga dapat digunakan untuk me-reset timer ke waktu awal yang telah disimpan
 * - Tombol hour (mengubah jam), minute (mengubah menit), dan second (mengubah detik) hanya dapat digunakan pada state set_timer
 * - Tombol start/stop dapat digunakan untuk memulai dan menghentikan timer dan hanya dapat digunakan ketika timer berada pada state awal
 * - Jika pengguna tidak ingin menyelesaikan timer dan ingin kembali ke state awal, tekan tombol start/stop (jika timer masih menyala), kemudian tekan tombol set_timer/reset
 * - Ketika timer telah selesai berjalan, piezo akan berbunyi. Untuk mematikan piezo, tekan tombol set_timer/reset
 * 
 */

#include <LiquidCrystal.h>

#define INIT 0
#define SET_TIMER 1
#define START_TIMER 2
#define STOP_TIMER 3
#define TIMER_FINISHED 4
#define NO_STATE 5

#define SET_BUTTON 0
#define HOUR_BUTTON 1
#define MINUTE_BUTTON 2
#define SECOND_BUTTON 3
#define START_BUTTON 4

#define NOTE_B4 494

const int numOfButton = 5;
const int buttonPins[numOfButton] = {2, 12, 11, 10, 9};
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
const int kPinPiezo = 13;
String msg = "Countdown timer";

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < numOfButton; i++) {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
  }
  lcd.begin(16, 2);
  pinMode(kPinPiezo, OUTPUT);
}

int hour = 0;
int minute = 0;
int second = 0;
int savedHour = 0;
int savedMinute = 0;
int savedSecond = 0;
int state = INIT;
int prevState = NO_STATE;
bool pressed = false;
int currentPress = -1;
int buttonRead[numOfButton];
bool currSwitch = true;
bool prevSwitch = false;
long now = millis();

void loop()
{
  for (int i = 0; i < numOfButton; i++) {
    buttonRead[i] = digitalRead(buttonPins[i]);
  }

  if (buttonRead[SET_BUTTON] == LOW && !pressed) {
    pressed = true;
    currentPress = SET_BUTTON;
    currSwitch = !currSwitch;
    if (state == INIT) {
      state = SET_TIMER;
      msg = "Set timer";
    } else if (state == SET_TIMER) {
      state = INIT;
      msg = "Countdown timer";
    } else if (state == STOP_TIMER || state == TIMER_FINISHED) {
        state = INIT;
        hour = savedHour;
        minute = savedMinute;
        second = savedSecond;
        noTone(kPinPiezo);
        msg = "Countdown timer";
    }
  } else if (buttonRead[START_BUTTON] == LOW && !pressed) {
    pressed = true;
    currentPress = START_BUTTON;
    currSwitch = !currSwitch;
    if (state == INIT || state == STOP_TIMER) {
        if (hour != 0 || minute != 0 || second != 0) {
          state = START_TIMER;
          msg = "Running";
        } else {
          msg = "Set timer first";
        }
        now = millis();
    } else if (state == START_TIMER) {
        state = STOP_TIMER;
        msg = "Paused";
    }
  } else if (buttonRead[HOUR_BUTTON] == LOW && !pressed && state == SET_TIMER) {
    pressed = true;
    currentPress = HOUR_BUTTON;
    currSwitch = !currSwitch;
    savedHour = (savedHour + 1)%100;
    hour = savedHour;
  } else if (buttonRead[MINUTE_BUTTON] == LOW && !pressed && state == SET_TIMER) {
    pressed = true;
    currentPress = MINUTE_BUTTON;
    currSwitch = !currSwitch;
    savedMinute = (savedMinute + 1)%60;
    minute = savedMinute;
  } else if (buttonRead[SECOND_BUTTON] == LOW && !pressed && state == SET_TIMER) {
    pressed = true;
    currentPress = SECOND_BUTTON;
    currSwitch = !currSwitch;
    savedSecond = (savedSecond + 1)%60;
    second = savedSecond;
  }

  if (pressed) {
    if (buttonRead[currentPress] == HIGH) {
      pressed = false;
      currentPress = -1;
    }
  }

  if (state == START_TIMER) {
    if (millis() - now >= 500) {
      second -= 1;
      if (second < 0) {
        second = 59;
        minute -= 1;
        if (minute < 0) {
          minute = 59;
          hour -= 1;
        }
      }
      if (hour == 0 && minute == 0 && second == 0) {
        state = TIMER_FINISHED;
        msg = "Reset the timer";
      }
      currSwitch = !currSwitch;
      now = millis();
    }
  }

  if (state == TIMER_FINISHED) {
    tone(kPinPiezo, NOTE_B4);
  }
  
  if (currSwitch != prevSwitch) {
    printTime(hour, minute, second);
  }

  prevState = state;
  prevSwitch = currSwitch;
}

void printTime(int h, int m, int s)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":");
  lcd.print(s);
  lcd.setCursor(0,1);
  lcd.print(msg);
}