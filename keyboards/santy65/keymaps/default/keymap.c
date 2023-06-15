/* Copyright 2023 Your Name (@santy81855)
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
    [0] = LAYOUT(
	KC_F15, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_BSLS), LALT(KC_END), KC_TRNS, 
	KC_F16, KC_TAB, KC_SCLN, KC_COMMA, KC_DOT, KC_P, KC_Y, 		 		   		KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLS, KC_LBRC, KC_RBRC, KC_TRNS, 
	KC_F17, KC_BSPC, KC_A, KC_O, KC_E, KC_U, KC_I, 		 						KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT, KC_TRNS, 
	KC_F18, KC_RSFT, KC_QUOTE, KC_Q, KC_J, KC_K, KC_X, 						KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, KC_UP, 
	KC_TRNS, KC_LCTL, KC_LGUI, KC_LALT, KC_SPACE, KC_SPACE, KC_TRNS,		KC_SPACE, KC_SPACE, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAIN] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(C(KC_PGUP), C(KC_PGDN))  },
};
#endif
