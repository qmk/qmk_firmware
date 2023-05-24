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

#define setPinInput(pin) palSetLineMode((pin), PAL_MODE_INPUT)
#define setPinInputHigh(pin) palSetLineMode((pin), PAL_MODE_INPUT_PULLUP)
#define setPinInputLow(pin) palSetLineMode((pin), PAL_MODE_INPUT_PULLDOWN)
#define setPinOutputPushPull(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_PUSHPULL)
#define setPinOutputOpenDrain(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_OPENDRAIN)
#define setPinOutput(pin) setPinOutputPushPull(pin)

#define writePinHigh(pin) palSetLine(pin)
#define writePinLow(pin) palClearLine(pin)
#define writePin(pin, level)   \
    do {                       \
        if (level) {           \
            writePinHigh(pin); \
        } else {               \
            writePinLow(pin);  \
        }                      \
    } while (0)

#define readPin(pin) palReadLine(pin)

#define togglePin(pin) palToggleLine(pin)
