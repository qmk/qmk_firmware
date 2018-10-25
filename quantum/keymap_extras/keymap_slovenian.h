/* Copyright 2018 Žan Pevec

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

#define SI_PLUS KC_EQL // + and * and ~
#define SI_QOT KC_MINS // Single quote
#define SI_MINS KC_SLSH // - and _

// shifted characters
#define SI_EXLM LSFT(KC_1) // !
#define SI_DQOT LSFT(KC_2) // "
#define SI_HASH LSFT(KC_3) // #
#define SI_DLR  LSFT(KC_4) // $
#define SI_PERC LSFT(KC_5) // %
#define SI_AMPR LSFT(KC_6) // &
#define SI_SLSH LSFT(KC_7) // /
#define SI_LPRN LSFT(KC_8) // (
#define SI_RPRN LSFT(KC_9) // )
#define SI_EQL  LSFT(KC_0) // =
#define SI_QST  LSFT(SI_QOT) // ?
#define SI_ASTR LSFT(SI_PLUS) // *
#define SI_COLN LSFT(KC_DOT) // :
#define SI_SCLN LSFT(KC_COMM) // ;
#define SI_UNDS LSFT(SI_MINS) // _

// Alt Gr-ed characters
#define SI_CIRC ALTG(KC_3) // ^
#define SI_DEG ALTG(KC_5) // °
#define SI_GRV ALTG(KC_7) // `
#define SI_ACCU ALTG(KC_9) // ´
#define SI_LCBR ALTG(KC_B) // {
#define SI_RCBR ALTG(KC_N) // }
#define SI_LBRC ALTG(KC_F) // [
#define SI_RBRC ALTG(KC_G) // ]
#define SI_BSLS ALTG(KC_Q) // backslash
#define SI_AT  ALTG(KC_V) // @
#define SI_EURO ALTG(KC_E) // €
#define SI_TILD ALTG(KC_1) // ~
#define SI_PIPE ALTG(KC_W) // |

#endif
