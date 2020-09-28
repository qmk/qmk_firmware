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

#pragma once

#include <stdint.h>
#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif
void    analogReference(uint8_t mode);
int16_t analogRead(uint8_t pin);

int16_t analogReadPin(pin_t pin);
uint8_t pinToMux(pin_t pin);

int16_t adc_read(uint8_t mux);
#ifdef __cplusplus
}
#endif

#define ADC_REF_EXTERNAL 0                          // AREF, Internal Vref turned off
#define ADC_REF_POWER _BV(REFS0)                    // AVCC with external capacitor on AREF pin
#define ADC_REF_INTERNAL (_BV(REFS1) | _BV(REFS0))  // Internal 2.56V Voltage Reference with external capacitor on AREF pin (1.1V for 328P)

// These prescaler values are for high speed mode, ADHSM = 1
#if F_CPU == 16000000L || F_CPU == 12000000L
#    define ADC_PRESCALER (_BV(ADPS2) | _BV(ADPS1))  // /64
#elif F_CPU == 8000000L
#    define ADC_PRESCALER (_BV(ADPS2) | _BV(ADPS0))  // /32
#elif F_CPU == 4000000L
#    define ADC_PRESCALER (_BV(ADPS2))  // /16
#elif F_CPU == 2000000L
#    define ADC_PRESCALER (_BV(ADPS1) | _BV(ADPS0))  // /8
#elif F_CPU == 1000000L
#    define ADC_PRESCALER _BV(ADPS1)  // /4
#else
#    define ADC_PRESCALER _BV(ADPS0)  // /2
#endif
