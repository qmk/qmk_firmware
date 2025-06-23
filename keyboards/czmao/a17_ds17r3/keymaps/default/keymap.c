/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
//1    2        3        4        
LT(1,KC_NUM), LT(2,KC_PSLS), LT(3,KC_PAST), LT(4,KC_PMNS),
KC_P7, KC_P8,   KC_P9,   
KC_P4, KC_P5, KC_P6,   KC_PPLS,
KC_P1, KC_P2, KC_P3,   
KC_P0,          KC_PDOT, KC_PENT
    ),
    [1] = LAYOUT_numpad_5x4(
KC_TRNS,   KC_NUM,  MO(2),   KC_CALC,
KC_HOME, KC_UP,   KC_PGUP, 
KC_LEFT, KC_TRNS, KC_RGHT, KC_TRNS,  
KC_END,  KC_DOWN, KC_PGDN, 
KC_LSFT,          KC_RSFT, KC_N
    ),
        [2] = LAYOUT_numpad_5x4(
KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI,
RGB_TOG, RGB_SAI, KC_TRNS, 
RGB_HUD, EE_CLR, RGB_HUI, RGB_VAD,  
KC_TRNS, RGB_SAD, KC_TRNS, 
RGB_MOD,          KC_TRNS, KC_TRNS
    ),
        [3] = LAYOUT_numpad_5x4(
KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG,
KC_TRNS, KC_TRNS, KC_TRNS, 
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, 
KC_TRNS,          KC_TRNS, KC_TRNS
    )
};
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // num lock cyan
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 255, 255, 255);
    } 
    // layer state
    switch (get_highest_layer(layer_state)) {
        case 1:
            RGB_MATRIX_INDICATOR_SET_COLOR(11, 255, 255, 255);
            break;
        case 2:
            RGB_MATRIX_INDICATOR_SET_COLOR(12, 255, 255, 255);
            break;
        case 3:
            RGB_MATRIX_INDICATOR_SET_COLOR(13, 255, 255, 255);
            break;
        case 4:
            RGB_MATRIX_INDICATOR_SET_COLOR(8, 255, 255, 255);
            break;
        case 5:
            RGB_MATRIX_INDICATOR_SET_COLOR(9, 255, 255, 255);
            break;
        case 6:
            RGB_MATRIX_INDICATOR_SET_COLOR(10, 255, 255, 255);
            break;
        case 7:
            RGB_MATRIX_INDICATOR_SET_COLOR(4, 255, 255, 255);
            break;
    }
    return false;
}

