/*
Copyright 2023 ThePanduuh <thepanduuh.kb@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap

enum layer_names {
	_BASE,
	_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_6x4(
  KC_ESC , KC_EQL , KC_BSPC, MO(1)  ,
  KC_NUM , KC_PSLS, KC_PAST, KC_PMNS,
  KC_P7  , KC_P8  , KC_P9  , KC_PPLS,
  KC_P4  , KC_P5  , KC_P6  , KC_PPLS,
  KC_P1  , KC_P2  , KC_P3  , KC_PENT,
  KC_P0  , KC_P0  , KC_PDOT, KC_PENT
  ),

  [_FN] = LAYOUT_ortho_6x4(
  KC_TRNS, KC_TRNS, KC_DEL , KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_HOME, KC_UP  , KC_PGUP, KC_TRNS,
  KC_LEFT, KC_TRNS, KC_RGHT, KC_TRNS,
  KC_END , KC_DOWN, KC_PGDN, QK_BOOT,
  KC_INS , KC_INS , KC_DEL , QK_BOOT
  )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
  [_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
  [_FN]   = {ENCODER_CCW_CW(KC_NO, KC_NO)},
};
#endif
