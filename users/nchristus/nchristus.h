/*
Copyright 2020 Nick Christus <nick.christus@hey.com> @nchristus

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

#include QMK_KEYBOARD_H

// Define layer names
enum userspace_layers {
  _QWRTY = 0,
  _LOWER,
  _RAISE,
  _ARROW,
  _FNCTN,
  _ADJST
};

// CTRL / ESC
#define CTL_ESC CTL_T(KC_ESC)

// Force quit dialog
#define C_O_ESC LALT(LGUI(KC_ESC))

// Mac lock
#define MAC_LOK LCTL(LGUI(KC_Q))

// 1Password
#define OPW_OPN LALT(LGUI(KC_BSLS))
#define OPW_CPY S(LGUI(KC_C))

// Screenshotting
#define SCR_FLL S(LGUI(KC_3))
#define SCR_CRP S(LGUI(KC_4))

// FSNotes
#define FSNOTES LALT(LGUI(LSFT(LCTL(KC_0))))

#if (!defined(LAYOUT) && defined(KEYMAP))
  #define LAYOUT KEYMAP
#endif

#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)

#define ___________________BLANK___________________       _______, _______, _______, _______, _______

#define __________________QWERTYL1_________________       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define __________________QWERTYR1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P

#define __________________QWERTYL2_________________       KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define __________________QWERTYR2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN

#define __________________QWERTYL3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#define __________________QWERTYR3_________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________LOWER_L1__________________       ________________NUMBER_LEFT________________
#define _________________LOWER_L2__________________       KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS

#define _________________LOWER_R1__________________       ________________NUMBER_RIGHT_______________
#define _________________LOWER_R2__________________       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______

#define _________________RAISE_L1__________________       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________RAISE_L2__________________       ___________________BLANK___________________

#define _________________RAISE_R1__________________       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define _________________RAISE_R2__________________       KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE
