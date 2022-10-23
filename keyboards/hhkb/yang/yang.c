/* Copyright 2021 Kan-Ru Chen <kanru@kanru.info>
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

#include "yang.h"

extern uint8_t power_save_level;

void hhkb_led_on(uint8_t led) {
    switch (led) {
        case 1:
            writePinHigh(F4);
            break;
        case 2:
            writePinHigh(F2);
            break;
        case 3:
            writePinHigh(F0);
            break;
    }
}

void hhkb_led_off(uint8_t led) {
    switch (led) {
        case 1:
            writePinLow(F4);
            break;
        case 2:
            writePinLow(F2);
            break;
        case 3:
            writePinLow(F0);
            break;
    }
}

void keyboard_pre_init_kb(void) {
    // BT power up
    setPinOutput(D5);
    writePinLow(D5);

    // Row selectors
    setPinOutput(B0);
    setPinOutput(B1);
    setPinOutput(B2);

    // Col selectors
    setPinOutput(B3);
    setPinOutput(B4);
    setPinOutput(B5);

    // Key strobe
    setPinOutput(B6);
    writePinHigh(B6);

    // Key: input with pull-up
    setPinInputHigh(D7);

    // Unused pins on Pro2 ANSI
    // Input with pull up to save power
    setPinInputHigh(C6);
    setPinInputHigh(C7);

    // LED pin configuration
    setPinOutput(F0);
    setPinOutput(F1);
    setPinOutput(F4);
    writePinLow(F0);
    writePinLow(F1);
    writePinLow(F4);

    // Turn on switch PCB
    setPinOutput(D6);
    writePinLow(D6);

    keyboard_pre_init_user();
}

void suspend_power_down_kb(void) {
    if (power_save_level > 2) {
        // Disable UART TX to avoid current leakage
        UCSR1B &= ~_BV(TXEN1);
        // Power down BLE module
        writePinHigh(D5);
    }

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    // Power up BLE module
    writePinLow(D5);
    // Enable UART TX
    UCSR1B |= _BV(TXEN1);

    suspend_wakeup_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);

    writePin(F1, IS_LAYER_ON_STATE(state, 1));
    writePin(F0, IS_LAYER_ON_STATE(state, 2));

    return state;
}
