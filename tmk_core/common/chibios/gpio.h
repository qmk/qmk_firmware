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

#define setPinInput(pin) palSetLineMode(pin, PAL_MODE_INPUT)
#define setPinInputHigh(pin) palSetLineMode(pin, PAL_MODE_INPUT_PULLUP)
#define setPinInputLow(pin) palSetLineMode(pin, PAL_MODE_INPUT_PULLDOWN)
#define setPinOutput(pin) palSetLineMode(pin, PAL_MODE_OUTPUT_PUSHPULL)

#define writePinHigh(pin) palSetLine(pin)
#define writePinLow(pin) palClearLine(pin)
#define writePin(pin, level) ((level) ? (writePinHigh(pin)) : (writePinLow(pin)))

#define readPin(pin) palReadLine(pin)

#define togglePin(pin) palToggleLine(pin)

/* Operation of GPIO by port. */

typedef uint16_t port_data_t;

#define readPort(pin) palReadPort(PAL_PORT(pin))

#define setPortBitInput(pin, bit) palSetPadMode(PAL_PORT(pin), bit, PAL_MODE_INPUT)
#define setPortBitInputHigh(pin, bit) palSetPadMode(PAL_PORT(pin), bit, PAL_MODE_INPUT_PULLUP)
#define setPortBitInputLow(pin, bit) palSetPadMode(PAL_PORT(pin), bit, PAL_MODE_INPUT_PULLDOWN)
#define setPortBitOutput(pin, bit) palSetPadMode(PAL_PORT(pin), bit, PAL_MODE_OUTPUT_PUSHPULL)

#define writePortBitLow(pin, bit) palClearLine(PAL_LINE(PAL_PORT(pin), bit))
#define writePortBitHigh(pin, bit) palSetLine(PAL_LINE(PAL_PORT(pin), bit))
