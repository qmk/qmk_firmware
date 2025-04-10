/* Copyright 2020 QMK
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

#include "quantum.h"

#define LED_POWER LINE_PIN13

void matrix_init_kb(void) {
    matrix_init_user();

    // Turn on the Teensy 4.x Power LED:
    gpio_set_pin_output(LED_POWER);
    gpio_write_pin_high(LED_POWER);
}

// delay_inline sleeps for |cycles| (e.g. sleeping for F_CPU will sleep 1s).
// delay_inline assumes the cycle counter has already been initialized and
// should not be modified, i.e. it is safe to call during keyboard matrix scan.
//
// ChibiOS enables the cycle counter in chcore_v7m.c:
// https://github.com/ChibiOS/ChibiOS/blob/b63023915c304092acb9f33bbab40f3ec07a7f0e/os/common/ports/ARMCMx/chcore_v7m.c#L263
static void delay_inline(const uint32_t cycles) {
    const uint32_t start = DWT->CYCCNT;
    while ((DWT->CYCCNT - start) < cycles) {
        // busy-loop until time has passed
    }
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    // Use the cycle counter to do precise timing in microseconds. The ChibiOS
    // thread sleep functions only allow sleep durations starting at 1 tick, which
    // is 100μs in our configuration.

    // Empirically: e.g. 5μs is not enough, will result in keys that don’t work
    // and ghost key presses. 10μs seems to work well.

    // On some variants of the hardware, 20μs seems to be required. This was found
    // on a combination of KB600LF+stapelberg v2020-06-30+teensy41.

    // 600 cycles at 0.6 cycles/ns == 1μs
    const uint32_t cycles_per_us = 600;
    delay_inline(20 * cycles_per_us);
}
