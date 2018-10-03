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

#ifndef KEYMAP_SLOVENIAN
#define KEYMAP_SLOVENIAN
#include "keymap.h"


//Swapped Z and Y
#define SI_Z KC_Y
#define SI_Y KC_Z

//Special characters
#define SI_CV KC_SCLN
#define SI_SV KC_LBRC
#define SI_ZV KC_BSLS

#define SI_A KC_A
#define SI_B KC_B
#define SI_C KC_C
#define SI_D KC_D
#define SI_E KC_E
#define SI_F KC_F
#define SI_G KC_G
#define SI_H KC_H
#define SI_I KC_I
#define SI_J KC_J
#define SI_K KC_K
#define SI_L KC_L
#define SI_M KC_M
#define SI_N KC_N
#define SI_O KC_O
#define SI_P KC_P
#define SI_Q KC_Q
#define SI_R KC_R
#define SI_S KC_S
#define SI_T KC_T
#define SI_U KC_U
#define SI_V KC_V
#define SI_W KC_W
#define SI_X KC_X

#define SI_0 KC_0
#define SI_1 KC_1
#define SI_2 KC_2
#define SI_3 KC_3
#define SI_4 KC_4
#define SI_5 KC_5
#define SI_6 KC_6
#define SI_7 KC_7
#define SI_8 KC_8
#define SI_9 KC_9

#define SI_DOT KC_DOT
#define SI_COMM KC_COMM

#define DE_CIRC KC_GRAVE // accent circumflex ^ and ring °
#define DE_ACUT KC_EQL // accent acute ´ and grave `
#define DE_PLUS KC_RBRC // + and * and ~
#define DE_HASH KC_BSLS // # and '
#define DE_LESS KC_NUBS // < and > and |
#define DE_MINS KC_SLSH // - and _

// shifted characters
#define DE_RING LSFT(DE_CIRC) // °
#define DE_EXLM LSFT(KC_1) // !
#define DE_DQOT LSFT(KC_2) // "
#define DE_PARA LSFT(KC_3) // §
#define DE_DLR  LSFT(KC_4) // $
#define DE_PERC LSFT(KC_5) // %
#define DE_AMPR LSFT(KC_6) // &
#define DE_SLSH LSFT(KC_7) // /
#define DE_LPRN LSFT(KC_8) // (
#define DE_RPRN LSFT(KC_9) // )
#define DE_EQL  LSFT(KC_0) // =
#define DE_QST  LSFT(DE_SS) // ?
#define DE_GRV  LSFT(DE_ACUT) // `
#define DE_ASTR LSFT(DE_PLUS) // *
#define DE_QUOT LSFT(DE_HASH) // '
#define DE_MORE LSFT(DE_LESS) // >
#define DE_COLN LSFT(KC_DOT) // :
#define DE_SCLN LSFT(KC_COMM) // ;
#define DE_UNDS LSFT(DE_MINS) // _

// Alt Gr-ed characters
#define DE_SQ2 ALGR(KC_2) // ²
#define DE_SQ3 ALGR(KC_3) // ³
#define DE_LCBR ALGR(KC_7) // {
#define DE_LBRC ALGR(KC_8) // [
#define DE_RBRC ALGR(KC_9) // ]
#define DE_RCBR ALGR(KC_0) // }
#define DE_BSLS ALGR(DE_SS) // backslash
#define DE_AT  ALGR(KC_Q) // @
#define DE_EURO ALGR(KC_E) // €
#define DE_TILD ALGR(DE_PLUS) // ~
#define DE_PIPE ALGR(DE_LESS) // |

#endif
