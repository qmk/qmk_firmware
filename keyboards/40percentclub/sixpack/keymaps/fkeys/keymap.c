/* Copyright 2020
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

// Tap Dance declarations
enum {
    F13F19,
    F14F20,
    F15F21,
    F16F22,
    F17F23,
    F18F24,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for F13 to F18, twice for F19 to F24
    [F13F19] = ACTION_TAP_DANCE_DOUBLE(KC_F13, KC_F19), [F14F20] = ACTION_TAP_DANCE_DOUBLE(KC_F14, KC_F20), [F15F21] = ACTION_TAP_DANCE_DOUBLE(KC_F15, KC_F21),
    [F16F22] = ACTION_TAP_DANCE_DOUBLE(KC_F16, KC_F22), [F17F23] = ACTION_TAP_DANCE_DOUBLE(KC_F17, KC_F23), [F18F24] = ACTION_TAP_DANCE_DOUBLE(KC_F18, KC_F24)
};

// Add tap dance item in place of a key code
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 2x3 layout
     * .-----------------------------.
     * | F13/F19 | D14/F20 | F15/F21 |
     * |---------+---------+---------+
     * | F16/F22 | D17/F23 | F18/F24 |
     * '-----------------------------'
     */

    [0] = LAYOUT_ortho_2x3(/* F13 to F24 */
                 TD(F13F19), TD(F14F20), TD(F15F21),
		 TD(F16F22), TD(F17F23), TD(F18F24)
		),
};
