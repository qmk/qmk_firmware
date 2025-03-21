/* Copyright 2018 Jack Humbert
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

#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT(
  KC_P7  , KC_P8, KC_P9  , KC_PAST, KC_ESC , KC_Q   , KC_W   , KC_E, KC_R   , KC_T  , KC_Y, KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL , KC_BSPC ,
  KC_P4  , KC_P5, KC_P6  , KC_PMNS, KC_TAB , KC_A   , KC_S   , KC_D, KC_F   , KC_G  , KC_H, KC_J   , KC_K   , KC_L   , KC_SCLN,          KC_ENT  ,
  KC_P1  , KC_P2, KC_P3  , KC_PPLS, KC_LSFT,          KC_Z   , KC_X, KC_C   , KC_V  , KC_B, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP   ,KC_RSFT ,
  MO(_FL), KC_P0, KC_PDOT, KC_PENT, KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,       KC_SPC , KC_BSPC, KC_APP , KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
  */
  [_FL] = LAYOUT(
  KC_P7 , KC_P8, KC_P9  , KC_VOLU, QK_BOOT  , KC_Q   , KC_W   , KC_E, KC_R   , KC_T  , KC_Y, KC_U   , KC_I   , KC_LBRC, KC_RBRC, KC_INS , KC_BSPC ,
  KC_P4 , KC_P5, KC_P6  , KC_VOLD, KC_TAB , KC_A   , KC_SCRL, KC_D, KC_F   , KC_G  , KC_H, KC_J   , KC_K   , KC_L   , KC_QUOT,          KC_BSLS ,
  KC_P1 , KC_P2, KC_P3  , KC_PEQL, KC_LSFT,          KC_Z   , KC_X, KC_CAPS, KC_V  , KC_B, KC_NUM , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_PGUP ,
  KC_END, KC_P0, KC_PDOT, KC_PENT, KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,       KC_SPC , KC_BSPC, KC_APP , MO(_FL), KC_HOME, KC_PGDN),
};
