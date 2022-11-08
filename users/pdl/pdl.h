/*
Copyright 2018-2021 Daniel Perrett

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

#pragma once

#include "quantum.h"

enum userspace_layer_codes {
    QWERTY = SAFE_RANGE,
    PROXIM,
    PUNCTN,
    CODING,
    KU_LBRC,
    KU_NUHS,
    KU_GRV,
    KU_RBRC,
    NEW_SAFE_RANGE
};

enum userspace_layers {
    _PROXIM,
    _QWERTY,
    _NUMBRS,
    _NAVIGN,
    _PUNCTN,
    _CODING,
    _FUNCTN
};

#define MY_FESC  LT(_FUNCTN,  KC_ESC)
#define MY_SSPC  MT(MOD_RSFT, KC_SPC)
#define MY_SESC  MT(MOD_LSFT, KC_ESC)
#define MY_SBSL  MT(MOD_LSFT, KC_NUBS)
#define MY_CBSL  MT(MOD_LCTL, KC_NUBS)
#define MY_SSCL  MT(MOD_RSFT, KC_SCLN)
#define MY_ASCL  MT(MOD_LALT, KC_SCLN)
#define MY_SQUO  MT(MOD_RSFT, KC_QUOT)
#define MY_CENT  MT(MOD_RCTL, KC_ENT)
#define MY_SENT  MT(MOD_RSFT, KC_ENT)
#define MY_AMNU  MT(MOD_RALT, KC_APP)

#define MY_TILD  S(KC_NUHS)
#define MY_SEQL  MT(MOD_RALT, KC_PEQL)
#define MY_CMIN  MT(MOD_RALT, KC_MINS)
#define MY_ASLS  MT(MOD_RALT, KC_SLSH)

#define MY_UNDO  LCTL(KC_Z)
#define MY_CUT   LCTL(KC_X)
#define MY_COPY  LCTL(KC_C)
#define MY_PASTE LCTL(KC_V)

#define MY_AF4  LALT(KC_F4)
#define MY_CF4  LCTL(KC_F4)
#define MY_CF5  LCTL(KC_F5)
#define MY_CAD  LCTL(LALT(KC_DEL))

#define NUMBRS TT(_NUMBRS)
#define NAVIGN TT(_NAVIGN)
#define FUNCTN TT(_FUNCTN)

#define EITHER_SHIFT (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))

// Cannot redefine this here
// #define TAPPING_TOGGLE 2

// Taken from drashna:
// Since our quirky block definitions are basically a list of comma separated
// arguments, we need a wrapper in order for these definitions to be
// expanded before being used as arguments to the LAYOUT_xxx macro.
#if !defined(LAYOUT)
#if defined(LAYOUT_ortho_4x12)
#define LAYOUT_wrapper_ortho_4x12(...) LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT LAYOUT_ortho_4x12
#elif defined(KEYMAP)
#define LAYOUT KEYMAP
#endif
#endif
#define KEYMAP_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define ___________________________________________  _______, _______, _______, _______, _______

#define _________________QWERTY_L1_________________  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________  KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________PROXIM_L1_________________  KC_Q,    KC_W,    KC_F,    KC_R,    KC_B
#define _________________PROXIM_L2_________________  KC_A,    KC_S,    KC_D,    KC_T,    KC_G
#define _________________PROXIM_L3_________________  KC_Z,    KC_X,    KC_C,    KC_V,    KC_K

#define _________________PROXIM_R1_________________  KC_J,    KC_Y,    KC_O,    KC_U,    KC_QUOT
#define _________________PROXIM_R2_________________  KC_P,    KC_N,    KC_E,    KC_I,    KC_L
#define _________________PROXIM_R3_________________  KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________PUNCTN_R1_________________  KC_NUBS, KC_NUHS, KC_LPRN, KC_RPRN, _______
#define _________________PUNCTN_R2_________________  KC_GRV,  KC_EQL,  KC_MINS, KC_PLUS, KC_SLSH
#define _________________PUNCTN_R3_________________  KC_LBRC, KC_RBRC, _______, _______, _______

#define _________________CODING_R1_________________  KU_GRV,  KC_PERC, KC_DLR,  KC_AT,   _______
#define _________________CODING_R2_________________  KC_CIRC, KC_UNDS, MY_TILD, KC_AMPR, KU_NUHS
#define _________________CODING_R3_________________  KU_LBRC, KU_RBRC, _______, _______, _______

#define _________________NAVIGN_L1_________________  KC_DEL,  KC_PGUP, KC_UP,   KC_PGDN,  KC_BSPC
#define _________________NAVIGN_L2_________________  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END
#define _________________NAVIGN_L3_________________  MY_UNDO, MY_CUT,  MY_COPY, MY_PASTE, KC_ENT

#define _________________NUMBRS_L1_________________  KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBRS_L2_________________  KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________NUMBRS_L3_________________  KC_UNDO, KC_MINS, KC_EQL,  KC_PDOT, KC_ENT

#define _________________FUNCTN_L1_________________  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   MY_AF4
#define _________________FUNCTN_L2_________________  KC_APP,  KC_F4,   KC_F5,   KC_F6,   MY_CF5
#define _________________FUNCTN_L3_________________  RESET,   KC_F7,   KC_F8,   KC_F9,   MY_CF4

#define _________________FUNCTN_R1_________________  KC_VOLU, KC_F10,  KC_F11,  KC_F12,  KC_INS
#define _________________FUNCTN_R2_________________  KC_VOLD, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT
#define _________________FUNCTN_R3_________________  KC_MUTE, KC_PAUS, QWERTY,  PROXIM,  DB_TOGG
