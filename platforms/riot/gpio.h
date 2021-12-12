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

#include "periph/gpio.h"
#include "pin_defs.h"

typedef gpio_t pin_t;

#define setPinInput(pin) gpio_init(pin, GPIO_IN)
#define setPinInputHigh(pin) gpio_init(pin, GPIO_IN_PU)
#define setPinInputLow(pin) gpio_init(pin, GPIO_IN_PD)
#define setPinOutput(pin) gpio_init(pin, GPIO_OUT)
#define writePinHigh(pin) gpio_set(pin)
#define writePinLow(pin) gpio_clear(pin)
#define writePin(pin, level) gpio_write(pin, level)
#define readPin(pin) gpio_read(pin)
#define togglePin(pin) gpio_toggle(pin)
