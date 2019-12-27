/* Copyright 2018 fuge
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

#ifndef KEYMAP_HUNGARIAN
#define KEYMAP_HUNGARIAN

#include "keymap.h"

// basic letters
#define HU_Z KC_Y
#define HU_Y KC_Z

#define HU_A KC_A
#define HU_B KC_B
#define HU_C KC_C
#define HU_D KC_D
#define HU_E KC_E
#define HU_F KC_F
#define HU_G KC_G
#define HU_H KC_H
#define HU_I KC_I
#define HU_J KC_J
#define HU_K KC_K
#define HU_L KC_L
#define HU_M KC_M
#define HU_N KC_N
#define HU_O KC_O
#define HU_P KC_P
#define HU_Q KC_Q
#define HU_R KC_R
#define HU_S KC_S
#define HU_T KC_T
#define HU_U KC_U
#define HU_V KC_V
#define HU_W KC_W
#define HU_X KC_X

// num row
#define HU_0 KC_GRV
#define HU_1 KC_1
#define HU_2 KC_2
#define HU_3 KC_3
#define HU_4 KC_4
#define HU_5 KC_5
#define HU_6 KC_6
#define HU_7 KC_7
#define HU_8 KC_8
#define HU_9 KC_9
#define HU_OE KC_0

#define HU_UE KC_MINS
#define HU_OO KC_EQL

// q row
#define HU_OEE KC_LBRC
#define HU_UU KC_RBRC

// a row
#define HU_EE KC_SCLN
#define HU_AA KC_QUOT
#define HU_UEE KC_NUHS

#define HU_MINS KC_SLSH  // -

#define HU_DOT KC_DOT
#define HU_COMM KC_COMM

// shifted characters
// num row
#define HU_PARA LSFT(HU_0)  // §
#define HU_QUOT LSFT(HU_1)  // '
#define HU_DQOT LSFT(HU_2)  // "
#define HU_PLUS LSFT(HU_3)  // +
#define HU_EXLM LSFT(HU_4)  // !
#define HU_PERC LSFT(HU_5)  // %
#define HU_SLSH LSFT(HU_6)  // /
#define HU_EQL LSFT(HU_7)   // =
#define HU_LPRN LSFT(HU_8)  // (
#define HU_RPRN LSFT(HU_9)  // )

// í,y row
#define HU_II KC_NUBS
#define HU_QST LSFT(HU_COMM)   // ?
#define HU_COLN LSFT(HU_DOT)   // :
#define HU_UNDS LSFT(HU_MINS)  // _

// Alt Gr'd characters
// num row
#define HU_TILD ALGR(HU_1)  // ~
//#define HU_?? ALGR(HU_2) // ˇ (proper name?)
#define HU_CIRC ALGR(HU_3)  // ^
#define HU_BRV ALGR(HU_4)   // ˘
#define HU_RING ALGR(HU_5)  // °
//#define HU_?? ALGR(HU_6) // ˛ (proper name?)
#define HU_GRV ALGR(HU_7)  // `
//#define HU_?? ALGR(HU_8) // ˙ (proper name?)
#define HU_ACUT ALGR(HU_9)  // ´

// q row
#define HU_BSLS ALGR(HU_Q)   // \ backslash
#define HU_PIPE ALGR(HU_W)   // |
#define HU_DIV ALGR(HU_OEE)  // ÷
#define HU_CRSS ALGR(HU_UU)  // ×
#define HU_EURO ALGR(HU_U)   // €

// a row
#define HU_LBRC ALGR(HU_F)  // [
#define HU_RBRC ALGR(HU_G)  // ]
#define HU_DLR ALGR(HU_EE)  // $
#define HU_SS ALGR(HU_AA)   // ß

// í,y row
#define HU_LESS ALGR(KC_NUBS)  // <
#define HU_MORE ALGR(HU_Y)     // >
#define HU_HASH ALGR(HU_X)     // #
#define HU_AMPR ALGR(HU_C)     // &
#define HU_AT ALGR(HU_V)       // @
#define HU_LCBR ALGR(HU_B)     // {
#define HU_RCBR ALGR(HU_N)     // }
#define HU_SCLN ALGR(HU_COMM)  // ;
#define HU_ASTR ALGR(HU_MINS)  // *

#endif
