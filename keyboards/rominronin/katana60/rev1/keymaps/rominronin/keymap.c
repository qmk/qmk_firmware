/* Copyright 2017 Baris Tosun
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

// MacOS based definitions.
#define K_SPCFN LT(SYMB, KC_SPACE) // Tap for space, hold for symbols layer
#define K_PRVWD LALT(KC_LEFT)      // Previous word
#define K_NXTWD LALT(KC_RIGHT)     // Next word
#define K_LSTRT LGUI(KC_LEFT)      // Start of line
#define K_LEND  LGUI(KC_RIGHT)     // End of line
#define UNDO    LGUI(KC_Z)         // UNDO
#define CUT     LGUI(KC_X)         // CUT
#define COPY    LGUI(KC_C)         // COPY
#define PASTE   LGUI(KC_V)         // PASTE


#define BASE 0 // Default
#define NUMB 1 // Numbers
#define SYMB 2 // Symbols
#define CURS 3 // Text Editing

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT( /* Base */
  KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    DF(1),   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC,          KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_BSPC,
  MO(3),   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_HOME,          KC_PGUP, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_END,  KC_DEL,  KC_PGDN, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  MO(2),   KC_LCTL, KC_LALT, KC_LGUI,                   KC_BSPC, KC_ENT,  K_SPCFN,          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,MO(2)
    ),
[NUMB] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, DF(0),   KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______, _______,
  _______, _______, _______, KC_MS_U, _______, _______, _______,          KC_7,    KC_8,    KC_9,    KC_PPLS, _______, _______, _______,
  _______, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,          KC_4,    KC_5,    KC_6,    KC_PPLS, _______, _______, _______,
  _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_PENT, _______, _______, _______,
  _______, _______, _______, _______,                   KC_BTN1, _______, KC_P0,            KC_PDOT, KC_PENT, _______, _______, _______
    ),
[SYMB] = LAYOUT(
  QK_BOOT, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,          _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_VOLD,          KC_VOLU, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, KC_PLUS, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_MPRV, KC_MPLY, KC_MNXT, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
  _______, _______, _______, _______,                   KC_DEL,  _______, _______,          _______, _______, _______, _______, _______
    ),
[CURS] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_WH_U, _______, _______, _______, _______,          _______, _______, K_PRVWD, KC_UP,   K_NXTWD, _______, _______,
  _______, KC_LCTL, KC_WH_D, KC_LSFT, _______, _______, _______,          _______, KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  _______,
  _______, UNDO,    CUT,     COPY,    PASTE,   _______, _______, _______, _______, _______, K_LSTRT, _______, K_LEND,  _______, _______,
  _______, _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
    )

};
