/* Copyright 2024 rot13labs
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
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,     KC_O,    KC_P,    KC_BSPC,
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,     KC_L,             KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_RCTL,           KC_UP,   DF(1),
      KC_LCTL, KC_LGUI, MO(2),            KC_SPC,         KC_SPC,         MO(1),    KC_LEFT, KC_DOWN, KC_RIGHT),

  /* FN - symbols & audio controls */
  [1] = LAYOUT(
      KC_ESC,  KC_MINS, KC_EQL,  KC_E,  KC_R,   KC_T,    KC_Y,   KC_U,    KC_LBRC,  KC_RBRC, KC_BSLS,   KC_BSPC,
      KC_TAB,  KC_A,    KC_S,    KC_D,  KC_F,   KC_G,    KC_H,   KC_J,    KC_SCLN,  KC_QUOT,            KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,   KC_COMM, KC_DOT, KC_SLSH, KC_RCTL,           KC_VOLU,   DF(2),
      KC_LCTL, KC_LGUI, KC_LALT,        KC_SPC,          KC_SPC,          KC_TRNS,  KC_MPRV, KC_VOLD,   KC_MNXT),

  /* ALT - numbers */
  [2] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,     KC_9,     KC_0,    KC_DEL,
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,     KC_L,              KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_RCTL,            KC_UP,   DF(3),
      KC_LCTL, KC_LGUI, _______,          MO(3),          KC_SPC,         KC_RALT,  KC_LEFT,  KC_DOWN, KC_RIGHT),

  /* SPC - RGB control layer */
  [3] = LAYOUT(
      KC_ESC,  KC_Q,    RGB_M_SW, KC_E,  RGB_M_R, KC_T,    KC_Y,   RM_SPDD, RM_SPDU,  RM_PREV,  RM_NEXT, KC_DEL,
      KC_TAB,  KC_A,    RGB_M_P,  KC_D,  KC_F,    KC_G,    KC_H,   RM_SATD, RM_SATU,  RM_TOGG,           KC_ENT,
      KC_LSFT, KC_Z,    KC_X,     KC_C,  KC_V,    RGB_M_B, KC_N,   KC_M,    KC_RCTL,            RM_VALU, DF(0),
      KC_LCTL, KC_LGUI, KC_LALT,         KC_SPC,           KC_SPC,          _______,  RM_HUED,  RM_VALD, RM_HUEU),
};