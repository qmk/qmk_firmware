/*  Keymap for Space Oddity Keyboard
    Copyright (C) 2017  James Taylor

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Custom keycodes needed for dynamic macros.
enum custom_keycodes {

  QWERTY = SAFE_RANGE,
  PAIR_PR,
  PAIR_BR,
  PAIR_CB,
  LAMBDA
};

// Tap Dance initializer.
enum {

  SFT_CAPS = 0,

};

// Tap dance actions - double tap for Caps Lock.
tap_dance_action_t tap_dance_actions[] = {

  [SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Here is an ASCII version of the base layout. Note that Dynamic Macros 1 and 2 are considered Macro 5 and Macro 6.
   *
   *  ___________________________________________________________________________________
   * |           |           |           |           |           |  Dynamic  |  Dynamic  |
   * |    ()     |    []     |    {}     |   NO OP   |   NO OP   |  Macro 1  |  Macro 2  |
   * |___________|___________|___________|___________|___________|___________|___________|
   * |           |     |     |     |     |     |     |     |     |     |     |           |
   * |     `     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |   BKSP    |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   * |           |     |     |     |     |     |     |     |     |     |     |           |
   * |    TAB    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |     -     |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   * |           |     |     |     |     |     |     |     |     |     |     |           |
   * |ESC (CTL_T)|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |     '     |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   *   |         |     |     |     |     |     |     |     |     |     |     |         |
   *   |  SHFT   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |SHFT(ENT)|
   *   |_________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_________|
   *       |     |     |     |     |           |           | ALT | HYP | LT 1| LT 2|
   *       |MO(2)|MO(1)| GUI | ALT |    CTRL   |    SPC    |(LFT)|(RGT)| (UP)|(DWN)|
   *       |_____|_____|_____|_____|___________|___________|_____|_____|_____|_____|
   */

  [0] = LAYOUT(
    PAIR_PR,       PAIR_BR,          PAIR_CB,          XXXXXXX,          XXXXXXX,                 DM_PLY1,                      DM_PLY2,
    KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,           KC_9,           KC_0,         KC_BSPC,
    KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,           KC_O,           KC_P,         KC_MINS,
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,           KC_L,           KC_SCLN,      KC_QUOT,
    TD(SFT_CAPS),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,        KC_DOT,         KC_SLSH,      SFT_T(KC_ENT),
    MO(2),         MO(1),   KC_LGUI, KC_RALT,          KC_LCTL, KC_SPC,           ALT_T(KC_LEFT), ALL_T(KC_RGHT), LT(1, KC_UP), LT(2, KC_DOWN)
  ),

  /* Function layer.
   * Blank keys correspond to the KC_TRNS keycode.
   *
   *  ___________________________________________________________________________________
   * |           |           |           |           |           |  DYN REC  |  DYN REC  |
   * |  LAMBDA   |           |           |           |           |     1     |     2     |
   * |___________|___________|___________|___________|___________|___________|___________|
   * |  DYN REC  |     |     |     |     |     |     |     |     |     |     |           |
   * |   STOP    | F1  | F2  | F3  | F4  | F5  |  [  |  7  |  8  |  9  |  *  |    DEL    |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   * |           |     |     |     |     |     |     |     |     |     |     |           |
   * |           | F6  | F7  | F8  | F9  | F10 |  ]  |  4  |  5  |  6  |  +  |     =     |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   * |           |     |     |     |     |     |     |     |     |     |     |           |
   * |     \     | F11 | F12 | F13 | F14 | F15 |  {  |  1  |  2  |  3  |  -  |     |     |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   *   |         |     |     |     |     |     |     |     |     |     |     |         |
   *   |         | F16 | F17 | F18 | F19 | F20 |  }  |  0  |  ,  |  .  |  /  |         |
   *   |_________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_________|
   *       |     |     |     |     |           |           |     |     |     |     |
   *       |     |     |     |     |           |           |     |     |     |     |
   *       |_____|_____|_____|_____|___________|___________|_____|_____|_____|_____|
   *
   */

  [1] = LAYOUT(
    LAMBDA,       _______,          _______,          _______,          _______,          DM_REC1,          DM_REC2,
    DM_RSTP,      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LBRC, KC_P7,   KC_P8,   KC_P9,   KC_ASTR, KC_DEL,
    _______,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_EQL,
    KC_BSLS,      KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_LCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, KC_PIPE,
    _______,      KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_RCBR, KC_P0,   KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______,      _______, _______, _______,          _______, _______,          _______, _______, _______, _______
  ),

  /* Mouse layer.
   *
   *  ___________________________________________________________________________________
   * |           |           |           |           |           |           |           |
   * |           |           |           |           |           |           |           |
   * |___________|___________|___________|___________|___________|___________|___________|
   * |           |     |     | MS  |     |     |     |     |     |     |     |           |
   * |           |     |     | UP  |     |     |     |     |     |     |     |           |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   * |           |     | MS  | MS  | MS  |     |     |     |     |     |     |           |
   * |           |     | LFT | DWN | RGT |     |     | MS1 | MS3 | MS2 |     |           |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   * |           |     |     |     |     |     |     |     |     |     |     |           |
   * |           |     |     |     |     |     |     |     |     |     |     |           |
   * |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
   *   |         |     |     |     |     |     |     |     |     |     |     |         |
   *   |         |QK_BOOT|     |     |     |     |     |     |     |     |     |         |
   *   |_________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_________|
   *       |     |     |     |     |           |           |     |     |     |     |
   *       |     |     |     |     |           |           |     |     |     | F(2)|
   *       |_____|_____|_____|_____|___________|___________|_____|_____|_____|_____|
   *
   */

  [2] = LAYOUT(
    _______, _______,          _______,          _______,          _______,          _______,          _______,
    _______, _______, _______, KC_MS_U, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, QK_BOOT,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______, _______,          _______, _______, _______, TG(2)
  )
};

// Simple macro ideas follow. Each of them is designed to give you a quick way to create pairs of
// delimiters and then position the cursor between them, much like Emacs' ParEdit does. This way,
// you can have some convenient coding "helpers" even when not using Emacs. It is also nice for
// LaTeX editing.
//
// Customize to your heart's content!
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case PAIR_PR:
      if (record->event.pressed) {
        SEND_STRING("()"SS_TAP(X_LEFT));
      }
      return false;

    case PAIR_BR:
      if (record->event.pressed) {
        SEND_STRING("[]"SS_TAP(X_LEFT));
      }
      return false;

    case PAIR_CB:
      if (record->event.pressed) {
        SEND_STRING("{}"SS_TAP(X_LEFT));
      }
      return false;

    // Probably something only Lisp users will appreciate...
    case LAMBDA:
      if (record->event.pressed) {
        SEND_STRING("(lambda ())"SS_TAP(X_LEFT)SS_TAP(X_LEFT));
      }
      return false;
  }

  return true;
}
