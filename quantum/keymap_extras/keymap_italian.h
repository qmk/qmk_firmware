/* Copyright 2015-2016 Matthias Schmidtt
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

#ifndef KEYMAP_ITALIAN
#define KEYMAP_ITALIAN

#include "keymap.h"

// normal characters
#define IT_A KC_A
#define IT_B KC_B
#define IT_C KC_C
#define IT_D KC_D
#define IT_E KC_E
#define IT_F KC_F
#define IT_G KC_G
#define IT_H KC_H
#define IT_I KC_I
#define IT_J KC_J
#define IT_K KC_K
#define IT_L KC_L
#define IT_M KC_M
#define IT_N KC_N
#define IT_O KC_O
#define IT_P KC_P
#define IT_Q KC_Q
#define IT_R KC_R
#define IT_S KC_S
#define IT_T KC_T
#define IT_U KC_U
#define IT_V KC_V
#define IT_W KC_W
#define IT_X KC_X
#define IT_Y KC_Y
#define IT_Z KC_Z

#define IT_0 KC_0
#define IT_1 KC_1
#define IT_2 KC_2
#define IT_3 KC_3
#define IT_4 KC_4
#define IT_5 KC_5
#define IT_6 KC_6
#define IT_7 KC_7
#define IT_8 KC_8
#define IT_9 KC_9

#define IT_DOT KC_DOT
#define IT_COMM KC_COMM

#define IT_EACC KC_LBRC  // è, é, [, {
#define IT_PLUS KC_RBRC  // +, *, ], }
#define IT_OACC KC_SCLN  // ò, ç, @,
#define IT_AACC KC_QUOT  // à, °, #,
#define IT_UACC KC_BSLS  // ù, §,  ,
#define IT_IACC KC_EQL   // ì, ^,  ,

#define IT_APOS KC_MINS  // ', ?,  ,

#define IT_BKSL KC_GRAVE  // backslash \, |

#define IT_ACUT  // accent acute ´ and grave `

#define IT_LESS KC_NUBS  // < and > and |
#define IT_MINS KC_SLSH  // - and _

// shifted characters
#define IT_PIPE LSFT(IT_BKSL)  // °
#define IT_EXLM LSFT(KC_1)     // !
#define IT_DQOT LSFT(KC_2)     // "
#define IT_STRL LSFT(KC_3)     // £
#define IT_DLR LSFT(KC_4)      // $
#define IT_PERC LSFT(KC_5)     // %
#define IT_AMPR LSFT(KC_6)     // &
#define IT_SLSH LSFT(KC_7)     // /
#define IT_LPRN LSFT(KC_8)     // (
#define IT_RPRN LSFT(KC_9)     // )
#define IT_EQL LSFT(KC_0)      // =
#define IT_QST LSFT(IT_APOS)   // ?
#define IT_CRC LSFT(IT_IACC)   // ^
#define IT_ASTR LSFT(IT_PLUS)  // *
#define IT_MORE LSFT(IT_LESS)  // >
#define IT_COLN LSFT(IT_DOT)   // :
#define IT_SCLN LSFT(IT_COMM)  // ;
#define IT_UNDS LSFT(IT_MINS)  // _

// Alt Gr-ed characters
#define IT_LCBR ALGR(KC_7)     // {
#define IT_LBRC ALGR(IT_EACC)  // [
#define IT_RBRC ALGR(IT_PLUS)  // ]
#define IT_RCBR ALGR(KC_0)     // }
#define IT_AT ALGR(IT_OACC)    // @
#define IT_EURO ALGR(KC_E)     // €
#define IT_PIPE LSFT(IT_BKSL)  // |
#define IT_SHRP ALGR(IT_AACC)  // #

#define IT_X_PLUS X_RBRACKET  // #

#endif
