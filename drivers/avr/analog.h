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

#ifndef _analog_h_included__
#define _analog_h_included__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void    analogReference(uint8_t mode);
int16_t analogRead(uint8_t pin);
int16_t adc_read(uint8_t mux);
#ifdef __cplusplus
}
#endif

#define ADC_REF_POWER (1 << REFS0)
#define ADC_REF_INTERNAL ((1 << REFS1) | (1 << REFS0))
#define ADC_REF_EXTERNAL (0)

// These prescaler values are for high speed mode, ADHSM = 1
#if F_CPU == 16000000L
#    define ADC_PRESCALER ((1 << ADPS2) | (1 << ADPS1))
#elif F_CPU == 8000000L
#    define ADC_PRESCALER ((1 << ADPS2) | (1 << ADPS0))
#elif F_CPU == 4000000L
#    define ADC_PRESCALER ((1 << ADPS2))
#elif F_CPU == 2000000L
#    define ADC_PRESCALER ((1 << ADPS1) | (1 << ADPS0))
#elif F_CPU == 1000000L
#    define ADC_PRESCALER ((1 << ADPS1))
#else
#    define ADC_PRESCALER ((1 << ADPS0))
#endif

// some avr-libc versions do not properly define ADHSM
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#    if !defined(ADHSM)
#        define ADHSM (7)
#    endif
#endif

#endif
