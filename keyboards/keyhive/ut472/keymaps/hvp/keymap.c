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
#define LT4_TAB LT(5, KC_TAB)
#define LT2 LT(2, KC_LEFT_CURLY_BRACE)
#define LT1 LT(1, KC_RIGHT_CURLY_BRACE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  LT4_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
  LT3_ESC, LG_A, LA_S, LS_D, LC_F, LT(4,KC_G), RC_H, RS_J, RA_K, RG_L, TD(TD1), TD(TD2),
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, TD(TD3), KC_SFTENT,
  KC_LCPO, KC_RPRN, KC_LGUI, KC_LALT, LT2, KC_SPC, LT1, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
),

[1] = LAYOUT( /* Right */
  KC_TILDE,  KC_EXCLAIM,  KC_AT,  KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_DELETE, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,
  _______, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_UNDS,   KC_PLUS,   KC_LBRC,   KC_RBRC,   KC_BSLS,  KC_TILD,
  _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),

[2] = LAYOUT( /* Left */
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_DELETE, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX, XXXXXXX,
  _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),

[3] = LAYOUT( /* Esc */
  KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
  _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, KC_PSCR,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
  _______, _______, _______, _______, KC_MUTE,     KC_MPLY,      KC_MSTP, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

[4] = LAYOUT( /* G */
  _______,  LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), KC_7, KC_8, KC_9, KC_BSPC,
  _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_4, KC_5, KC_6, KC_0,
  _______, _______, _______, _______, _______, _______, XXXXXXX, KC_0, KC_1, KC_2, KC_3, _______,
  QK_BOOT, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),

[5] = LAYOUT( /* Tab */
  _______,  G(S(KC_1)), G(S(KC_2)), G(S(KC_3)), G(S(KC_4)), G(S(KC_5)), G(S(KC_6)), G(S(KC_7)), G(S(KC_8)), G(S(KC_9)), G(S(KC_0)), _______,
  RGB_TOG, RGB_MOD, RGB_M_P, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______,
  KC_PSCR, _______, RGB_RMOD, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, _______, KC_CAPS,
  QK_BOOT, _______, RGB_VAD, RGB_VAI, _______,     _______,      _______, _______, _______, _______, KC_NLCK
),
};
