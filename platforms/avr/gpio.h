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
#include "pin_defs.h"

typedef uint8_t pin_t;

/* Operation of GPIO by pin. */

#define setPinInput(pin) (DDRx_ADDRESS(pin) &= ~_BV((pin)&0xF), PORTx_ADDRESS(pin) &= ~_BV((pin)&0xF))
#define setPinInputHigh(pin) (DDRx_ADDRESS(pin) &= ~_BV((pin)&0xF), PORTx_ADDRESS(pin) |= _BV((pin)&0xF))
#define setPinInputLow(pin) _Static_assert(0, "AVR processors cannot implement an input as pull low")
#define setPinOutputPushPull(pin) (DDRx_ADDRESS(pin) |= _BV((pin)&0xF))
#define setPinOutputOpenDrain(pin) _Static_assert(0, "AVR platform does not implement an open-drain output")
#define setPinOutput(pin) setPinOutputPushPull(pin)

#define writePinHigh(pin) (PORTx_ADDRESS(pin) |= _BV((pin)&0xF))
#define writePinLow(pin) (PORTx_ADDRESS(pin) &= ~_BV((pin)&0xF))
#define writePin(pin, level) ((level) ? writePinHigh(pin) : writePinLow(pin))

#define readPin(pin) ((bool)(PINx_ADDRESS(pin) & _BV((pin)&0xF)))

#define togglePin(pin) (PORTx_ADDRESS(pin) ^= _BV((pin)&0xF))
