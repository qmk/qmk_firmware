/* Copyright 2019-2020 DMQ Design
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
    [0] = LAYOUT(/* Base */
                KC_7, KC_8,  KC_9, KC_TRNS,
                KC_4, KC_5,  KC_6, KC_TRNS,
                KC_1, KC_2,  KC_3, KC_TRNS,
                KC_0, KC_PDOT    , KC_ENTER
                ),
    [1] = LAYOUT(/* Function Layer */
                KC_F7, KC_F8,  KC_F9, KC_TRNS,
                KC_F4, KC_F5,  KC_F6, KC_TRNS,
                KC_F1, KC_F2,  KC_F3, KC_TRNS,
                KC_F10, KC_TRNS, KC_TRNS
                ),
}; 

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_VOLU); //Example of using tap_code which lets you use keycodes outside of the keymap
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code(KC_MS_WH_DOWN);  // Scroll
    } else {
      tap_code(KC_MS_WH_UP);
    }
  } else if (index == 2) { /* Third encoder */
    if (clockwise) {
        tap_code16(LCTL(KC_PPLS));  // CTRL+NumpadPlus
    } else {
        tap_code16(LCTL(KC_PMNS));   // CTRL+NumpadMinus
    }
  }
    return true;
}
