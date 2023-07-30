/* Copyright 2021 bdtc123
 * Copyright 2022 peepeetee
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi_arrow(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,          KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,        KC_UP,   KC_SLSH,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                              KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    )

};

//Static LEDs

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    RGB_MATRIX_INDICATOR_SET_COLOR(0, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(1, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(2, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(3, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(4, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(5, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(6, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(7, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(8, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(9, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(10, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(11, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(12, 128, 128, 128);
    RGB_MATRIX_INDICATOR_SET_COLOR(13, 128, 128, 128);

switch (get_highest_layer(layer_state)) {
        case 0:
            RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 128, 128);
            RGB_MATRIX_INDICATOR_SET_COLOR(13, 0, 128, 128);
            break;
        case 1:
            RGB_MATRIX_INDICATOR_SET_COLOR(12, 128, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(1, 128, 0, 0);
            break;
        case 2:
            RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 128, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(11, 0, 128, 0);
            break;
        case 3:
            RGB_MATRIX_INDICATOR_SET_COLOR(3, 0, 0, 128);
            RGB_MATRIX_INDICATOR_SET_COLOR(10, 0, 0, 128);
            break;
        case 4:
            RGB_MATRIX_INDICATOR_SET_COLOR(4, 0, 128, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(9, 0, 128, 0);
            break;
        case 5:
            RGB_MATRIX_INDICATOR_SET_COLOR(5, 0, 0, 128);
            RGB_MATRIX_INDICATOR_SET_COLOR(8, 0, 0, 128);
            break;
        default:
            // white
            RGB_MATRIX_INDICATOR_SET_COLOR(2, 128, 128, 128);
            break;
    }

  return false;
}
#endif
