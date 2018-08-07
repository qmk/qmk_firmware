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

#ifdef INDICATOR_LIGHTS
extern userspace_config_t userspace_config;

uint8_t last_mod;
uint8_t last_led;
uint8_t last_osm;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_wrapper(\
  KC_ESC,  _________________QWERTY_L1_________________,                                                               _________________QWERTY_R1_________________, KC_BSPC,
  KC_TAB,  _________________QWERTY_L2_________________,          ___________ORTHODOX_THUMP_TOP_____________,          _________________QWERTY_R2_________________, KC_QUOT,
  KC_MLSF, _________________QWERTY_L3_________________, ___________________ORTHODOX_THUMB_BOTTOM____________________, _________________QWERTY_R3_________________, KC_MRSF
),

[_COLEMAK] = LAYOUT_wrapper(\
  KC_ESC,  _________________COLEMAK_L1________________,                                                               _________________COLEMAK_R1________________, KC_BSPC,
  KC_TAB,  _________________COLEMAK_L2________________,          ___________ORTHODOX_THUMP_TOP_____________,          _________________COLEMAK_R2________________, KC_QUOT,
  KC_MLSF, _________________COLEMAK_L3________________, ___________________ORTHODOX_THUMB_BOTTOM____________________, _________________COLEMAK_R3________________, KC_MRSF
),

[_DVORAK] = LAYOUT_wrapper(\
  KC_ESC,  _________________DVORAK_L1_________________,                                                               _________________DVORAK_R1_________________, KC_BSPC,
  KC_TAB,  _________________DVORAK_L2_________________,          ___________ORTHODOX_THUMP_TOP_____________,          _________________DVORAK_R2_________________, KC_MINS,
  KC_MLSF, _________________DVORAK_L3_________________, ___________________ORTHODOX_THUMB_BOTTOM____________________, _________________DVORAK_R3_________________, KC_MRSF
),
[_WORKMAN] = LAYOUT_wrapper(\
  KC_ESC,  _________________WORKMAN_L1________________,                                                               _________________WORKMAN_R1________________, KC_BSPC,
  KC_TAB,  _________________WORKMAN_L2________________,          ___________ORTHODOX_THUMP_TOP_____________,          _________________WORKMAN_R2________________, KC_MINS,
  KC_MLSF, _________________WORKMAN_L3________________, ___________________ORTHODOX_THUMB_BOTTOM____________________, _________________WORKMAN_R3________________, KC_MRSF
),
[_MODS] = LAYOUT_wrapper(\
  _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,          _______, _______,         _______, _______,          _______, _______, _______, _______, _______, _______,
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LOWER] = LAYOUT_wrapper(\
  KC_TILD, _________________LOWER_L1__________________,                                                               _________________LOWER_R1__________________, KC_BSPC,
  KC_F11,  _________________LOWER_L2__________________,          _______, _______,         _______, _______,          _________________LOWER_R2__________________, KC_PIPE,
  KC_F12,  _________________LOWER_L3__________________, _______, _______, _______,         _______, _______, _______, _________________LOWER_R3__________________, _______
),

[_RAISE] = LAYOUT_wrapper(\
  KC_GRV,  _________________RAISE_L1__________________,                                                               _________________RAISE_R1__________________, KC_BSPC,
  _______, _________________RAISE_L2__________________,          _______, _______,         _______, _______,          _________________RAISE_R2__________________, KC_BSLS,
  _______, _________________RAISE_L3__________________, _______, _______, _______,         _______, _______, _______, _________________RAISE_R3__________________, _______
),

[_ADJUST] = LAYOUT_wrapper(\
  KC_MAKE, _________________ADJUST_L1_________________,                                                               _________________ADJUST_R1_________________, KC_RESET,
  VRSN,    _________________ADJUST_L2_________________,          _______, _______,         _______, KC_NUKE,          _________________ADJUST_R2_________________, EPRM,
  TG_MODS, _________________ADJUST_L3_________________, _______, _______, _______,         _______, _______, _______, _________________ADJUST_R3_________________, KC_MPLY
)
};

void matrix_init_keymap(void) {
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
}
