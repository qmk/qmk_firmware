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

void analogReference(uint8_t mode) { aref = mode & (_BV(REFS1) | _BV(REFS0)); }

// Arduino compatible pin input
int16_t analogRead(uint8_t pin) {
#if defined(__AVR_ATmega32U4__)
    // clang-format off
    static const uint8_t PROGMEM pin_to_mux[] = {
        //A0    A1    A2    A3    A4    A5
        //F7    F6    F5    F4    F1    F0
        0x07, 0x06, 0x05, 0x04, 0x01, 0x00,
        //A6    A7    A8    A9   A10   A11
        //D4    D7    B4    B5    B6    D6
        0x20, 0x22, 0x23, 0x24, 0x25, 0x21
    };
    // clang-format on
    if (pin >= 12) return 0;
    return adc_read(pgm_read_byte(pin_to_mux + pin));
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
    if (pin >= 8) return 0;
    return adc_read(pin);
#else
    return 0;
#endif
}

int16_t analogReadPin(pin_t pin) { return adc_read(pinToMux(pin)); }

uint8_t pinToMux(pin_t pin) {
    switch (pin) {
        // clang-format off
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
        case F0: return 0;  // ADC0
        case F1: return _BV(MUX0);  // ADC1
        case F2: return _BV(MUX1);  // ADC2
        case F3: return _BV(MUX1) | _BV(MUX0);  // ADC3
        case F4: return _BV(MUX2);  // ADC4
        case F5: return _BV(MUX2) | _BV(MUX0);  // ADC5
        case F6: return _BV(MUX2) | _BV(MUX1);  // ADC6
        case F7: return _BV(MUX2) | _BV(MUX1) | _BV(MUX0);  // ADC7
        default: return _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);  // 0V
#elif defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
        case F0: return 0;  // ADC0
        case F1: return _BV(MUX0);  // ADC1
        case F4: return _BV(MUX2);  // ADC4
        case F5: return _BV(MUX2) | _BV(MUX0);  // ADC5
        case F6: return _BV(MUX2) | _BV(MUX1);  // ADC6
        case F7: return _BV(MUX2) | _BV(MUX1) | _BV(MUX0);  // ADC7
        case D4: return _BV(MUX5);  // ADC8
        case D6: return _BV(MUX5) | _BV(MUX0);  // ADC9
        case D7: return _BV(MUX5) | _BV(MUX1);  // ADC10
        case B4: return _BV(MUX5) | _BV(MUX1) | _BV(MUX0);  // ADC11
        case B5: return _BV(MUX5) | _BV(MUX2);  // ADC12
        case B6: return _BV(MUX5) | _BV(MUX2) | _BV(MUX0);  // ADC13
        default: return _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);  // 0V
#elif defined(__AVR_ATmega32A__)
        case A0: return 0;  // ADC0
        case A1: return _BV(MUX0);  // ADC1
        case A2: return _BV(MUX1);  // ADC2
        case A3: return _BV(MUX1) | _BV(MUX0);  // ADC3
        case A4: return _BV(MUX2);  // ADC4
        case A5: return _BV(MUX2) | _BV(MUX0);  // ADC5
        case A6: return _BV(MUX2) | _BV(MUX1);  // ADC6
        case A7: return _BV(MUX2) | _BV(MUX1) | _BV(MUX0);  // ADC7
        default: return _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);  // 0V
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
        case C0: return 0;  // ADC0
        case C1: return _BV(MUX0);  // ADC1
        case C2: return _BV(MUX1);  // ADC2
        case C3: return _BV(MUX1) | _BV(MUX0);  // ADC3
        case C4: return _BV(MUX2);  // ADC4
        case C5: return _BV(MUX2) | _BV(MUX0);  // ADC5
        // ADC7:6 not present in DIP package and not shared by GPIO pins
        default: return _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);  // 0V
#endif
            // clang-format on
    }
    return 0;
}

int16_t adc_read(uint8_t mux) {
    uint16_t low;

    // Enable ADC and configure prescaler
    ADCSRA = _BV(ADEN) | ADC_PRESCALER;

#if defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
    // High speed mode and ADC8-13
    ADCSRB = _BV(ADHSM) | (mux & _BV(MUX5));
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
    // High speed mode only
    ADCSRB = _BV(ADHSM);
#endif

    // Configure mux input
#if defined(MUX4)
    ADMUX = aref | (mux & (_BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0)));
#else
    ADMUX  = aref | (mux & (_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0)));
#endif

    // Start the conversion
    ADCSRA |= _BV(ADSC);
    // Wait for result
    while (ADCSRA & _BV(ADSC))
        ;
    // Must read LSB first
    low = ADCL;
    // Must read MSB only once!
    low |= (ADCH << 8);

    // turn off the ADC
    ADCSRA &= ~(1 << ADEN);

    return low;
}
