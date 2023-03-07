/* Copyright 2021 John Mueller
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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _VIMA,
    _VIMI
};

// Define custom keycodes
enum my_keycodes {
    CLUTCH_A = SAFE_RANGE,
    CLUTCH_I
};

// Layer-specific lighting
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _VIMA:
        writePinLow(F4);
	writePinHigh(F5);
        break;
    case _VIMI:
        writePinHigh(F4);
	writePinLow(F5);
        break;
    default:
        writePinHigh(F4);
        writePinHigh(F5);
        break;
    }
    return state;
};

// Define the layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_VIMA] = LAYOUT(
        TO(_VIMA),    TO(_VIMI),  CLUTCH_A
    ),

    [_VIMI] = LAYOUT(
        TO(_VIMA),    TO(_VIMI),  CLUTCH_I
    )
};

// Define vim-clutching
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CLUTCH_A:
        if (record->event.pressed) {
            tap_code_delay(KC_ESC, 50); 
            tap_code_delay(KC_A, 50); 
        } else {
            tap_code_delay(KC_ESC, 50); 
        }
        break;
    case CLUTCH_I:
        if (record->event.pressed) {
            tap_code_delay(KC_ESC, 50); 
            tap_code_delay(KC_I, 50); 
        } else {
            tap_code_delay(KC_ESC, 50); 
        }
        break;
    }
    return true;
};
