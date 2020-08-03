/* Copyright 2016 Vincent Pochet
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

#include "keymap.h"

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ ^ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ è │ ¨ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ é │ à │ $ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CH_SECT KC_GRV  // §
#define CH_1    KC_1    // 1
#define CH_2    KC_2    // 2
#define CH_3    KC_3    // 3
#define CH_4    KC_4    // 4
#define CH_5    KC_5    // 5
#define CH_6    KC_6    // 6
#define CH_7    KC_7    // 7
#define CH_8    KC_8    // 8
#define CH_9    KC_9    // 9
#define CH_0    KC_0    // 0
#define CH_QUOT KC_MINS // '
#define CH_CIRC KC_EQL  // ^ (dead)
// Row 2
#define CH_Q    KC_Q    // Q
#define CH_W    KC_W    // W
#define CH_E    KC_E    // E
#define CH_R    KC_R    // R
#define CH_T    KC_T    // T
#define CH_Z    KC_Y    // Z
#define CH_U    KC_U    // U
#define CH_I    KC_I    // I
#define CH_O    KC_O    // O
#define CH_P    KC_P    // P
#define CH_EGRV KC_LBRC // è
#define CH_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define CH_A    KC_A    // A
#define CH_S    KC_S    // S
#define CH_D    KC_D    // D
#define CH_F    KC_F    // F
#define CH_G    KC_G    // G
#define CH_H    KC_H    // H
#define CH_J    KC_J    // J
#define CH_K    KC_K    // K
#define CH_L    KC_L    // L
#define CH_EACU KC_SCLN // é
#define CH_AGRV KC_QUOT // à
#define CH_DLR  KC_NUHS // $
// Row 4
#define CH_LABK KC_NUBS // <
#define CH_Y    KC_Z    // Y
#define CH_X    KC_X    // X
#define CH_C    KC_C    // C
#define CH_V    KC_V    // V
#define CH_B    KC_B    // B
#define CH_N    KC_N    // N
#define CH_M    KC_M    // M
#define CH_COMM KC_COMM // ,
#define CH_DOT  KC_DOT  // .
#define CH_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │ + │ " │ * │ ç │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ü │ ! │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ ö │ ä │ £ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CH_DEG  S(CH_SECT) // °
#define CH_PLUS S(CH_1)    // +
#define CH_DQUO S(CH_2)    // "
#define CH_ASTR S(CH_3)    // *
#define CH_CCED S(CH_4)    // ç
#define CH_PERC S(CH_5)    // %
#define CH_AMPR S(CH_6)    // &
#define CH_SLSH S(CH_7)    // /
#define CH_LPRN S(CH_8)    // (
#define CH_RPRN S(CH_9)    // )
#define CH_EQL  S(CH_0)    // =
#define CH_QUES S(CH_QUOT) // ?
#define CH_GRV  S(CH_CIRC) // ` (dead)
// Row 2
#define CH_UDIA S(CH_EGRV) // ü
#define CH_EXLM S(CH_DIAE) // !
// Row 3
#define CH_ODIA S(CH_EACU) // ö
#define CH_ADIA S(CH_AGRV) // ä
#define CH_PND  S(CH_DLR)  // £
// Row 4
#define CH_RABK S(CH_LABK) // >
#define CH_SCLN S(CH_COMM) // ;
#define CH_COLN S(CH_DOT)  // :
#define CH_UNDS S(CH_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ¦ │ @ │ # │   │   │ ¬ │ | │ ¢ │   │   │ ´ │ ~ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │   │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ { │ } │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CH_BRKP ALGR(CH_1)    // ¦
#define CH_AT   ALGR(CH_2)    // @
#define CH_HASH ALGR(CH_3)    // #
#define CH_NOT  ALGR(CH_6)    // ¬
#define CH_PIPE ALGR(CH_7)    // |
#define CH_CENT ALGR(CH_8)    // ¢
#define CH_ACUT ALGR(CH_QUOT) // ´ (dead)
#define CH_TILD ALGR(CH_CIRC) // ~ (dead)
// Row 2
#define CH_EURO ALGR(CH_E)    // €
#define CH_LBRC ALGR(CH_EGRV) // [
#define CH_RBRC ALGR(CH_DIAE) // ]
// Row 3
#define CH_LCBR ALGR(CH_AGRV) // {
#define CH_RCBR ALGR(CH_DLR)  // }
// Row 4
#define CH_BSLS ALGR(CH_LABK) // (backslash)

// DEPRECATED
#define FR_CH_Z    CH_Z
#define FR_CH_Y    CH_Y
#define FR_CH_A    CH_A
#define FR_CH_B    CH_B
#define FR_CH_C    CH_C
#define FR_CH_D    CH_D
#define FR_CH_E    CH_E
#define FR_CH_F    CH_F
#define FR_CH_G    CH_G
#define FR_CH_H    CH_H
#define FR_CH_I    CH_I
#define FR_CH_J    CH_J
#define FR_CH_K    CH_K
#define FR_CH_L    CH_L
#define FR_CH_M    CH_M
#define FR_CH_N    CH_N
#define FR_CH_O    CH_O
#define FR_CH_P    CH_P
#define FR_CH_Q    CH_Q
#define FR_CH_R    CH_R
#define FR_CH_S    CH_S
#define FR_CH_T    CH_T
#define FR_CH_U    CH_U
#define FR_CH_V    CH_V
#define FR_CH_W    CH_W
#define FR_CH_X    CH_X
#define FR_CH_0    CH_0
#define FR_CH_1    CH_1
#define FR_CH_2    CH_2
#define FR_CH_3    CH_3
#define FR_CH_4    CH_4
#define FR_CH_5    CH_5
#define FR_CH_6    CH_6
#define FR_CH_7    CH_7
#define FR_CH_8    CH_8
#define FR_CH_9    CH_9
#define FR_CH_DOT  CH_DOT
#define FR_CH_COMM CH_COMM
#define FR_CH_QUOT CH_QUOT
#define FR_CH_AE   CH_AGRV
#define FR_CH_UE   CH_EGRV
#define FR_CH_OE   CH_EACU
#define FR_CH_CIRC CH_CIRC
#define FR_CH_LESS CH_LABK
#define FR_CH_MINS CH_MINS
#define FR_CH_DLR  CH_DLR
#define FR_CH_PARA CH_SECT
#define FR_CH_DIAE CH_DIAE
#define FR_CH_RING CH_DEG
#define FR_CH_EXLM CH_EXLM
#define FR_CH_PLUS CH_PLUS
#define FR_CH_DQOT CH_DQUO
#define FR_CH_ASTR CH_ASTR
#define FR_CH_PERC CH_PERC
#define FR_CH_AMPR CH_AMPR
#define FR_CH_SLSH CH_SLSH
#define FR_CH_LPRN CH_LPRN
#define FR_CH_RPRN CH_RPRN
#define FR_CH_EQL  CH_EQL
#define FR_CH_QST  CH_QUES
#define FR_CH_MORE CH_RABK
#define FR_CH_COLN CH_COLN
#define FR_CH_SCLN CH_SCLN
#define FR_CH_UNDS CH_UNDS
#define FR_CH_CCED CH_CCED
#define FR_CH_GRV  CH_GRV
#define FR_CH_LCBR CH_LCBR
#define FR_CH_LBRC CH_LBRC
#define FR_CH_RBRC CH_RBRC
#define FR_CH_RCBR CH_RCBR
#define FR_CH_BSLS CH_BSLS
#define FR_CH_AT   CH_AT
#define FR_CH_EURO CH_EURO
#define FR_CH_TILD CH_TILD
#define FR_CH_PIPE CH_PIPE
#define FR_CH_HASH CH_HASH
#define FR_CH_ACUT CH_ACUT
