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
#include "drashna.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define MG_NKRO MAGIC_TOGGLE_NKRO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = KEYMAP_wrapper(\
  KC_ESC,  _________________QWERTY_L1_________________,                                                               _________________QWERTY_R1_________________, KC_BSPC, \
  KC_TAB,  _________________QWERTY_L2_________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________QWERTY_R2_________________, KC_QUOT, \
  KC_MLSF, _________________QWERTY_L3_________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________QWERTY_R3_________________, KC_LGUI \
),

[_COLEMAK] = KEYMAP_wrapper(\
  KC_ESC,  _________________COLEMAK_L1________________,                                                               _________________COLEMAK_R1________________, KC_BSPC, \
  KC_TAB,  _________________COLEMAK_L2________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________COLEMAK_R2________________, KC_QUOT, \
  KC_MLSF, _________________COLEMAK_L3________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________COLEMAK_R3________________, KC_LGUI \
),

[_DVORAK] = KEYMAP_wrapper(\
  KC_ESC,  _________________DVORAK_L1_________________,                                                               _________________DVORAK_R1_________________, KC_BSPC, \
  KC_TAB,  _________________DVORAK_L2_________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________DVORAK_R2_________________, KC_MINS, \
  KC_MLSF, _________________DVORAK_L3_________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________DVORAK_R3_________________, KC_LGUI \
),
[_WORKMAN] = KEYMAP_wrapper(\
  KC_ESC,  _________________WORKMAN_L1________________,                                                               _________________WORKMAN_R1________________, KC_BSPC, \
  KC_TAB,  _________________WORKMAN_L2________________,          KC_UP,   KC_DOWN,         KC_LEFT, KC_RIGHT,         _________________WORKMAN_R2________________, KC_MINS, \
  KC_MLSF, _________________WORKMAN_L3________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________WORKMAN_R3________________, KC_LGUI \
),
[_MODS] = KEYMAP(\
  _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,          _______, _______,         _______, _______,          _______, _______, _______, _______, _______, _______, \
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_LOWER] = KEYMAP(\
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F11,  KC_F12,          _______, _______,          XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______,         _______, _______, _______, XXXXXXX, KC_PGUP, KC_COMM, KC_DOT,  KC_PGDN, _______ \
),

[_RAISE] = KEYMAP(\
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F11,  KC_F12,          _______, KC_RCTL,          XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______,         _______, _______, _______, XXXXXXX, KC_HOME, KC_COMM, KC_DOT,  KC_END,  _______ \
),

[_ADJUST] = KEYMAP(\
  KC_MAKE,KC_RESET, EPRM,    _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,  \
  RGB_SMOD,RGB_HUI, KC_FXCL, AUD_ON,  AUD_OFF, AG_NORM,          _______, _______,         _______, _______,          AG_SWAP, KC_QWERTY, KC_COLEMAK, KC_DVORAK, KC_WORKMAN, TG(_MODS), \
  KC_RGB_T,RGB_HUD, MU_ON,   MU_OFF,  MU_TOG,  MU_MOD,  _______, _______, _______,         _______, _______, _______, MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY  \
)


};

