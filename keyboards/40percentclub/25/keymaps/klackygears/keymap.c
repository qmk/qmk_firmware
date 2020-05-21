/* Copyright 2020 klackygears
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
#include "klackygears.h"
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// #define _QWERTY 0
// #define _LOWER  1



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_5x5_wrapper(
    _________________MEDIA_____________________,\
    RGBRST, RGBRST, RGBRST, RGBRST, RGBRST,\
    RGBRST, RGBRST, RGBRST, RGBRST, RGBRST,\
    RGBRST, RGBRST, RGBRST, RGBRST, RGBRST,\
    RGBRST, RGBRST, RGBRST, RGBRST, RGBRST\
  ),


  [1] = LAYOUT_ortho_5x5_wrapper(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    \
    _________________NUMB_R1___________________, \
    _________________NUMB_R2___________________, \
    _________________NUMB_R3_MAC_______________, \
    KC_____, ________MAC_THUMB_CLUSTER_________ \
  ),
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {

}
