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
#define _NUM 1
#define _SYM 2

#define LOWER LT(1, KC_SPC)
#define RAISE LT(2, KC_ENT)

#define CTRLESC CTL_T(KC_ESC)
#define CTRLTAB LCTL_T(KC_TAB)
#define DSKLEFT C(G(KC_LEFT))
#define DSKRGHT C(G(KC_RIGHT))
#define LSFTSLS LSFT_T(KC_BSLS)
#define LSFTGRV LSFT_T(KC_GRV)
#define PRSCR KC_PSCREEN

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _QWE: Base Layer (Default Layer) */
  [_QW] = LAYOUT_ortho_hhkb(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,   KC_NO,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,  \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    DSKLEFT, DSKRGHT, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  CTRLTAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  LSFTSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS, KC_EQL,  KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
           KC_NO,   KC_LGUI, KC_LALT, MO(_NUM),      KC_SPC,        KC_ENT,       MO(_SYM),KC_RGUI, KC_RALT, KC_NO             \
  ),

  /* Keymap LOWER: Lower Layer */
  [_NUM] = LAYOUT_ortho_hhkb(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  CTRLTAB, KC_LT,   KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_GT,   KC_TAB,  \
  LSFTGRV, KC_UNDS, KC_LPRN, KC_DEL,  KC_MINS, KC_LBRC, KC_END,  KC_PGDN, KC_RBRC, KC_EQL,  KC_INS,  KC_RPRN, KC_PLUS, KC_RSFT, \
           PRSCR,   KC_LGUI, KC_LALT, MO(_NUM),      KC_SPC,        KC_ENT,        MO(_SYM),KC_RGUI, KC_RALT, KC_NO             \
  ),

  /* Keymap RAISE: Raise Layer */
  [_SYM] = LAYOUT_ortho_hhkb(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_HOME, KC_PGUP, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  LSFTGRV, RGB_MOD, RESET,   RGB_HUD, RGB_SAD, RGB_VAD, KC_END,  KC_PGDN, RGB_VAI, RGB_SAI, RGB_HUI, KC_NO,   RGB_TOG, KC_RSFT, \
           KC_NO,   KC_LGUI, KC_LALT, MO(_NUM),      KC_SPC,        KC_ENT,        MO(_SYM),KC_RGUI, KC_RALT, KC_NO
  )
};
