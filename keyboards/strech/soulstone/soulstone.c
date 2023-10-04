/* Copyright 2023 Strech
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

// Prepare layer indicator LED
void keyboard_post_init_kb(void) {
    setPinOutput(LAYER_INDICATOR_LED_PIN);
    writePinLow(LAYER_INDICATOR_LED_PIN);
    keyboard_post_init_user();
}

// Function for layer indicator LED
layer_state_t layer_state_set_kb(layer_state_t state) {
    writePin(LAYER_INDICATOR_LED_PIN, !layer_state_cmp(state, 0));
    return layer_state_set_user(state);
}
