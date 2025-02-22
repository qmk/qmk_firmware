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

#include "pin_defs.h"

#if __has_include_next("gpio.h")
#    include_next "gpio.h" /* Include the platforms gpio.h */
#endif

// ======== DEPRECATED DEFINES - DO NOT USE ========

#define setPinInput(pin) gpio_set_pin_input(pin)
#define setPinInputHigh(pin) gpio_set_pin_input_high(pin)
#define setPinInputLow(pin) gpio_set_pin_input_low(pin)
#define setPinOutputPushPull(pin) gpio_set_pin_output_push_pull(pin)
#define setPinOutputOpenDrain(pin) gpio_set_pin_output_open_drain(pin)
#define setPinOutput(pin) gpio_set_pin_output_push_pull(pin)

#define writePinHigh(pin) gpio_write_pin_high(pin)
#define writePinLow(pin) gpio_write_pin_low(pin)
#define writePin(pin, level) gpio_write_pin(pin, level)

#define readPin(pin) gpio_read_pin(pin)

#define togglePin(pin) gpio_toggle_pin(pin)
