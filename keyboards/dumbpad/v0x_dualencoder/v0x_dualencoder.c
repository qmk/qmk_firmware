/* Copyright 2020 imchipwood
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
#include "v0x_dualencoder.h"

void keyboard_pre_init_kb(void) {
    // Set LED IO as outputs
    setPinOutput(LED_00);
    setPinOutput(LED_01);
    keyboard_pre_init_user();
}

void shutdown_user() {
    // Shutdown LEDs
    writePinLow(LED_00);
    writePinLow(LED_01);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    // Layer LEDs act as binary indication of current layer
    uint8_t layer = get_highest_layer(state);
    writePin(LED_00, layer & 0b1);
    writePin(LED_01, (layer >> 1) & 0b1);
    return layer_state_set_user(state);
}

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    uint8_t led_delay_ms = 80;
    for (int i = 0; i < 2; i++) {
        writePinHigh(LED_00);
        writePinHigh(LED_01);
        wait_ms(led_delay_ms);
        writePinLow(LED_00);
        writePinLow(LED_01);
        if (i < 1) {
            wait_ms(led_delay_ms);
        }
    }

    matrix_init_user();
}
