/* Copyright 2020 Ungodly Design <hello@ungodly.design>
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
#include "analog.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap _BL: (Base Layer) Default Numpad Layer
 * ,-------------------.
 * | NV | /  | *  |BK/FN|
 * |----|----|----|-----|
 * | 7  | 8  | 9  |  -  |
 * |----|----|----|-----|
 * | 4  | 5  | 6  |  +  |
 * |----|----|----|-----|
 * | 1  | 2  | 3  |     |
 * |----|----|----| En  |
 * |    0    | .  |     |
 * `--------------------'
 */
 [0] = LAYOUT_ortho_5x4(
   TG(1),  KC_PSLS,  KC_PAST,   LT(2, KC_BSPC),
   KC_7,    KC_8,    KC_9,     KC_PMNS,
   KC_4,    KC_5,    KC_6,     KC_PPLS,
   KC_1,    KC_2,    KC_3,     KC_PENT,
   KC_0,    KC_0,  KC_DOT,   KC_PENT
 ),

/* Keymap _NV: Navigation layer
 * ,-------------------.
 * |INS |HOME|PGUP|    |
 * |----|----|----|----|
 * |DEL |END |PGDN|    |
 * |----|----|----|----|
 * |    | UP |    |    |
 * |----|----|----|----|
 * |LEFT|DOWN|RIGH|    |
 * |----|----|----|    |
 * |         |    |    |
 * `-------------------'
 */
  [1] = LAYOUT_ortho_5x4(
    KC_INS,   KC_HOME,  KC_PGUP,   TG(1),
    KC_DEL,   KC_END,   KC_PGDN,   XXXXXXX,
    XXXXXXX,  KC_UP,    XXXXXXX,   XXXXXXX,
    KC_LEFT,  KC_DOWN,  KC_RGHT,   XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX
  ),

/* Keymap _FN: RGB Function Layer
 * ,-------------------.
 * |RMOD|RGBP|RTOG| FN |
 * |----|----|----|----|
 * |HUD |HUI |    |    |
 * |----|----|----|----|
 * |SAD |SAI |    |    |
 * |----|----|----|----|
 * |VAD |VAS |    |    |
 * |----|----|----|    |
 * |RST |    |    |    |
 * `-------------------'
 */
  [2] = LAYOUT_ortho_5x4(
    RGB_MOD,  RGB_M_P,  RGB_TOG,   _______,
    RGB_HUD,  RGB_HUI,  XXXXXXX,   XXXXXXX,
    RGB_SAD,  RGB_SAI,  XXXXXXX,   XXXXXXX,
    RGB_VAD,  RGB_VAI,  XXXXXXX,   XXXXXXX,
    RESET,    XXXXXXX,  XXXXXXX,   XXXXXXX
  ),
};

// (Optional) Rotary Encoder, Volume Control
void encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
      tap_code(KC_VOLU);
  } else {
      tap_code(KC_VOLD);
  }
}
