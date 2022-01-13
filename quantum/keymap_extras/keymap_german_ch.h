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

#ifdef CH_H
// The ChibiOS ch.h file defines this...
#    undef CH_H
#endif

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ ^ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ ü │ ¨ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ö │ ä │ $ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
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
#define CH_UDIA KC_LBRC // ü
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
#define CH_ODIA KC_SCLN // ö
#define CH_ADIA KC_QUOT // ä
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
 * │ ° │ + │ " │ * │ ç │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ è │ ! │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ é │ à │ £ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
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
#define CH_EGRV S(CH_UDIA) // è
#define CH_EXLM S(CH_DIAE) // !
// Row 3
#define CH_EACU S(CH_ODIA) // é
#define CH_AGRV S(CH_ADIA) // à
#define CH_PND  S(CH_DLR)  // £
// Row 4
#define CH_RABK S(CH_LABK) // >
#define CH_SCLN S(CH_COMM) // ;
#define CH_COLN S(CH_DOT)  // :
#define CH_UNDS S(CH_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ¦ │ @ │ # │   │   │ ¬ │ | │ ¢ │   │   │ ´ │ ~ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │   │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ { │ } │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
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
#define CH_LBRC ALGR(CH_UDIA) // [
#define CH_RBRC ALGR(CH_DIAE) // ]
// Row 3
#define CH_LCBR ALGR(CH_ADIA) // {
#define CH_RCBR ALGR(CH_DLR)  // }
// Row 4
#define CH_BSLS ALGR(CH_LABK) // (backslash)
