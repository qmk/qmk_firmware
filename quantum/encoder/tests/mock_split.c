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

#include "mock_split.h"

bool pins[32]           = {0};
bool pinIsInputHigh[32] = {0};

uint8_t mock_set_pin_input_high(pin_t pin) {
    // dprintf("Setting pin %d input high.", pin);
    pins[pin]           = true;
    pinIsInputHigh[pin] = true;
    return 0;
}

bool mock_read_pin(pin_t pin) {
    return pins[pin];
}

bool setPin(pin_t pin, bool val) {
    pins[pin] = val;
    return val;
}

void last_encoder_activity_trigger(void) {}

__attribute__((weak)) bool is_keyboard_master(void) {
    return true;
}
