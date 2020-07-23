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
 * │ ° │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ Ö │ - │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Ð │ ' │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Æ │ ´ │ + │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ Þ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IS_RNGA KC_GRV  // ° (dead)
#define IS_1    KC_1    // 1
#define IS_2    KC_2    // 2
#define IS_3    KC_3    // 3
#define IS_4    KC_4    // 4
#define IS_5    KC_5    // 5
#define IS_6    KC_6    // 6
#define IS_7    KC_7    // 7
#define IS_8    KC_8    // 8
#define IS_9    KC_9    // 9
#define IS_0    KC_0    // 0
#define IS_ODIA KC_MINS // Ö
#define IS_MINS KC_EQL  // -
// Row 2
#define IS_Q    KC_Q    // Q
#define IS_W    KC_W    // W
#define IS_E    KC_E    // E
#define IS_R    KC_R    // R
#define IS_T    KC_T    // T
#define IS_Y    KC_Y    // Y
#define IS_U    KC_U    // U
#define IS_I    KC_I    // I
#define IS_O    KC_O    // O
#define IS_P    KC_P    // P
#define IS_ETH  KC_LBRC // Ð
#define IS_QUOT KC_RBRC // '
// Row 3
#define IS_A    KC_A    // A
#define IS_S    KC_S    // S
#define IS_D    KC_D    // D
#define IS_F    KC_F    // F
#define IS_G    KC_G    // G
#define IS_H    KC_H    // H
#define IS_J    KC_J    // J
#define IS_K    KC_K    // K
#define IS_L    KC_L    // L
#define IS_AE   KC_SCLN // Æ
#define IS_ACUT KC_QUOT // ´ (dead)
#define IS_PLUS KC_NUHS // +
// Row 4
#define IS_LABK KC_NUBS // <
#define IS_Z    KC_Z    // Z
#define IS_X    KC_X    // X
#define IS_C    KC_C    // C
#define IS_V    KC_V    // V
#define IS_B    KC_B    // B
#define IS_N    KC_N    // N
#define IS_M    KC_M    // M
#define IS_COMM KC_COMM // ,
#define IS_DOT  KC_DOT  // .
#define IS_THRN KC_SLSH // Þ

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¨ │ ! │ " │ # │ $ │ % │ & │ / │ ( │ ) │ = │   │ _ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ? │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ * │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IS_DIAE S(IS_RNGA) // ¨ (dead)
#define IS_EXLM S(IS_1)    // !
#define IS_DQUO S(IS_2)    // "
#define IS_HASH S(IS_3)    // #
#define IS_DLR  S(IS_4)    // $
#define IS_PERC S(IS_5)    // %
#define IS_AMPR S(IS_6)    // &
#define IS_SLSH S(IS_7)    // /
#define IS_LPRN S(IS_8)    // (
#define IS_RPRN S(IS_9)    // )
#define IS_EQL  S(IS_0)    // =
#define IS_UNDS S(IS_MINS) // _
// Row 2
#define IS_QUES S(IS_QUOT) // ?
// Row 3
#define IS_ASTR S(IS_PLUS) // *
// Row 4
#define IS_RABK S(IS_LABK) // >
#define IS_SCLN S(IS_COMM) // ;
#define IS_COLN S(IS_DOT)  // :

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │   │   │   │   │   │   │ { │ [ │ ] │ } │ \ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ @ │   │ € │   │   │   │   │   │   │   │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ ^ │ ` │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │   │   │   │   │   │   │ µ │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IS_DEG  ALGR(IS_RNGA) // °
#define IS_LCBR ALGR(IS_7)    // {
#define IS_LBRC ALGR(IS_8)    // [
#define IS_RBRC ALGR(IS_9)    // ]
#define IS_RCBR ALGR(IS_0)    // }
#define IS_BSLS ALGR(IS_ODIA) // (backslash)
// Row 2
#define IS_AT   ALGR(IS_Q)    // @
#define IS_EURO ALGR(IS_E)    // €
#define IS_TILD ALGR(IS_QUOT) // ~
// Row 3
#define IS_CIRC ALGR(IS_ACUT) // ^ (dead)
#define IS_GRV  ALGR(IS_PLUS) // ` (dead)
// Row 4
#define IS_PIPE ALGR(IS_LABK) // |
#define IS_MICR ALGR(IS_M)    // µ
