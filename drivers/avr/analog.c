/* Copyright 2015 Jack Humbert
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

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "analog.h"

static uint8_t aref = ADC_REF_POWER;

void analogReference(uint8_t mode) {
    aref = mode & (_BV(REFS1) | _BV(REFS0));
}

// Arduino compatible pin input
int16_t analogRead(uint8_t pin) {
#if defined(__AVR_ATmega32U4__)
    static const uint8_t PROGMEM pin_to_mux[] = {0x00, 0x01, 0x04, 0x05, 0x06, 0x07, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20};
    if (pin >= 12) return 0;
    return adc_read(pgm_read_byte(pin_to_mux + pin));
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
    if (pin >= 8) return 0;
    return adc_read(pin);
#else
    return 0;
#endif
}

int16_t analogReadPin(pin_t pin) {
    return adc_read(pinToMux(pin));
}

uint8_t pinToMux(pin_t pin) {
    switch(pin) {
#if defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__)
        case F0: return 0;
        case F1: return _BV(MUX0);
        case F2: return _BV(MUX1);
        case F3: return _BV(MUX1) | _BV(MUX0);
        case F4: return _BV(MUX2);
        case F5: return _BV(MUX2) | _BV(MUX0);
        case F6: return _BV(MUX2) | _BV(MUX1);
        case F7: return _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
#elif defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
        case F0: return 0;
        case F1: return _BV(MUX0);
        case F4: return _BV(MUX2);
        case F5: return _BV(MUX2) | _BV(MUX0);
        case F6: return _BV(MUX2) | _BV(MUX1);
        case F7: return _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
        case D4: return _BV(MUX5);
        case D6: return _BV(MUX5) | _BV(MUX0);
        case D7: return _BV(MUX5) | _BV(MUX1);
        case B4: return _BV(MUX5) | _BV(MUX1) | _BV(MUX0);
        case B5: return _BV(MUX5) | _BV(MUX2);
        case B6: return _BV(MUX5) | _BV(MUX2) | _BV(MUX0);
#elif defined(__AVR_ATmega32A__)
        case A0: return 0;
        case A1: return _BV(MUX0);
        case A2: return _BV(MUX1);
        case A3: return _BV(MUX1) | _BV(MUX0);
        case A4: return _BV(MUX2);
        case A5: return _BV(MUX2) | _BV(MUX0);
        case A6: return _BV(MUX2) | _BV(MUX1);
        case A7: return _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
#elif defined(__AVR_ATmega328P__)
        case C0: return 0;
        case C1: return _BV(MUX0);
        case C2: return _BV(MUX1);
        case C3: return _BV(MUX1) | _BV(MUX0);
        case C4: return _BV(MUX2);
        case C5: return _BV(MUX2) | _BV(MUX0);
        // ADC7:6 not present in DIP package and not shared by GPIO pins
#endif
        default:
            return 0;
    }
}

int16_t adc_read(uint8_t mux) {
    uint8_t low;
    ADCSRA = _BV(ADEN) | ADC_PRESCALER;                          // enable ADC

#if defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
    ADCSRB = _BV(ADHSM) | (mux & _BV(MUX5));                     // high speed mode and ADC8-13
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
    ADCSRB = _BV(ADHSM)                                          // high speed mode only
#endif

    ADMUX  = aref | (mux & (_BV(MUX2) | _BV(MUX1) | _BV(MUX0))); // configure mux input (mask off MUX4:3, single channel only)
    ADCSRA |= _BV(ADSC);                                         // start the conversion
    while (ADCSRA & _BV(ADSC))
        ;                                                        // wait for result
    low = ADCL;                                                  // must read LSB first
    return (ADCH << 8) | low;                                    // must read MSB only once!
}
