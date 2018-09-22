/* Copyright 2016 Wez Furlong
 *          2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

// Some helpers for controlling gpio pins

#if defined(PROTOCOL_CHIBIOS)
  #include "hal.h"

  #define PIN_VALUE(p)  palReadPad(p & 0xFFFFFFF0, p & 0xF)

  #define DDR_OUTPUT(p) palSetPadMode(p & 0xFFFFFFF0, p & 0xF, PAL_MODE_OUTPUT_PUSHPULL)
  #define DDR_INPUT(p)  palSetPadMode(p & 0xFFFFFFF0, p & 0xF, PAL_MODE_INPUT_PULLDOWN)

  #define PORT_HIGH(p) palSetPad(p & 0xFFFFFFF0, p & 0xF)
  #define PORT_LOW(p) palClearPad(p & 0xFFFFFFF0, p & 0xF)

#endif

#if defined(__AVR__)
  #include <avr/io.h>
  
  #define PIN_ADDRESS(p, offset) _SFR_IO8(ADDRESS_BASE + (p >> PORT_SHIFTER) + offset)

  #define PIN(p) PIN_ADDRESS(p, 0)
  #define PIN_VALUE(p) (PIN(p) & _BV(p & 0xF))

  #define DDR(p) PIN_ADDRESS(p, 1)
  #define DDR_OUTPUT(p) (DDR(p) |= _BV(p & 0xF))
  #define DDR_INPUT(p) (DDR(p) &= ~_BV(p & 0xF))

  #define PORT(p) PIN_ADDRESS(p, 2)
  #define PORT_HIGH(p) (PORT(p) |= _BV(p & 0xF))
  #define PORT_LOW(p) (PORT(p) &= ~_BV(p & 0xF))

  // Arduino shortcuts

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

#endif