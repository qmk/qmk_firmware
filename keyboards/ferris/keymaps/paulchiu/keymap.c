/*
Copyright 2021 Paul Chiu

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
#include "g/keymap_combo.h"

enum ferris_layers {
  _QT,
  _NV,
  _SB,
  _NU
};

#define LSFT_Z  LSFT_T(KC_Z)
#define RSFT_SL RSFT_T(KC_SLSH)
#define NV_ESC  LT(_NV, KC_ESC)
#define NU_SPC  LT(_NU, KC_SPC)
#define SB_ENT  LT(_SB, KC_ENT)
#define OS_SFT  OSM(MOD_LSFT)
#define MAC_DW  LALT(KC_BSPC) // MacOS Delete word (backwards)
#define MAC_SP  LGUI(KC_SPC)  // MacOS Spotlight
#define MAC_NW  LALT(KC_RGHT) // MacOS Next word
#define MAC_PW  LALT(KC_LEFT) // MacOS Prev word
#define MAC_XW  LGUI(KC_GRV)  // MacOS Next window

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QT] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,  KC_K,    KC_L,   KC_QUOT,
    LSFT_Z,  KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,  KC_COMM, KC_DOT, RSFT_SL,
                                    NV_ESC, NU_SPC, KC_SPC, SB_ENT
  ),

  [_NV] = LAYOUT( /* Navigation */
     KC_TAB,  MAC_XW, KC_PGUP, C(KC_R), _______,         _______, KC_CAPS, _______,  KC_DEL, KC_BSPC,
     KC_ESC,  MAC_SP, KC_PGDN,  OS_SFT, _______,         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_ENT,
    KC_LCTL, KC_LOPT, KC_LGUI, KC_LSFT, C(KC_B),          MAC_PW,  MAC_NW, KC_RGUI, KC_ROPT, KC_RCTL,
                                    _______, _______, MAC_DW, KC_HYPR
  ),

  [_SB] = LAYOUT( /* Symbols */
    KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR,   KC_LT,   KC_GT,
     KC_GRV, KC_TILD, KC_LPRN, KC_RPRN, _______,         KC_PIPE, KC_MINS,  KC_EQL, KC_COLN, KC_SCLN,
    KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,         KC_BSLS, KC_UNDS, KC_PLUS, _______, _______,
                                    _______, _______, _______, _______
  ),

  [_NU] = LAYOUT( /* Numbers */
    _______,   KC_F7,   KC_F8,   KC_F9,  KC_F12,         KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS,
    _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11,         KC_ASTR,    KC_4,    KC_5,    KC_6, KC_PLUS,
    _______,   KC_F1,   KC_F2,   KC_F3,  KC_F10,         _______,    KC_1,    KC_2,    KC_3,  KC_DOT,
                                    _______, _______, _______, KC_0
  )
};
