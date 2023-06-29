/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

// Need to disable GCC's "maybe-uninitialized" warning for this file, as it causes issues when running `KEEP_INTERMEDIATES=yes`.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#include <util/delay.h>
#pragma GCC diagnostic pop

// http://ww1.microchip.com/downloads/en/devicedoc/atmel-0856-avr-instruction-set-manual.pdf
// page 22: Table 4-2. Arithmetic and Logic Instructions
/*
    for (uint16_t i = times; i > 0; i--) {
        __builtin_avr_delay_cycles(1);
    }

    .L3:  sbiw r24,0  // loop step 1
          brne .L4    // loop step 2
          ret
    .L4:  nop         // __builtin_avr_delay_cycles(1);
          sbiw r24,1  // loop step 3
          rjmp .L3    // loop step 4
*/

#define AVR_sbiw_clocks 2
#define AVR_rjmp_clocks 2
#define AVR_brne_clocks 2
#define AVR_WAIT_LOOP_OVERHEAD (AVR_sbiw_clocks + AVR_brne_clocks + AVR_sbiw_clocks + AVR_rjmp_clocks)

#define wait_ms(ms)                             \
    do {                                        \
        if (__builtin_constant_p(ms)) {         \
            _delay_ms(ms);                      \
        } else {                                \
            for (uint16_t i = ms; i > 0; i--) { \
                _delay_ms(1);                   \
            }                                   \
        }                                       \
    } while (0)
#define wait_us(us)                                                                     \
    do {                                                                                \
        if (__builtin_constant_p(us)) {                                                 \
            _delay_us(us);                                                              \
        } else {                                                                        \
            for (uint16_t i = us; i > 0; i--) {                                         \
                __builtin_avr_delay_cycles((F_CPU / 1000000) - AVR_WAIT_LOOP_OVERHEAD); \
            }                                                                           \
        }                                                                               \
    } while (0)
#define wait_cpuclock(n) __builtin_avr_delay_cycles(n)
#define CPU_CLOCK F_CPU

/* The AVR series GPIOs have a one clock read delay for changes in the digital input signal.
 * But here's more margin to make it two clocks. */
#ifndef GPIO_INPUT_PIN_DELAY
#    define GPIO_INPUT_PIN_DELAY 2
#endif

#define waitInputPinDelay() wait_cpuclock(GPIO_INPUT_PIN_DELAY)
