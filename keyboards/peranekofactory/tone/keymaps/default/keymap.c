/* Copyright 2021 peraneko
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
        C(S(KC_E)), S(KC_TAB),  KC_TAB,      KC_0,
        KC_LSFT,    C(KC_LEFT), C(KC_RIGHT), C(KC_Z)
    )
};

/* Rotary encoder settings */
bool encoder_update_user(uint8_t index, bool clockwise) {
   if (clockwise) {
        tap_code(KC_UP);    //Rotary encoder clockwise
    } else {
        tap_code(KC_DOWN);  //Rotary encoder Reverse clockwise
    }
    return true;
}
