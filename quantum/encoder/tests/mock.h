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

/* Here, "pins" from 0 to 31 are allowed. */
#define ENCODERS_PAD_A \
    { 0 }
#define ENCODERS_PAD_B \
    { 1 }

typedef uint8_t pin_t;

extern bool pins[];
extern bool pinIsInputHigh[];

#define setPinInputHigh(pin) (mockSetPinInputHigh(pin))
#define readPin(pin) (mockReadPin(pin))

uint8_t mockSetPinInputHigh(pin_t pin);

bool mockReadPin(pin_t pin);

bool setPin(pin_t pin, bool val);
