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

#include "quantum.h"

extern uint8_t power_save_level;

void hhkb_led_on(uint8_t led) {
    switch (led) {
        case 1:
            gpio_write_pin_high(F4);
            break;
        case 2:
            gpio_write_pin_high(F2);
            break;
        case 3:
            gpio_write_pin_high(F0);
            break;
    }
}

void hhkb_led_off(uint8_t led) {
    switch (led) {
        case 1:
            gpio_write_pin_low(F4);
            break;
        case 2:
            gpio_write_pin_low(F2);
            break;
        case 3:
            gpio_write_pin_low(F0);
            break;
    }
}

void keyboard_pre_init_kb(void) {
    // BT power up
    gpio_set_pin_output(D5);
    gpio_write_pin_low(D5);

    // Row selectors
    gpio_set_pin_output(B0);
    gpio_set_pin_output(B1);
    gpio_set_pin_output(B2);

    // Col selectors
    gpio_set_pin_output(B3);
    gpio_set_pin_output(B4);
    gpio_set_pin_output(B5);

    // Key strobe
    gpio_set_pin_output(B6);
    gpio_write_pin_high(B6);

    // Key: input with pull-up
    gpio_set_pin_input_high(D7);

    // Unused pins on Pro2 ANSI
    // Input with pull up to save power
    gpio_set_pin_input_high(C6);
    gpio_set_pin_input_high(C7);

    // LED pin configuration
    gpio_set_pin_output(F0);
    gpio_set_pin_output(F1);
    gpio_set_pin_output(F4);
    gpio_write_pin_low(F0);
    gpio_write_pin_low(F1);
    gpio_write_pin_low(F4);

    // Turn on switch PCB
    gpio_set_pin_output(D6);
    gpio_write_pin_low(D6);

    keyboard_pre_init_user();
}

void suspend_power_down_kb(void) {
    if (power_save_level > 2) {
        // Disable UART TX to avoid current leakage
        UCSR1B &= ~_BV(TXEN1);
        // Power down BLE module
        gpio_write_pin_high(D5);
    }

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    // Power up BLE module
    gpio_write_pin_low(D5);
    // Enable UART TX
    UCSR1B |= _BV(TXEN1);

    suspend_wakeup_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);

    gpio_write_pin(F1, IS_LAYER_ON_STATE(state, 1));
    gpio_write_pin(F0, IS_LAYER_ON_STATE(state, 2));

    return state;
}
