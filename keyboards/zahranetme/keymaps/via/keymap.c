/* Copyright 2024 Didot <didot404@zlab.my.id>
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

enum layer_names {
  _MAIN,
  _FN1,
  _FN2,
  _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MAIN] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

  [_FN1] = LAYOUT(KC_NO, KC_NO, KC_NO, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

  [_FN2] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, _______),

  [_FN3] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, _______)

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_MAIN] = {
    ENCODER_CCW_CW(KC_NO, KC_NO),
    ENCODER_CCW_CW(KC_NO, KC_NO)
  },
  [_FN1] = {
    ENCODER_CCW_CW(KC_NO, KC_NO),
    ENCODER_CCW_CW(KC_NO, KC_NO)
  },
  [_FN2] = {
    ENCODER_CCW_CW(KC_NO, KC_NO),
    ENCODER_CCW_CW(_______, _______)
  },
  [_FN3] = {
    ENCODER_CCW_CW(_______, _______),
    ENCODER_CCW_CW(_______, _______)
  },
};
#endif