/* Copyright 2020 dezlidezlidezli
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

enum layers {
     _MAIN,
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder*/
    if (clockwise) {
      tap_code(KC_1);
    } else {
      tap_code(KC_2);
    }
  } else if (index == 1) { /* Second encoder*/
    if (clockwise) {
      tap_code(KC_3);
    } else {
      tap_code(KC_4);
    }
  } else if (index == 2) { /* Third encoder*/
    if (clockwise) {
      tap_code(KC_5);
    } else {
      tap_code(KC_6);
    }
  } else if (index == 3) { /* Fourth encoder*/
    if (clockwise) {
      tap_code(KC_7);
    } else {
      tap_code(KC_8);
    }
  } else if (index == 4) { /* Fifth encoder*/
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
    return true;
}

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT_ortho_1x5(
     KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE
  )
};
