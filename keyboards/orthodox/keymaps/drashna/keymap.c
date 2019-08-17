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

// clang-format off
#define LAYOUT_orthodox_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                                                             K06,     K07,     K08,     K09,     K0A,     KC_BSPC, \
    KC_TAB,  K11,    K12,     K13,      K14,     K15,              OS_LALT, OS_LGUI,   OS_RALT, RAISE,            K16,     K17,     K18,     K19,     K1A,     KC_QUOT, \
    KC_MLSF, CTL_T(K21), K22, K23,      K24,     K25,     LOWER,   KC_SPACE,KC_BSPC,   KC_DEL,  KC_ENT,  RAISE,   K26,     K27,     K28,     K29, RCTL_T(K2A), KC_MRSF  \
  )
#define LAYOUT_orthodox_base_wrapper(...)       LAYOUT_orthodox_base(__VA_ARGS__)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_orthodox_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_COLEMAK] = LAYOUT_orthodox_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_DVORAK] = LAYOUT_orthodox_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),

  [_WORKMAN] = LAYOUT_orthodox_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_NORMAN] = LAYOUT_orthodox_base_wrapper(
    _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
    _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
    _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
  ),

  [_MALTRON] = LAYOUT_orthodox_base_wrapper(
    _________________MALTRON_L1________________, _________________MALTRON_R1________________,
    _________________MALTRON_L2________________, _________________MALTRON_R2________________,
    _________________MALTRON_L3________________, _________________MALTRON_R3________________
  ),

  [_EUCALYN] = LAYOUT_orthodox_base_wrapper(
    _________________EUCALYN_L1________________, _________________EUCALYN_R1________________,
    _________________EUCALYN_L2________________, _________________EUCALYN_R2________________,
    _________________EUCALYN_L3________________, _________________EUCALYN_R3________________
  ),

  [_CARPLAX] = LAYOUT_orthodox_base_wrapper(
    _____________CARPLAX_QFMLWY_L1_____________, _____________CARPLAX_QFMLWY_R1_____________,
    _____________CARPLAX_QFMLWY_L2_____________, _____________CARPLAX_QFMLWY_R2_____________,
    _____________CARPLAX_QFMLWY_L3_____________, _____________CARPLAX_QFMLWY_R3_____________
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
    VRSN,    _________________ADJUST_L2_________________,          _______, _______,         _______, KC_NUKE,          _________________ADJUST_R2_________________, EEP_RST,
    TG_MODS, _________________ADJUST_L3_________________, _______, _______, _______,         _______, _______, _______, _________________ADJUST_R3_________________, KC_MPLY
  )

};
// clang-format on

void matrix_init_keymap(void) {
#ifndef CONVERT_TO_PROTON_C
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#endif
}
