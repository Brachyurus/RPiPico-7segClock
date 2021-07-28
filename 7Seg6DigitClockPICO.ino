#include <RTClib.h>
RTC_DS3231 rtc;

byte digit[6] = {21, 20, 19, 18, 17, 16};
byte numberOfDigits = sizeof(digit);

byte segmentPin[7] = {6, 7, 8, 9, 10, 11, 12};

bool num[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1}
};

uint32_t prevRefresh = 0;
uint32_t prevUpdate = 0;
byte digitNumber;
uint8_t second = 0;

void setup() {

  for (int i = 0; i < numberOfDigits; i++) {
    pinMode(digit[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPin[i], OUTPUT);
  }

  rtc.begin();
//  rtc.adjust(DateTime(2014, 1, 21, 20, 27, 0));
}

void loop() {
  DateTime now = rtc.now();
  uint32_t currentMillis = millis();

  if (currentMillis - prevRefresh >= 2) {
    prevRefresh = currentMillis;
    displayNumber();
  }
}

void displayNumber() {
  for (int i = 0; i < numberOfDigits; i++) {
    digitalWrite(digit[i], HIGH);
  }
  digitNumber++;
  if (digitNumber >= numberOfDigits) {
    digitNumber = 0;
  }
  DateTime now = rtc.now();

  switch (digitNumber) {
    case 0:
      for (int j = 0; j < 7; j++) {
        digitalWrite(segmentPin[j], num[now.hour() / 10][j]);
      }
      break;
    case 1:
      for (int j = 0; j < 7; j++) {
        digitalWrite(segmentPin[j], num[now.hour() % 10][j]);
      }
      break;
    case 2:
      for (int j = 0; j < 7; j++) {
        digitalWrite(segmentPin[j], num[now.minute() / 10][j]);
      }
      break;
    case 3:
      for (int j = 0; j < 7; j++) {
        digitalWrite(segmentPin[j], num[now.minute() % 10][j]);
      }
      break;
    case 4:
      for (int j = 0; j < 7; j++) {
        digitalWrite(segmentPin[j], num[now.second() / 10][j]);
      }
      break;
    case 5:
      for (int j = 0; j < 7; j++) {
        digitalWrite(segmentPin[j], num[now.second() % 10][j]);
      }
      break;
  }
  digitalWrite(digit[digitNumber], LOW);
}
