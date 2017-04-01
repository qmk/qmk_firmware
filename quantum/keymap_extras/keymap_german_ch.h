/* Copyright 2016 heartsekai
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
#ifndef KEYMAP_SWISS_GERMAN
#define KEYMAP_SWISS_GERMAN

#include "keymap.h"

// Alt gr
#define ALGR(kc) RALT(kc)
#define CH_ALGR KC_RALT

// normal characters
#define CH_Z KC_Y
#define CH_Y KC_Z

#define CH_A KC_A
#define CH_B KC_B
#define CH_C KC_C
#define CH_D KC_D
#define CH_E KC_E
#define CH_F KC_F
#define CH_G KC_G
#define CH_H KC_H
#define CH_I KC_I
#define CH_J KC_J
#define CH_K KC_K
#define CH_L KC_L
#define CH_M KC_M
#define CH_N KC_N
#define CH_O KC_O
#define CH_P KC_P
#define CH_Q KC_Q
#define CH_R KC_R
#define CH_S KC_S
#define CH_T KC_T
#define CH_U KC_U
#define CH_V KC_V
#define CH_W KC_W
#define CH_X KC_X

#define CH_0 KC_0
#define CH_1 KC_1
#define CH_2 KC_2
#define CH_3 KC_3
#define CH_4 KC_4
#define CH_5 KC_5
#define CH_6 KC_6
#define CH_7 KC_7
#define CH_8 KC_8
#define CH_9 KC_9

#define CH_DOT KC_DOT
#define CH_COMM KC_COMM

#define CH_QUOT KC_MINS // ' ? ´
#define CH_AE KC_QUOT
#define CH_UE KC_LBRC
#define CH_OE KC_SCLN

#define CH_PARA KC_GRAVE // secction sign § and °
#define CH_CARR KC_EQL // carret ^ ` ~
#define CH_DIER KC_RBRC // dieresis ¨ ! ]
#define CH_DLR KC_BSLS // $ £ }
#define CH_LESS KC_NUBS // < and > and backslash
#define CH_MINS KC_SLSH // - and _

// shifted characters
#define CH_RING LSFT(CH_PARA) // °
#define CH_PLUS LSFT(KC_1) // +
#define CH_DQOT LSFT(KC_2) // "
#define CH_PAST LSFT(KC_3) // *
#define CH_CELA  LSFT(KC_4) // ç
#define CH_PERC LSFT(KC_5) // %
#define CH_AMPR LSFT(KC_6) // &
#define CH_SLSH LSFT(KC_7) // /
#define CH_LPRN LSFT(KC_8) // (
#define CH_RPRN LSFT(KC_9) // )
#define CH_EQL  LSFT(KC_0) // =
#define CH_QST  LSFT(CH_QUOT) // ?
#define CH_GRV  LSFT(CH_CARR) // `
#define CH_EXLM LSFT(CH_DIER) // !
#define CH_POND LSFT(CH_DLR) // £
#define CH_MORE LSFT(CH_LESS) // >
#define CH_COLN LSFT(KC_DOT) // :
#define CH_SCLN LSFT(KC_COMM) // ;
#define CH_UNDS LSFT(CH_MINS) // _

// Alt Gr-ed characters
#define CH_BRBR ALGR(KC_1) // ¦ brocken bar
#define CH_AT ALGR(KC_2) // @
#define CH_HASH ALGR(KC_3) // #
#define CH_NOTL ALGR(KC_6) // ¬ negative logic
#define CH_PIPE ALGR(KC_7) // |
#define CH_CENT ALGR(KC_8) // ¢ cent
#define CH_ACUT ALGR(CH_QUOT) // ´
#define CH_TILD ALGR(CH_CARR) // ~
#define CH_EURO ALGR(KC_E) // €
#define CH_LBRC ALGR(CH_UE) // [
#define CH_RBRC ALGR(CH_DIER) // ]
#define CH_LCBR ALGR(CH_AE) // {
#define CH_RCBR ALGR(CH_DLR) // }
#define CH_BSLS ALGR(CH_LESS) // backslash

#endif
