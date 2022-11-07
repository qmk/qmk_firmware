/* Copyright 2022 Hugo Muñoz
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
//Spanish Latinamerican sort
/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ | │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ ¿ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ ´ │ + │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ñ │ { │ } │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SP_PIPE KC_GRV  // |
#define SP_1    KC_1    // 1
#define SP_2    KC_2    // 2
#define SP_3    KC_3    // 3
#define SP_4    KC_4    // 4
#define SP_5    KC_5    // 5
#define SP_6    KC_6    // 6
#define SP_7    KC_7    // 7
#define SP_8    KC_8    // 8
#define SP_9    KC_9    // 9
#define SP_0    KC_0    // 0
#define SP_QUOT KC_MINS // '
#define SP_IQUE KC_EQL  // ¿
// Row 2
#define SP_Q    KC_Q    // Q
#define SP_W    KC_W    // W
#define SP_E    KC_E    // E
#define SP_R    KC_R    // R
#define SP_T    KC_T    // T
#define SP_Y    KC_Y    // Y
#define SP_U    KC_U    // U
#define SP_I    KC_I    // I
#define SP_O    KC_O    // O
#define SP_P    KC_P    // P
#define SP_ACUT KC_LBRC // ´ (dead)
#define SP_PLUS KC_RBRC // +
// Row 3
#define SP_A    KC_A    // A
#define SP_S    KC_S    // S
#define SP_D    KC_D    // D
#define SP_F    KC_F    // F
#define SP_G    KC_G    // G
#define SP_H    KC_H    // H
#define SP_J    KC_J    // J
#define SP_K    KC_K    // K
#define SP_L    KC_L    // L
#define SP_NTIL KC_SCLN // Ñ
#define SP_LCBR KC_QUOT // { (dead)
#define SP_RCBR KC_NUHS // }
// Row 4
#define SP_LABK KC_NUBS // <
#define SP_Z    KC_Z    // Z
#define SP_X    KC_X    // X
#define SP_C    KC_C    // C
#define SP_V    KC_V    // V
#define SP_B    KC_B    // B
#define SP_N    KC_N    // N
#define SP_M    KC_M    // M
#define SP_COMM KC_COMM // ,
#define SP_DOT  KC_DOT  // .
#define SP_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │ ! │ " │ # │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ ¡ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ¨ │ * │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ [ │ ] │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SP_MORD S(SP_PIPE) // °
#define SP_EXLM S(SP_1)    // !
#define SP_DQUO S(SP_2)    // "
#define SP_HASH S(SP_3)    // #
#define SP_DLR  S(SP_4)    // $
#define SP_PERC S(SP_5)    // %
#define SP_AMPR S(SP_6)    // &
#define SP_SLSH S(SP_7)    // /
#define SP_LPRN S(SP_8)    // (
#define SP_RPRN S(SP_9)    // )
#define SP_EQL  S(SP_0)    // =
#define SP_QUES S(SP_QUOT) // ?
#define SP_IEXL S(SP_IQUE) // ¡
// Row 2
#define SP_DIAE S(SP_ACUT) // ¨ (dead)
#define SP_ASTR S(SP_PLUS) // *
// Row 3
#define SP_LBRC S(SP_LCBR) // [
#define SP_RBRC S(SP_RCBR) // ]
// Row 4
#define SP_RABK S(SP_LABK) // >
#define SP_SCLN S(KC_COMM) // ;
#define SP_COLN S(KC_DOT)  // :
#define SP_UNDS S(SP_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¬ │   │   │   │   │   │   │   │   │   │   │ \ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ @ │   │   │   │   │   │   │   │   │   │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ ^ │ ` │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SP_NOT  ALGR(SP_PIPE) // ¬
#define SP_BSLS ALGR(SP_QUOT) // (backslash)
// Row 2
#define SP_AT   ALGR(SP_Q)    // @
#define SP_TILD ALGR(SP_PLUS) // ~
// Row 3
#define SP_CIRC ALGR(SP_LCBR) // ^ (dead)
#define SP_GRV  ALGR(SP_RCBR) // ` (dead)