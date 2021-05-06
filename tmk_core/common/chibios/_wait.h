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

#include <ch.h>

/* chThdSleepX of zero maps to infinite - so we map to a tiny delay to still yield */
#define wait_ms(ms)                     \
    do {                                \
        if (ms != 0) {                  \
            chThdSleepMilliseconds(ms); \
        } else {                        \
            chThdSleepMicroseconds(1);  \
        }                               \
    } while (0)
#define wait_us(us)                     \
    do {                                \
        if (us != 0) {                  \
            chThdSleepMicroseconds(us); \
        } else {                        \
            chThdSleepMicroseconds(1);  \
        }                               \
    } while (0)

/* For GPIOs on ARM-based MCUs, the input pins are sampled by the clock of the bus
 * to which the GPIO is connected.
 * The connected buses differ depending on the various series of MCUs.
 * And since the instruction execution clock of the CPU and the bus clock of GPIO are different,
 * there is a delay of several clocks to read the change of the input signal.
 *
 * Define this delay with the GPIO_INPUT_PIN_DELAY macro.
 * If the GPIO_INPUT_PIN_DELAY macro is not defined, the following default values will be used.
 * (A fairly large value of 0.25 microseconds is set.)
 */

#include "wait.c"

#ifndef GPIO_INPUT_PIN_DELAY
#    define GPIO_INPUT_PIN_DELAY (STM32_SYSCLK / 1000000L / 4)
#endif

#define waitInputPinDelay() wait_cpuclock(GPIO_INPUT_PIN_DELAY)
