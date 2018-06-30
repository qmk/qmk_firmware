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
  KC_TAB,  _________________QWERTY_L2_________________,          ALT_APP, OS_LGUI,         KC_LALT, OS_RGUI,          _________________QWERTY_R2_________________, KC_QUOT,
  KC_MLSF, _________________QWERTY_L3_________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________QWERTY_R3_________________, KC_MRSF
),

[_COLEMAK] = LAYOUT_wrapper(\
  KC_ESC,  _________________COLEMAK_L1________________,                                                               _________________COLEMAK_R1________________, KC_BSPC,
  KC_TAB,  _________________COLEMAK_L2________________,          ALT_APP, OS_LGUI,         KC_LALT, OS_RGUI,          _________________COLEMAK_R2________________, KC_QUOT,
  KC_MLSF, _________________COLEMAK_L3________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________COLEMAK_R3________________, KC_MRSF
),

[_DVORAK] = LAYOUT_wrapper(\
  KC_ESC,  _________________DVORAK_L1_________________,                                                               _________________DVORAK_R1_________________, KC_BSPC,
  KC_TAB,  _________________DVORAK_L2_________________,          ALT_APP, OS_LGUI,         KC_LALT, OS_RGUI,          _________________DVORAK_R2_________________, KC_MINS,
  KC_MLSF, _________________DVORAK_L3_________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________DVORAK_R3_________________, KC_MRSF
),
[_WORKMAN] = LAYOUT_wrapper(\
  KC_ESC,  _________________WORKMAN_L1________________,                                                               _________________WORKMAN_R1________________, KC_BSPC,
  KC_TAB,  _________________WORKMAN_L2________________,          ALT_APP, OS_LGUI,         KC_LALT, OS_RGUI,          _________________WORKMAN_R2________________, KC_MINS,
  KC_MLSF, _________________WORKMAN_L3________________, LOWER,   KC_SPACE,KC_BSPC,         KC_DEL,  KC_ENT,  RAISE,   _________________WORKMAN_R3________________, KC_MRSF
),
[_MODS] = LAYOUT_wrapper(\
  _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,          _______, _______,         _______, _______,          _______, _______, _______, _______, _______, _______,
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LOWER] = LAYOUT_wrapper(\
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_F11,  _________________FUNC_LEFT_________________,           _______, _______,         _______, _______,          _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  KC_F12,  _________________FUNC_RIGHT________________,  _______, _______, _______,         _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
),

[_RAISE] = LAYOUT_wrapper(\
  KC_GRV,  ________________NUMBER_LEFT________________,                                                               ________________NUMBER_RIGHT_______________, KC_BSPC,
  _______, _______, _______, _______, _______, _______,          _______, _______,         _______, _______,          _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______
),

[_ADJUST] = LAYOUT_wrapper(\
  KC_MAKE, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,                                                               KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5, KC_RESET,
  VRSN,    _______, CK_TOGG, AU_ON,   AU_OFF,  AG_NORM,          _______, _______,         _______, KC_NUKE,          AG_SWAP, QWERTY,  COLEMAK, DVORAK,  WORKMAN, EPRM,
  TG(_MODS),RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, KC_RGB_T,_______, _______, _______,         _______, _______, _______, MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY
)


};


bool indicator_is_this_led_used(uint8_t index) {
  switch (index) {
#ifdef INDICATOR_LIGHTS
    case SHFT_LED1:
    case SHFT_LED2:
    case CTRL_LED1:
    case CTRL_LED2:
    case GUI_LED1:
    case GUI_LED2:
      return true;
      break;
#endif
    default:
    return false;
  }
}
