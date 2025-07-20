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

#include <hal.h>
#include "pin_defs.h"

typedef ioline_t pin_t;

/* Operation of GPIO by pin. */

#define gpio_set_pin_input(pin) palSetLineMode((pin), PAL_MODE_INPUT)
#define gpio_set_pin_input_high(pin) palSetLineMode((pin), PAL_MODE_INPUT_PULLUP)
#define gpio_set_pin_input_low(pin) palSetLineMode((pin), PAL_MODE_INPUT_PULLDOWN)
#define gpio_set_pin_output_push_pull(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_PUSHPULL)
#define gpio_set_pin_output_open_drain(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_OPENDRAIN)
#define gpio_set_pin_output(pin) gpio_set_pin_output_push_pull(pin)

#define gpio_write_pin_high(pin) palSetLine(pin)
#define gpio_write_pin_low(pin) palClearLine(pin)
#define gpio_write_pin(pin, level)    \
    do {                              \
        if (level) {                  \
            gpio_write_pin_high(pin); \
        } else {                      \
            gpio_write_pin_low(pin);  \
        }                             \
    } while (0)

#define gpio_read_pin(pin) palReadLine(pin)

#define gpio_toggle_pin(pin) palToggleLine(pin)
