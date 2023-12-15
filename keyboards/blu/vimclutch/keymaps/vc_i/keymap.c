/* Copyright 2023 Brandon Lu
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

enum layer_names {
    _VC,
    _VIM
};

enum my_keycodes {
    USER_CLUTCH = QK_USER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_VC] = LAYOUT(
        TO(_VC),    TO(_VIM),  KC_F13
    ),

    [_VIM] = LAYOUT(
        TO(_VC),    TO(_VIM),  USER_CLUTCH
    )
};

/* Layer-specific lighting */
layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(F4, !layer_state_cmp(state, _VC));
    writePin(F5, !layer_state_cmp(state, _VIM));
    return state;
};

/* Define vim-clutching */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case USER_CLUTCH:
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
