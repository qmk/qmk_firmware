/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the icense, or
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

#define _BASE_BEPO \
    KC_B,     KC_Z,     KC_P,   KC_O,     KC_QUOT,      KC_DOT,   KC_V,     KC_D,     KC_L,     KC_J, \
    KC_A,     KC_U,     KC_I,   KC_E,     KC_COMM,      KC_C,     KC_T,     KC_S,     KC_R,     KC_N, \
    LT(MOUSE, KC_W),     KC_Y,     KC_X,   KC_SLSH,  KC_K,         KC_M,     KC_Q,     KC_G,     KC_H,     LT(MOUSE, KC_F),  \
                         LT(NAV, KC_BSPC),LT(MBO, KC_ENT),   LT(MEDIA, KC_TAB), LT(NUM, KC_ESC),   LT(SYM, KC_SPC),   U_NP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]    = LAYOUT_split_3x5_3_wrapper(HRM_GASC_wrapper(_BASE_BEPO)),
  [MBO]     = LAYOUT_split_3x5_3_wrapper(_MBO),
  [MEDIA]   = LAYOUT_split_3x5_3_wrapper(_MEDIA),
  [NAV]     = LAYOUT_split_3x5_3_wrapper(_NAV),
  [MOUSE]   = LAYOUT_split_3x5_3_wrapper(_MOUSE),
  [SYM]     = LAYOUT_split_3x5_3_wrapper(_SYM),
  [NUM]     = LAYOUT_split_3x5_3_wrapper(_NUM),
  [FUN]     = LAYOUT_split_3x5_3_wrapper(_FUN)
};
