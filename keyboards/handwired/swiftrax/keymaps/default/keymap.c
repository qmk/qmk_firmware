/* Copyright 2020 Swiftrax
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

enum{ //Tap Dance Declarations 
    TD_RALT_RGUI = 0,
    TD_LALT_LGUI
};

#define RALT_RG TD(TD_RALT_RGUI)
#define LALT_LG TD(TD_LALT_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
		KC_F1, KC_F13, KC_ESC, 	KC_1, 	KC_2, 	KC_3, 	KC_4, 	KC_5, 	KC_6, 	KC_7, 	KC_8, 	KC_9, 	KC_0, 	 KC_MINS, 	KC_EQL, KC_GRV, KC_BSLS, 
		KC_F2, KC_F14, KC_TAB, 	KC_Q, 	KC_W, 	KC_E, 	KC_R, 	KC_T, 	KC_Y, 	KC_U, 	KC_I, 	KC_O, 	KC_P, 	 KC_LBRC, 	KC_RBRC,KC_BSPC,KC_DEL, 
		KC_F3, KC_F15, KC_LCTL, KC_A, 	KC_S, 	KC_D, 	KC_F, 	KC_G, 	KC_H, 	KC_J, 	KC_K, 	KC_L, 	KC_SCLN, KC_QUOT, 	KC_ENT, 		KC_PGUP, 
		KC_F4, KC_F16, KC_LSFT, KC_Z, 	KC_X, 	KC_C, 	KC_V, 	KC_B, 	KC_N, 	KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_NO, 	KC_UP, 			KC_PGDN, 
		KC_F5, KC_F17, KC_LCTL, LALT_LG, 				KC_SPC, 			RALT_RG, 	KC_RCTL, 				   KC_LEFT, KC_DOWN, KC_RGHT),

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for L-Alt, twice for L-GUI
    //[TD_LALT_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
    // Tap once for R-Alt, twice for R-GUI
    [TD_RALT_RGUI] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_RGUI)
};