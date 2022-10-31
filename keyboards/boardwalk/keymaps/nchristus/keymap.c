/*
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

// Layer shorthand
#define _QW 0

#define LOWER LT(1, KC_SPC)
#define RAISE LT(2, KC_ENT)

#define CTRLESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _QWE: Base Layer (Default Layer) */
  [_QW] = LAYOUT_ortho_hhkb(
  QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, _______, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  CTRLESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, _______, KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
           MO(3),   KC_LCTL, KC_LALT, KC_LGUI,       RAISE,         LOWER,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT           \
  ),

  /* Keymap LOWER: Lower Layer */
  [1] = LAYOUT_ortho_hhkb(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, _______,       XXXXXXX,       _______,       _______, _______, _______, _______
  ),

  /* Keymap RAISE: Raise Layer */
  [2] = LAYOUT_ortho_hhkb(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, _______,       _______,       XXXXXXX,       _______, _______, _______, _______
  ),

  /* Keymap _FL: Function Layer */
  [3] = LAYOUT_ortho_hhkb(
  QK_BOOT, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, _______,       _______,       _______,       _______, _______, _______, _______
  )
};
