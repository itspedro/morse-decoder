#ifndef Morse_h
#define Morse_h

#include "Arduino.h"
#include "stdint.h"
#define MAX_SEQUENCE 5

struct MorseMapping {
  bool pattern[MAX_SEQUENCE];
  uint8_t length;
  char letter;
};

class Morse
{
  public:
    Morse(uint8_t _led_pin, uint8_t _btn_pin, uint8_t _buzzer_pin, unsigned long _threshold);
    void begin();
    void update();
    String message;
  private:
    char onIdle();
    char getChar();
    void clearSequence();
    bool sequencesMatch(const bool* seq1, size_t len1, const bool* seq2, size_t len2);
    void dot();
    void dash();
    const uint8_t _led_pin;
    const uint8_t _btn_pin;
    const uint8_t _buzzer_pin;
    const unsigned long _threshold;

    bool holding;
    size_t sequenceLength;

    
    unsigned long start_time;
    unsigned long last_press_time;
    bool sequence[MAX_SEQUENCE];
  
    const MorseMapping morseMap[26] = {
      { { false, true }, 2, 'A' },
      { { true, false, false, false }, 4, 'B' },
      { { true, false, true, false }, 4, 'C' },
      { { true, false, false }, 3, 'D' },
      { { false }, 1, 'E' },
      { { false, false, true, false }, 4, 'F' },
      { { true, true, false }, 3, 'G' },
      { { false, false, false, false }, 4, 'H' },
      { { false, false }, 2, 'I' },
      { { false, true, true, true }, 4, 'J' },
      { { true, false, true }, 3, 'K' },
      { { false, true, false, false }, 4, 'L' },
      { { true, true }, 2, 'M' },
      { { true, false }, 2, 'N' },
      { { true, true, true }, 3, 'O' },
      { { false, true, true, false }, 4, 'P' },
      { { true, true, false, true }, 4, 'Q' },
      { { false, true, false }, 3, 'R' },
      { { false, false, false }, 3, 'S' },
      { { true }, 1, 'T' },
      { { false, false, true }, 3, 'U' },
      { { false, false, false, true }, 4, 'V' },
      { { false, true, true }, 3, 'W' },
      { { true, false, false, true }, 4, 'X' },
      { { true, false, true, true }, 4, 'Y' },
      { { true, true, false, false }, 4, 'Z' }
    };

    const size_t morseMapCount = 26;
};

#endif