/* Copyright 2016 Stephen Bösebeck
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
#ifndef KEYMAP_GERMAN_OSX
#define KEYMAP_GERMAN_OSX

#include "keymap.h"

// Alt gr

// normal characters
#define DE_OSX_Z KC_Y
#define DE_OSX_Y KC_Z

#define DE_OSX_A KC_A
#define DE_OSX_B KC_B
#define DE_OSX_C KC_C
#define DE_OSX_D KC_D
#define DE_OSX_E KC_E
#define DE_OSX_F KC_F
#define DE_OSX_G KC_G
#define DE_OSX_H KC_H
#define DE_OSX_I KC_I
#define DE_OSX_J KC_J
#define DE_OSX_K KC_K
#define DE_OSX_L KC_L
#define DE_OSX_M KC_M
#define DE_OSX_N KC_N
#define DE_OSX_O KC_O
#define DE_OSX_P KC_P
#define DE_OSX_Q KC_Q
#define DE_OSX_R KC_R
#define DE_OSX_S KC_S
#define DE_OSX_T KC_T
#define DE_OSX_U KC_U
#define DE_OSX_V KC_V
#define DE_OSX_W KC_W
#define DE_OSX_X KC_X

#define DE_OSX_0 KC_0
#define DE_OSX_1 KC_1
#define DE_OSX_2 KC_2
#define DE_OSX_3 KC_3
#define DE_OSX_4 KC_4
#define DE_OSX_5 KC_5
#define DE_OSX_6 KC_6
#define DE_OSX_7 KC_7
#define DE_OSX_8 KC_8
#define DE_OSX_9 KC_9

#define DE_OSX_DOT KC_DOT
#define DE_OSX_COMM KC_COMM

#define DE_OSX_SS KC_MINS
#define DE_OSX_AE KC_QUOT
#define DE_OSX_UE KC_LBRC
#define DE_OSX_OE KC_SCLN

#define DE_OSX_CIRC KC_NUBS  // accent circumflex ^ and ring °
#define DE_OSX_ACUT KC_EQL   // accent acute ´ and grave `
#define DE_OSX_PLUS KC_RBRC  // + and * and ~
#define DE_OSX_HASH KC_BSLS  // # and '
#define DE_OSX_LESS KC_GRV   // < and > and |
#define DE_OSX_MINS KC_SLSH  // - and _

// shifted characters
#define DE_OSX_RING LSFT(DE_OSX_CIRC)  // °
#define DE_OSX_EXLM LSFT(KC_1)         // !
#define DE_OSX_DQOT LSFT(KC_2)         // "
#define DE_OSX_PARA LSFT(KC_3)         // §
#define DE_OSX_DLR LSFT(KC_4)          // $
#define DE_OSX_PERC LSFT(KC_5)         // %
#define DE_OSX_AMPR LSFT(KC_6)         // &
#define DE_OSX_SLSH LSFT(KC_7)         // /
#define DE_OSX_LPRN LSFT(KC_8)         // (
#define DE_OSX_RPRN LSFT(KC_9)         // )
#define DE_OSX_EQL LSFT(KC_0)          // =
#define DE_OSX_QST LSFT(DE_OSX_SS)     // ?
#define DE_OSX_GRV LSFT(DE_OSX_ACUT)   // `
#define DE_OSX_ASTR LSFT(DE_OSX_PLUS)  // *
#define DE_OSX_QUOT LSFT(DE_OSX_HASH)  // '
#define DE_OSX_MORE LSFT(DE_OSX_LESS)  // >
#define DE_OSX_COLN LSFT(KC_DOT)       // :
#define DE_OSX_SCLN LSFT(KC_COMM)      // ;
#define DE_OSX_UNDS LSFT(DE_OSX_MINS)  // _

// Alt-ed characters
//#define DE_OSX_SQ2 LALT(KC_2) // ²
//#define DE_OSX_SQ3 LALT(KC_3) // ³
#define DE_OSX_LCBR LALT(KC_8)        // {
#define DE_OSX_LBRC LALT(KC_5)        // [
#define DE_OSX_RBRC LALT(KC_6)        // ]
#define DE_OSX_RCBR LALT(KC_9)        // }
#define DE_OSX_BSLS LALT(LSFT(KC_7))  // backslash
#define DE_OSX_AT LALT(DE_OSX_L)      // @
#define DE_OSX_EURO LALT(KC_E)        // €
#define DE_OSX_TILD LALT(DE_OSX_N)    // ~
#define DE_OSX_PIPE LALT(DE_OSX_7)    // |

#endif
