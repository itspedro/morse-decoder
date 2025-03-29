#include "Arduino.h"
#include "Morse.h"

Morse::Morse(uint8_t led_pin, uint8_t btn_pin, uint8_t buzzer_pin, unsigned long threshold)
  : _led_pin(led_pin), _btn_pin(btn_pin), _buzzer_pin(buzzer_pin), _threshold(threshold) {
}


void Morse::begin() {
  pinMode(_led_pin, OUTPUT);
  pinMode(_btn_pin, INPUT_PULLUP);
  pinMode(_buzzer_pin, OUTPUT);
}

void Morse::clearSequence() {
  sequenceLength = 0;
}

char Morse::onIdle() {
  if (sequenceLength > 0) {
    char decoded_char = getChar();
    message += decoded_char;
    Serial.print(decoded_char);
    clearSequence();
    return decoded_char;
  }
}

bool Morse::sequencesMatch(const bool* seq1, size_t len1, const bool* seq2, size_t len2) {
  if (len1 != len2) return false;
  for (size_t i = 0; i < len1; i++) {
    if (seq1[i] != seq2[i]) return false;
  }
  return true;
}

char Morse::getChar() {
  for (size_t i = 0; i < morseMapCount; i++) {
    if (sequencesMatch(sequence, sequenceLength, morseMap[i].pattern, morseMap[i].length)) {
      return morseMap[i].letter;
    }
  }
  return '?';
}


void Morse::dot() {
  if (sequenceLength < MAX_SEQUENCE) {
    sequence[sequenceLength++] = false;
  }
}

void Morse::dash() {
  if (sequenceLength < MAX_SEQUENCE) {
    sequence[sequenceLength++] = true;
  }
}


void Morse::update() {
  bool button_pressed = (digitalRead(_btn_pin) == HIGH);
  unsigned long current_time = millis();

  if (button_pressed && !holding) {
    holding = true;
    start_time = current_time;
    digitalWrite(_led_pin, HIGH);
    tone(_buzzer_pin, 262);
  }

  if (!button_pressed && holding) {
    unsigned long press_duration = current_time - start_time;

    if (press_duration < _threshold) {
      dot();
    } else {
      dash();
    }

    holding = false;
    digitalWrite(_led_pin, LOW);
    noTone(_buzzer_pin);
    last_press_time = current_time;
  }


  if (!holding && (current_time - last_press_time > _threshold * 3)) {
    onIdle();
  }
}