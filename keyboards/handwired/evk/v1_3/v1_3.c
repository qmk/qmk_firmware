/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "v1_3.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.
// For reference, visit https://docs.qmk.fm/#/custom_quantum_functions?id=layer-change-code

// keyboard start-up codes
// runs once when the firmware starts up
void matrix_init_kb(void) {
    // Set the LEDs pins
    setPinOutput(D5); // Layer 1 Status LED

    matrix_init_user();
}

// Set LED based on layer
__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(D5, layer_state_cmp(state, 1));
    return state;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        // writePin sets the pin high for 1 and low for 0.
        writePin(D4, led_state.caps_lock);
    }
    return res;
}
