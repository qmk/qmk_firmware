/*
This is the keymap for the keyboard

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _NAV 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NAV,
  CC_ARRW,
  CC_PRN,
  CC_BRC,
  CC_CBR,
};

#define NAV_TAP LT(_NAV, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          TT(_RAISE), TT(_LOWER),     TT(_LOWER), TT(_RAISE),      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
    KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BSPC, KC_LSFT, KC_LCTL,         KC_LALT, KC_LGUI, NAV_TAP,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT \
  ),

  [_LOWER] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                                  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
    KC_INS,  _______, _______, CC_PRN,  CC_BRC,  CC_CBR,           _______, _______,          _______, _______,          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
    QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU \
  ),

  [_RAISE] = LAYOUT( \
    KC_CAPS, KC_AMPR, KC_ASTR, KC_UNDS, KC_LPRN, KC_RPRN,                                                                KC_7,    KC_8,    KC_9,    KC_EQL,  _______, _______, \
    _______, KC_DLR,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC,          _______, _______,          _______, _______,          KC_4,    KC_5,    KC_6,    KC_MINS, KC_PLUS, _______, \
    CC_ARRW, KC_EXLM, KC_AT,   KC_HASH, KC_LCBR, KC_RCBR, _______, _______, _______,          _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  KC_BSLS, KC_PIPE \
  ),

  [_NAV] =  LAYOUT( \
    _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,                                                                _______, _______, _______, _______, _______, _______,  \
    _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT,          _______, _______,          _______, _______,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  )


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case CC_ARRW:
        SEND_STRING("->");
        return false;
      case CC_PRN:
        SEND_STRING("()"SS_TAP(X_LEFT));
        return false;
      case CC_BRC:
        SEND_STRING("[]"SS_TAP(X_LEFT));
        return false;
      case CC_CBR:
        SEND_STRING("{}"SS_TAP(X_LEFT));
        return false;
    }
  }
  return true;
}
