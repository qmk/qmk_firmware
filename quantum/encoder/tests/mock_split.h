/* Copyright 2021 Balz Guenat
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
#include <stdbool.h>

#define SPLIT_KEYBOARD
typedef uint8_t pin_t;

void encoder_state_raw(uint8_t* slave_state);
void encoder_update_raw(uint8_t* slave_state);

extern bool pins[];
extern bool pinIsInputHigh[];

#define gpio_set_pin_input_high(pin) (mock_set_pin_input_high(pin))
#define gpio_read_pin(pin) (mock_read_pin(pin))

uint8_t mock_set_pin_input_high(pin_t pin);

bool mock_read_pin(pin_t pin);

bool setPin(pin_t pin, bool val);
