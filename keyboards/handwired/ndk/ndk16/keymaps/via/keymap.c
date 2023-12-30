/*
Copyright 2023 kevin (@itskevin-zz)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FUNC,
    _GAME,
    _CODE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐     
     * │ e │NUM│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │   │ 7 │ 8 │ 9 │   │
     * │   ├───┼───┼───┤ + │
     * │   │ 4 │ 5 │ 6 │   │
     * │   ├───┼───┼───┼───┤
     * │   │ 1 │ 2 │ 3 │   │
     * ├───┼───┴───┼───┤ ← │
     * │ D │   0   │ . │   │
     * └───┴───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_5x5(
        KC_MUTE, KC_NUM, KC_PSLS, KC_PAST,  KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3, 
        TO(1), KC_P0,   KC_PDOT,  KC_PENT
    ),
    [1] = LAYOUT_numpad_5x5(
        _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,
        _______,   C(KC_A),   _______,   _______,
        C(KC_X),   C(KC_C),   C(KC_V), 
        TO(2),   C(KC_Z),   _______,   _______
    ),
    [2] = LAYOUT_numpad_5x5(
        _______,   _______,   _______,   _______,   _______,
        KC_1,   KC_2,   KC_3,  
        KC_Q,   KC_W,   KC_E, _______,
        KC_A,   KC_S,   KC_D, 
        TO(3),   _______,   _______,   _______
    ),
    [3] = LAYOUT_numpad_5x5(
        _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,
        C(KC_GRV),   C(S(KC_K)),   C(KC_SLSH), 
        TO(0),   _______,   _______,   _______
    )
    
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif