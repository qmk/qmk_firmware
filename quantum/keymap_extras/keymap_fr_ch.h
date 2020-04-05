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
#define FR_SECT KC_GRV  // §
#define FR_1    KC_1    // 1
#define FR_2    KC_2    // 2
#define FR_3    KC_3    // 3
#define FR_4    KC_4    // 4
#define FR_5    KC_5    // 5
#define FR_6    KC_6    // 6
#define FR_7    KC_7    // 7
#define FR_8    KC_8    // 8
#define FR_9    KC_9    // 9
#define FR_0    KC_0    // 0
#define FR_QUOT KC_MINS // '
#define FR_CIRC KC_EQL  // ^ (dead)
// Row 2
#define FR_Q    KC_Q    // Q
#define FR_W    KC_W    // W
#define FR_E    KC_E    // E
#define FR_R    KC_R    // R
#define FR_T    KC_T    // T
#define FR_Z    KC_Y    // Z
#define FR_U    KC_U    // U
#define FR_I    KC_I    // I
#define FR_O    KC_O    // O
#define FR_P    KC_P    // P
#define FR_EGRV KC_LBRC // è
#define FR_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define FR_A    KC_A    // A
#define FR_S    KC_S    // S
#define FR_D    KC_D    // D
#define FR_F    KC_F    // F
#define FR_G    KC_G    // G
#define FR_H    KC_H    // H
#define FR_J    KC_J    // J
#define FR_K    KC_K    // K
#define FR_L    KC_L    // L
#define FR_EACU KC_SCLN // é
#define FR_AGRV KC_QUOT // à
#define FR_DLR  KC_NUHS // $
// Row 4
#define FR_LABK KC_NUBS // <
#define FR_Y    KC_Z    // Y
#define FR_X    KC_X    // X
#define FR_C    KC_C    // C
#define FR_V    KC_V    // V
#define FR_B    KC_B    // B
#define FR_N    KC_N    // N
#define FR_M    KC_M    // M
#define FR_COMM KC_COMM // ,
#define FR_DOT  KC_DOT  // .
#define FR_MINS KC_SLSH // -

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
#define FR_DEG  S(FR_SECT) // °
#define FR_PLUS S(FR_1)    // +
#define FR_DQUO S(FR_2)    // "
#define FR_ASTR S(FR_3)    // *
#define FR_CCED S(FR_4)    // ç
#define FR_PERC S(FR_5)    // %
#define FR_AMPR S(FR_6)    // &
#define FR_SLSH S(FR_7)    // /
#define FR_LPRN S(FR_8)    // (
#define FR_RPRN S(FR_9)    // )
#define FR_EQL  S(FR_0)    // =
#define FR_QUES S(FR_QUOT) // ?
#define FR_GRV  S(FR_CIRC) // ` (dead)
// Row 2
#define FR_UDIA S(FR_EGRV) // ü
#define FR_EXLM S(FR_DIAE) // !
// Row 3
#define FR_ODIA S(FR_EACU) // ö
#define FR_ADIA S(FR_AGRV) // ä
#define FR_PND  S(FR_DLR)  // £
// Row 4
#define FR_RABK S(FR_LABK) // >
#define FR_SCLN S(FR_COMM) // ;
#define FR_COLN S(FR_DOT)  // :
#define FR_UNDS S(FR_MINS) // _

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
#define FR_BRKP ALGR(FR_1)    // ¦
#define FR_AT   ALGR(FR_2)    // @
#define FR_HASH ALGR(FR_3)    // #
#define FR_NOT  ALGR(FR_6)    // ¬
#define FR_PIPE ALGR(FR_7)    // |
#define FR_CENT ALGR(FR_8)    // ¢
#define FR_ACUT ALGR(FR_QUOT) // ´ (dead)
#define FR_TILD ALGR(FR_CIRC) // ~ (dead)
// Row 2
#define FR_EURO ALGR(FR_E)    // €
#define FR_LBRC ALGR(FR_EGRV) // [
#define FR_RBRC ALGR(FR_DIAE) // ]
// Row 3
#define FR_LCBR ALGR(FR_AGRV) // {
#define FR_RCBR ALGR(FR_DLR)  // }
// Row 4
#define FR_BSLS ALGR(FR_LABK) // (backslash)

// DEPRECATED
#define FR_CH_Z    FR_Z
#define FR_CH_Y    FR_Y
#define FR_CH_A    FR_A
#define FR_CH_B    FR_B
#define FR_CH_C    FR_C
#define FR_CH_D    FR_D
#define FR_CH_E    FR_E
#define FR_CH_F    FR_F
#define FR_CH_G    FR_G
#define FR_CH_H    FR_H
#define FR_CH_I    FR_I
#define FR_CH_J    FR_J
#define FR_CH_K    FR_K
#define FR_CH_L    FR_L
#define FR_CH_M    FR_M
#define FR_CH_N    FR_N
#define FR_CH_O    FR_O
#define FR_CH_P    FR_P
#define FR_CH_Q    FR_Q
#define FR_CH_R    FR_R
#define FR_CH_S    FR_S
#define FR_CH_T    FR_T
#define FR_CH_U    FR_U
#define FR_CH_V    FR_V
#define FR_CH_W    FR_W
#define FR_CH_X    FR_X
#define FR_CH_0    FR_0
#define FR_CH_1    FR_1
#define FR_CH_2    FR_2
#define FR_CH_3    FR_3
#define FR_CH_4    FR_4
#define FR_CH_5    FR_5
#define FR_CH_6    FR_6
#define FR_CH_7    FR_7
#define FR_CH_8    FR_8
#define FR_CH_9    FR_9
#define FR_CH_DOT  FR_DOT
#define FR_CH_COMM FR_COMM
#define FR_CH_QUOT FR_QUOT
#define FR_CH_AE   FR_AGRV
#define FR_CH_UE   FR_EGRV
#define FR_CH_OE   FR_EACU
#define FR_CH_CIRC FR_CIRC
#define FR_CH_LESS FR_LABK
#define FR_CH_MINS FR_MINS
#define FR_CH_DLR  FR_DLR
#define FR_CH_PARA FR_SECT
#define FR_CH_DIAE FR_DIAE
#define FR_CH_RING FR_DEG
#define FR_CH_EXLM FR_EXLM
#define FR_CH_PLUS FR_PLUS
#define FR_CH_DQOT FR_DQUO
#define FR_CH_ASTR FR_ASTR
#define FR_CH_PERC FR_PERC
#define FR_CH_AMPR FR_AMPR
#define FR_CH_SLSH FR_SLSH
#define FR_CH_LPRN FR_LPRN
#define FR_CH_RPRN FR_RPRN
#define FR_CH_EQL  FR_EQL
#define FR_CH_QST  FR_QUES
#define FR_CH_MORE FR_RABK
#define FR_CH_COLN FR_COLN
#define FR_CH_SCLN FR_SCLN
#define FR_CH_UNDS FR_UNDS
#define FR_CH_CCED FR_CCED
#define FR_CH_GRV  FR_GRV
#define FR_CH_LCBR FR_LCBR
#define FR_CH_LBRC FR_LBRC
#define FR_CH_RBRC FR_RBRC
#define FR_CH_RCBR FR_RCBR
#define FR_CH_BSLS FR_BSLS
#define FR_CH_AT   FR_AT
#define FR_CH_EURO FR_EURO
#define FR_CH_TILD FR_TILD
#define FR_CH_PIPE FR_PIPE
#define FR_CH_HASH FR_HASH
#define FR_CH_ACUT FR_ACUT
