/* Copyright 2020
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
 * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IE_GRV  KC_GRV  // `
#define IE_1    KC_1    // 1
#define IE_2    KC_2    // 2
#define IE_3    KC_3    // 3
#define IE_4    KC_4    // 4
#define IE_5    KC_5    // 5
#define IE_6    KC_6    // 6
#define IE_7    KC_7    // 7
#define IE_8    KC_8    // 8
#define IE_9    KC_9    // 9
#define IE_0    KC_0    // 0
#define IE_MINS KC_MINS // -
#define IE_EQL  KC_EQL  // =
// Row 2
#define IE_Q    KC_Q    // Q
#define IE_W    KC_W    // W
#define IE_E    KC_E    // E
#define IE_R    KC_R    // R
#define IE_T    KC_T    // T
#define IE_Y    KC_Y    // Y
#define IE_U    KC_U    // U
#define IE_I    KC_I    // I
#define IE_O    KC_O    // O
#define IE_P    KC_P    // P
#define IE_LBRC KC_LBRC // [
#define IE_RBRC KC_RBRC // ]
// Row 3
#define IE_A    KC_A    // A
#define IE_S    KC_S    // S
#define IE_D    KC_D    // D
#define IE_F    KC_F    // F
#define IE_G    KC_G    // G
#define IE_H    KC_H    // H
#define IE_J    KC_J    // J
#define IE_K    KC_K    // K
#define IE_L    KC_L    // L
#define IE_SCLN KC_SCLN // ;
#define IE_QUOT KC_QUOT // '
#define IE_HASH KC_NUHS // #
// Row 4
#define IE_BSLS KC_NUBS // (backslash)
#define IE_Z    KC_Z    // Z
#define IE_X    KC_X    // X
#define IE_C    KC_C    // C
#define IE_V    KC_V    // V
#define IE_B    KC_B    // B
#define IE_N    KC_N    // N
#define IE_M    KC_M    // M
#define IE_COMM KC_COMM // ,
#define IE_DOT  KC_DOT  // .
#define IE_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¬ │ ! │ " │ £ │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ : │ @ │ ~ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IE_NOT  S(IE_GRV)  // ¬
#define IE_EXLM S(IE_1)    // !
#define IE_DQUO S(IE_2)    // "
#define IE_PND  S(IE_3)    // £
#define IE_DLR  S(IE_4)    // $
#define IE_PERC S(IE_5)    // %
#define IE_CIRC S(IE_6)    // ^
#define IE_AMPR S(IE_7)    // &
#define IE_ASTR S(IE_8)    // *
#define IE_LPRN S(IE_9)    // (
#define IE_RPRN S(IE_0)    // )
#define IE_UNDS S(IE_MINS) // _
#define IE_PLUS S(IE_EQL)  // +
// Row 2
#define IE_LCBR S(IE_LBRC) // {
#define IE_RCBR S(IE_RBRC) // }
// Row 3
#define IE_COLN S(IE_SCLN) // :
#define IE_AT   S(IE_QUOT) // @
#define IE_TILD S(IE_HASH) // ~
// Row 4
#define IE_PIPE S(IE_BSLS) // |
#define IE_LABK S(IE_COMM) // <
#define IE_RABK S(IE_DOT)  // >
#define IE_QUES S(IE_SLSH) // ?

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¦ │   │   │   │ € │   │   │   │   │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ É │   │   │   │ Ú │ Í │ Ó │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Á │   │   │   │   │   │   │   │   │   │ ´ │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IE_BRKP ALGR(IE_GRV)  // ¦
#define IE_EURO ALGR(IE_4)    // €
// Row 2
#define IE_EACU ALGR(IE_E)    // É
#define IE_UACU ALGR(IE_U)    // Ú
#define IE_IACU ALGR(IE_I)    // Í
#define IE_OACU ALGR(IE_O)    // Ó
// Row 3
#define IE_AACU ALGR(IE_A)    // Á
#define IE_ACUT ALGR(IE_QUOT) // ´ (dead)
