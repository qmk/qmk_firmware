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

#include "orthodox.h"
#include "drashna.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = KEYMAP(\
  KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_UP, XXXXXXX,  KC_DOWN,        KC_LEFT, XXXXXXX, KC_RIGHT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,    CTL_T(KC_Z), KC_X, KC_C,   KC_V,    KC_B,      LOWER, KC_SPACE, KC_BSPC,        KC_DEL,  KC_ENT,  RAISE,    KC_N,    KC_M,    KC_COMM, KC_DOT, CTL_T(KC_SLASH), KC_LGUI \
),

[_COLEMAK] = KEYMAP(\
  KC_ESC,     KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                                                   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_TAB,     KC_A,    KC_R,    KC_S,    KC_T,    KC_D,      KC_UP, XXXXXXX,  KC_DOWN,        KC_LEFT, XXXXXXX, KC_RIGHT, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT,    CTL_T(KC_Z), KC_X, KC_C,   KC_V,    KC_B,      LOWER, KC_SPACE, KC_BSPC,        KC_DEL,  KC_ENT,  RAISE,    KC_K,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLASH), KC_LGUI \
),

[_DVORAK] = KEYMAP(\
    KC_ESC,   KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y,                                                                   KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
    KC_TAB,   KC_A,    KC_O,    KC_E,   KC_U,     KC_I,      KC_UP, XXXXXXX,  KC_DOWN,        KC_LEFT, XXXXXXX, KC_RIGHT, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
    KC_LSFT, CTL_T(KC_SCLN), KC_Q, KC_J, KC_K,    KC_X,      LOWER, KC_SPACE, KC_BSPC,        KC_DEL,  KC_ENT,  RAISE,    KC_B,    KC_M,    KC_W,    KC_V,    CTL_T(KC_Z), KC_LGUI \
),
[_WORKMAN] = KEYMAP(\
    KC_ESC,   KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y,                                                                   KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
    KC_TAB,   KC_A,    KC_O,    KC_E,   KC_U,     KC_I,      KC_UP, XXXXXXX,  KC_DOWN,        KC_LEFT, XXXXXXX, KC_RIGHT, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
    KC_LSFT, CTL_T(KC_SCLN), KC_Q, KC_J, KC_K,    KC_X,      LOWER, KC_SPACE, KC_BSPC,        KC_DEL,  KC_ENT,  RAISE,    KC_B,    KC_M,    KC_W,    KC_V,    CTL_T(KC_Z), KC_LGUI \
),

[_LOWER] = KEYMAP(\
  KC_TILD,    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                                KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,   XXXXXXX, KC_F12,          _______, XXXXXXX, KC_RCTL, XXXXXXX, KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE, \
  _______,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______,          _______, _______, _______, XXXXXXX, KC_HOME,    KC_COMM,    KC_DOT,  KC_END,  _______ \
),

[_RAISE] = KEYMAP(\
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                                   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  XXXXXXX, KC_F12,           _______, XXXXXXX, _______, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______,          _______, _______, _______, XXXXXXX, KC_PGUP, KC_COMM, KC_DOT,  KC_PGDN, _______ \
),

[_ADJUST] = KEYMAP(\
  KC_MAKE,KC_RESET, _______, _______, _______, _______,                                                                _______, _______, _______, _______, _______, _______,  \
  RGB_SMOD,RGB_HUI, _______, AU_ON,   AU_OFF,  AG_NORM, _______, XXXXXXX, _______,          _______, XXXXXXX, _______, AG_SWAP, KC_QWERTY, KC_COLEMAK, KC_DVORAK, KC_WORKMAN, _______, \
  KC_RGB_T,RGB_HUD, MU_ON,   MU_OFF,  MU_TOG,  MU_MOD,  _______, _______, _______,          _______, _______, _______, MAGIC_TOGGLE_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY  \
)


};

#ifdef FAUXCLICKY_ENABLE
float fauxclicky_pressed_note[2] = MUSICAL_NOTE(_A6, 2);  // (_D4, 0.25);
float fauxclicky_released_note[2] = MUSICAL_NOTE(_A6, 2); // (_C4, 0.125);
float fauxclicky_beep_note[2] = MUSICAL_NOTE(_C6, 2);       // (_C4, 0.25);
#endif 
