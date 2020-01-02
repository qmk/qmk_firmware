/* Copyright 2018 Carlos Filoteo
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
#include "hvp.c"

#define LT3_ESC LT(3, KC_ESC)
#define LT4_TAB LT(4, KC_TAB)
#define D_NAVI MT(MOD_LCTL | MOD_LSFT, KC_D)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

LAYOUT(
  LT4_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  LT3_ESC, KC_A,    KC_S,    KC_D,    LT(3,KC_F),    LT(4,KC_G),    KC_H,    KC_J,    KC_K,    KC_L,    TD(TD1), TD(TD2),
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD3), KC_SFTENT,
  KC_LCTL, KC_APP, KC_LGUI, KC_LALT,  MO(2),      KC_SPC,        MO(1),  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

LAYOUT( /* Right */
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_DELETE, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, KC_UNDERSCORE, KC_PLUS, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PIPE,
  _______, _______, _______, _______, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

LAYOUT( /* Left */
  KC_TILDE,  KC_EXCLAIM,  KC_AT,  KC_HASH,  KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_BSPC,
  KC_DELETE, _______, _______, _______, _______, _______, _______, KC_UNDERSCORE, KC_PLUS, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PIPE,
  _______, _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_EQL,   KC_LBRC,   KC_RBRC,  _______,
  _______, _______, _______, _______, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

LAYOUT( /* Esc */
  KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
  _______, _______, _______, D_NAVI, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, KC_PSCR,
  _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
  _______, _______, _______, _______, KC_MUTE,     KC_MPLY,      KC_MSTP, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),
LAYOUT( /* Tab */
  _______,  RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, _______, KC_7, KC_8, KC_9, KC_0, _______,
  _______, RGB_M_P, RGB_HUD, RGB_HUI, _______, _______, _______, KC_4, KC_5, KC_6, _______, _______,
  KC_PSCR, _______, RGB_SAD, RGB_SAI, _______, _______, KC_0, KC_1, KC_2, KC_3, _______, _______,
  RESET, _______, RGB_VAD, RGB_VAI, _______,     _______,      _______, _______, _______, _______, _______
),
};