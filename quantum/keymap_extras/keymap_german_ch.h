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

#pragma once

#include "keymap.h"

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ ^ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ ü │ ¨ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ö │ ä │ $ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DE_SECT KC_GRV  // §
#define DE_1    KC_1    // 1
#define DE_2    KC_2    // 2
#define DE_3    KC_3    // 3
#define DE_4    KC_4    // 4
#define DE_5    KC_5    // 5
#define DE_6    KC_6    // 6
#define DE_7    KC_7    // 7
#define DE_8    KC_8    // 8
#define DE_9    KC_9    // 9
#define DE_0    KC_0    // 0
#define DE_QUOT KC_MINS // '
#define DE_CIRC KC_EQL  // ^ (dead)
// Row 2
#define DE_Q    KC_Q    // Q
#define DE_W    KC_W    // W
#define DE_E    KC_E    // E
#define DE_R    KC_R    // R
#define DE_T    KC_T    // T
#define DE_Z    KC_Y    // Z
#define DE_U    KC_U    // U
#define DE_I    KC_I    // I
#define DE_O    KC_O    // O
#define DE_P    KC_P    // P
#define DE_UDIA KC_LBRC // ü
#define DE_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define DE_A    KC_A    // A
#define DE_S    KC_S    // S
#define DE_D    KC_D    // D
#define DE_F    KC_F    // F
#define DE_G    KC_G    // G
#define DE_H    KC_H    // H
#define DE_J    KC_J    // J
#define DE_K    KC_K    // K
#define DE_L    KC_L    // L
#define DE_ODIA KC_SCLN // ö
#define DE_ADIA KC_QUOT // ä
#define DE_DLR  KC_NUHS // $
// Row 4
#define DE_LABK KC_NUBS // <
#define DE_Y    KC_Z    // Y
#define DE_X    KC_X    // X
#define DE_C    KC_C    // C
#define DE_V    KC_V    // V
#define DE_B    KC_B    // B
#define DE_N    KC_N    // N
#define DE_M    KC_M    // M
#define DE_COMM KC_COMM // ,
#define DE_DOT  KC_DOT  // .
#define DE_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │ + │ " │ * │ ç │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ è │ ! │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ é │ à │ £ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DE_DEG  S(DE_SECT) // °
#define DE_PLUS S(DE_1)    // +
#define DE_DQUO S(DE_2)    // "
#define DE_ASTR S(DE_3)    // *
#define DE_CCED S(DE_4)    // ç
#define DE_PERC S(DE_5)    // %
#define DE_AMPR S(DE_6)    // &
#define DE_SLSH S(DE_7)    // /
#define DE_LPRN S(DE_8)    // (
#define DE_RPRN S(DE_9)    // )
#define DE_EQL  S(DE_0)    // =
#define DE_QUES S(DE_QUOT) // ?
#define DE_GRV  S(DE_CIRC) // ` (dead)
// Row 2
#define DE_EGRV S(DE_UDIA) // è
#define DE_EXLM S(DE_DIAE) // !
// Row 3
#define DE_EACU S(DE_ODIA) // é
#define DE_AGRV S(DE_ADIA) // à
#define DE_PND  S(DE_DLR)  // £
// Row 4
#define DE_RABK S(DE_LABK) // >
#define DE_SCLN S(DE_COMM) // ;
#define DE_COLN S(DE_DOT)  // :
#define DE_UNDS S(DE_MINS) // _

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
#define DE_BRKP ALGR(DE_1)    // ¦
#define DE_AT   ALGR(DE_2)    // @
#define DE_HASH ALGR(DE_3)    // #
#define DE_NOT  ALGR(DE_6)    // ¬
#define DE_PIPE ALGR(DE_7)    // |
#define DE_CENT ALGR(DE_8)    // ¢
#define DE_ACUT ALGR(DE_QUOT) // ´ (dead)
#define DE_TILD ALGR(DE_CIRC) // ~ (dead)
// Row 2
#define DE_EURO ALGR(DE_E)    // €
#define DE_LBRC ALGR(DE_UDIA) // [
#define DE_RBRC ALGR(DE_DIAE) // ]
// Row 3
#define DE_LCBR ALGR(DE_ADIA) // {
#define DE_RCBR ALGR(DE_DLR)  // }
// Row 4
#define DE_BSLS ALGR(DE_LABK) // (backslash)

// DEPRECATED
#ifdef CH_H
// The ChibiOS ch.h file defines this...
#    undef CH_H
#endif
#define CH_Z    DE_Y
#define CH_Y    DE_Z
#define CH_A    DE_A
#define CH_B    DE_B
#define CH_C    DE_C
#define CH_D    DE_D
#define CH_E    DE_E
#define CH_F    DE_F
#define CH_G    DE_G
#define CH_H    DE_H
#define CH_I    DE_I
#define CH_J    DE_J
#define CH_K    DE_K
#define CH_L    DE_L
#define CH_M    DE_M
#define CH_N    DE_N
#define CH_O    DE_O
#define CH_P    DE_P
#define CH_Q    DE_Q
#define CH_R    DE_R
#define CH_S    DE_S
#define CH_T    DE_T
#define CH_U    DE_U
#define CH_V    DE_V
#define CH_W    DE_W
#define CH_X    DE_X
#define CH_0    DE_0
#define CH_1    DE_1
#define CH_2    DE_2
#define CH_3    DE_3
#define CH_4    DE_4
#define CH_5    DE_5
#define CH_6    DE_6
#define CH_7    DE_7
#define CH_8    DE_8
#define CH_9    DE_9
#define CH_DOT  DE_DOT
#define CH_COMM DE_COMM
#define CH_QUOT DE_QUOT
#define CH_AE   DE_ADIA
#define CH_UE   DE_UDIA
#define CH_OE   DE_ODIA
#define CH_PARA DE_SECT
#define CH_CARR DE_CIRC
#define CH_DIER DE_DIAE
#define CH_DLR  DE_DLR
#define CH_LESS DE_LABK
#define CH_MINS DE_MINS
#define CH_RING DE_DEG
#define CH_PLUS DE_PLUS
#define CH_DQOT DE_DQUO
#define CH_PAST DE_ASTR
#define CH_CELA DE_CCED
#define CH_PERC DE_PERC
#define CH_AMPR DE_AMPR
#define CH_SLSH DE_SLSH
#define CH_LPRN DE_LPRN
#define CH_RPRN DE_RPRN
#define CH_EQL  DE_EQL
#define CH_QST  DE_QUES
#define CH_GRV  DE_GRV
#define CH_EXLM DE_EXLM
#define CH_POND DE_PND
#define CH_MORE DE_RABK
#define CH_COLN DE_COLN
#define CH_SCLN DE_SCLN
#define CH_UNDS DE_UNDS
#define CH_BRBR DE_BRKP
#define CH_AT   DE_AT
#define CH_HASH DE_HASH
#define CH_NOTL DE_NOT
#define CH_PIPE DE_PIPE
#define CH_CENT DE_CENT
#define CH_ACUT DE_ACUT
#define CH_TILD DE_TILD
#define CH_EURO DE_EURO
#define CH_LBRC DE_LBRC
#define CH_RBRC DE_RBRC
#define CH_LCBR DE_LCBR
#define CH_RCBR DE_RCBR
#define CH_BSLS DE_BSLS
