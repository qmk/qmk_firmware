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

#include <avr/io.h>

#include "compiler_support.h"
#include "pin_defs.h"

typedef uint8_t pin_t;

/* Operation of GPIO by pin. */

#define gpio_set_pin_input(pin) (DDRx_ADDRESS(pin) &= ~_BV((pin)&0xF), PORTx_ADDRESS(pin) &= ~_BV((pin)&0xF))
#define gpio_set_pin_input_high(pin) (DDRx_ADDRESS(pin) &= ~_BV((pin)&0xF), PORTx_ADDRESS(pin) |= _BV((pin)&0xF))
#define gpio_set_pin_input_low(pin) STATIC_ASSERT(0, "GPIO pulldowns in input mode are not available on AVR")
#define gpio_set_pin_output_push_pull(pin) (DDRx_ADDRESS(pin) |= _BV((pin)&0xF))
#define gpio_set_pin_output_open_drain(pin) STATIC_ASSERT(0, "Open-drain outputs are not available on AVR")
#define gpio_set_pin_output(pin) gpio_set_pin_output_push_pull(pin)

#define gpio_write_pin_high(pin) (PORTx_ADDRESS(pin) |= _BV((pin)&0xF))
#define gpio_write_pin_low(pin) (PORTx_ADDRESS(pin) &= ~_BV((pin)&0xF))
#define gpio_write_pin(pin, level) ((level) ? gpio_write_pin_high(pin) : gpio_write_pin_low(pin))

#define gpio_read_pin(pin) ((bool)(PINx_ADDRESS(pin) & _BV((pin)&0xF)))

#define gpio_toggle_pin(pin) (PORTx_ADDRESS(pin) ^= _BV((pin)&0xF))
