/* Copyright 2021 Mats Nilsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

// Layers
enum layers {
    _COLEMAK,
    _QWERTY,
    _SYMBOLS,
    _NAVIGATION,
    _NUMPAD,
};

// Custom Keycodes
#define _NAV_SPC LT(_NAVIGATION, KC_SPC)  // _NAVIGATION when held, SPACE when tapped
#define _SYM_ENT LT(_SYMBOLS, KC_ENT)     // _SYMBOLS when held, ENTER when tapped
#define CTL_BSPC MT(MOD_LCTL, KC_BSPC)    // CTRL when held, BACKSPACE when tapped
#define ALT_DEL MT(MOD_LALT, KC_DEL)      // ALT when held, DELETE when tapped
#define SFT_TAB MT(MOD_LSFT, KC_TAB)      // SHIFT when held, TAB when tapped
#define C_TAB C(KC_TAB)                   // CTRL+TAB
#define CS_TAB C(S(KC_TAB))               // SHIFT+CTRL+TAB
#define CUT C(KC_X)                       // CTRL+X
#define COPY C(KC_INS)                    // CTRL+INSERT
#define PASTE S(KC_INS)                   // SHIFT+INSERT
#define AUTOFILL C(S(KC_L))               // Bitwarden Autofill, CTRL+SHIFT+L

// i3 config
#define I3MOD KC_LGUI           // $mod
#define OPEN G(KC_SPC)          // $mod+SPACE
#define QUIT G(S(KC_Q))         // $mod+SHIFT+Q
#define WIN G(C(KC_SPC))        // $mod+CTRL+SPACE
#define BROWSER G(KC_ENTER)     // $mod+ENTER
#define TERM G(S(KC_ENTER))     // $mod+CTRL+ENTER
#define NXTWS G(KC_TAB)         // $mod+TAB
#define PRVWS G(S(KC_TAB))      // $mod+SHIFT+TAB
#define MOVWS G(KC_LSFT)        // $mod+SHIFT+$X
#define CRYWS G(KC_LALT)        // $mod+ALT+$X
#define MVWSL G(C(S(KC_LEFT)))  // $mod+CTRL+SHIFT+LEFT
#define MVWSR G(C(S(KC_RGHT)))  // $mod+CTRL+SHIFT+RIGHT

enum custom_keycodes {
    M_TILD = SAFE_RANGE,  // ~
    M_CIRC,               // ^
    M_BTCK,               // `
    QWE_COL,              // Swaps default layer
};

// Tap Dance
typedef struct {
    bool is_press_action;
    int  state;
} tap;

// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5,  // send two single taps
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7
};

enum {
    AAE = 0,  // a and ae
    OAA,      // o and aa
};
