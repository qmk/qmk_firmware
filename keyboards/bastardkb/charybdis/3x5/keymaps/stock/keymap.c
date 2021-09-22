/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
#include "wrappers.h"

#define LAYOUT_split_3x5_3_wrapper(...)      LAYOUT_split_3x5_3(__VA_ARGS__)

#define _BASE_QWERTY \
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  \
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, \
    LT(MOUSE, KC_Z),  KC_X,    KC_C,    KC_V,  KC_B,                  KC_N,    KC_M,    KC_COMM, KC_DOT, LT(MOUSE, KC_SLSH),  \
        LT(NAV, KC_BSPC), LT(MBO, KC_ENT), LT(MEDIA, KC_TAB),         LT(NUM, KC_ESC),   LT(SYM, KC_SPC),   U_NP


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]    = LAYOUT_split_3x5_3_wrapper(HRM_GASC_wrapper(_BASE_QWERTY)),
  [MBO]     = LAYOUT_split_3x5_3_wrapper(_MBO),
  [MEDIA]   = LAYOUT_split_3x5_3_wrapper(_MEDIA),
  [NAV]     = LAYOUT_split_3x5_3_wrapper(_NAV),
  [MOUSE]   = LAYOUT_split_3x5_3_wrapper(_MOUSE),
  [SYM]     = LAYOUT_split_3x5_3_wrapper(_SYM),
  [NUM]     = LAYOUT_split_3x5_3_wrapper(_NUM),
  [FUN]     = LAYOUT_split_3x5_3_wrapper(_FUN)
};
