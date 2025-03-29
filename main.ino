#include <LiquidCrystal.h>
#include "Morse.h"
#include "stdint.h"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const unsigned long THRESHOLD = 200;
const uint8_t BUZZER = 6, LED = 7, BTN = 8;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int potPin = A0;

String message = "";
int messageLength = 0;
int scrollPosition = 0;

int potValue = 0;
int scrollDelay = 0;
int percentage = 0;
unsigned long previousMillis = 0;

Morse morseDecoder(LED, BTN, BUZZER, THRESHOLD);

void setup() {
  lcd.begin(16, 2);
  morseDecoder.begin();
  Serial.begin(9600);
  lcd.setCursor(0, 1);
  lcd.print("                "); 
}

void loop() {
  morseDecoder.update();

  message = morseDecoder.message;
  messageLength = message.length();

  potValue = analogRead(potPin);

  scrollDelay = map(potValue, 0, 1023, 50, 500);
  percentage = map(potValue, 0, 1023, 100, 0);

  lcd.setCursor(0, 0);
  lcd.print(scrollDelay);
  lcd.setCursor(3, 0);
  lcd.print("ms");

  lcd.setCursor(12, 0);
  if (percentage < 10) {
    lcd.print(" ");
  }
  if (percentage < 100) {
    lcd.print(" ");
  }
  lcd.print(percentage);
  lcd.print("%");
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= scrollDelay) {
    previousMillis = currentMillis;

    lcd.setCursor(0, 1);
    lcd.print("                ");

    if (messageLength > 16) {
      lcd.setCursor(0, 1);
      for (int i = 0; i < 16; i++) {
        int charPosition = (scrollPosition + i) % messageLength;
        lcd.print(message[charPosition]);
      }
      scrollPosition = (scrollPosition + 1) % messageLength;
    } else {
      lcd.setCursor(0, 1);
      lcd.print(message);
    }
  }
}√