/*
Copyright 2023 Antonio Sesmero

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

enum layer_names {
    LAYER_0,
    LAYER_1,
    LAYER_2,
    LAYER_3
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [LAYER_0] = LAYOUT_ortho_6x6(
        MEH(KC_A), MEH(KC_B), MEH(KC_C), MEH(KC_D), MEH(KC_E), MEH(KC_F), 
        MEH(KC_G), MEH(KC_H), MEH(KC_I), MEH(KC_J), MEH(KC_K), MEH(KC_L), 
        MEH(KC_M), MEH(KC_N), MEH(KC_O), MEH(KC_P), MEH(KC_Q), MEH(KC_R), 
        MEH(KC_S), MEH(KC_T), MEH(KC_U), MEH(KC_V), MEH(KC_W), MEH(KC_X), 
        MEH(KC_Y), MEH(KC_Z), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), 
        MEH(KC_5), MEH(KC_6), MEH(KC_7), MEH(KC_8), MEH(KC_9), TO(1)
    ),

    [LAYER_1] = LAYOUT_ortho_6x6(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(2)
    ),

    [LAYER_2] = LAYOUT_ortho_6x6(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(3)
    ),

    [LAYER_3] = LAYOUT_ortho_6x6(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(0)
        )
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_RED);
};
	
layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
    case LAYER_0:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    case LAYER_1:
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
    case LAYER_2:
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
    case LAYER_3:
        rgblight_sethsv_noeeprom(HSV_PURPLE);
        break;
    default:
        rgblight_sethsv_noeeprom(HSV_BLACK);
        break;
    }
  return state;
};