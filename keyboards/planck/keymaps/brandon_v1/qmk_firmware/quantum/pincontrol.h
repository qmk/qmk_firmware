#pragma once
// Some helpers for controlling gpio pins
#include <avr/io.h>

enum {
  PinDirectionInput = 0,
  PinDirectionOutput = 1,
  PinLevelHigh = 1,
  PinLevelLow = 0,
};

// ex: pinMode(B0, PinDirectionOutput);
static inline void pinMode(uint8_t pin, int mode) {
  uint8_t bv = _BV(pin & 0xf);
  if (mode == PinDirectionOutput) {
    _SFR_IO8((pin >> 4) + 1) |= bv;
  } else {
    _SFR_IO8((pin >> 4) + 1) &= ~bv;
    _SFR_IO8((pin >> 4) + 2) &= ~bv;
  }
}

// ex: digitalWrite(B0, PinLevelHigh);
static inline void digitalWrite(uint8_t pin, int mode) {
  uint8_t bv = _BV(pin & 0xf);
  if (mode == PinLevelHigh) {
    _SFR_IO8((pin >> 4) + 2) |= bv;
  } else {
    _SFR_IO8((pin >> 4) + 2) &= ~bv;
  }
}

// Return true if the pin is HIGH
// digitalRead(B0)
static inline bool digitalRead(uint8_t pin) {
  return _SFR_IO8(pin >> 4) & _BV(pin & 0xf);
}
