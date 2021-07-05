/* Copyright 2015-2016 Jack Humbert
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
 * │ º │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ ¡ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ ` │ + │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ñ │ ´ │ Ç │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define ES_MORD KC_GRV  // º
#define ES_1    KC_1    // 1
#define ES_2    KC_2    // 2
#define ES_3    KC_3    // 3
#define ES_4    KC_4    // 4
#define ES_5    KC_5    // 5
#define ES_6    KC_6    // 6
#define ES_7    KC_7    // 7
#define ES_8    KC_8    // 8
#define ES_9    KC_9    // 9
#define ES_0    KC_0    // 0
#define ES_QUOT KC_MINS // '
#define ES_IEXL KC_EQL  // ¡
// Row 2
#define ES_Q    KC_Q    // Q
#define ES_W    KC_W    // W
#define ES_E    KC_E    // E
#define ES_R    KC_R    // R
#define ES_T    KC_T    // T
#define ES_Y    KC_Y    // Y
#define ES_U    KC_U    // U
#define ES_I    KC_I    // I
#define ES_O    KC_O    // O
#define ES_P    KC_P    // P
#define ES_GRV  KC_LBRC // ` (dead)
#define ES_PLUS KC_RBRC // +
// Row 3
#define ES_A    KC_A    // A
#define ES_S    KC_S    // S
#define ES_D    KC_D    // D
#define ES_F    KC_F    // F
#define ES_G    KC_G    // G
#define ES_H    KC_H    // H
#define ES_J    KC_J    // J
#define ES_K    KC_K    // K
#define ES_L    KC_L    // L
#define ES_NTIL KC_SCLN // Ñ
#define ES_ACUT KC_QUOT // ´ (dead)
#define ES_CCED KC_NUHS // Ç
// Row 4
#define ES_LABK KC_NUBS // <
#define ES_Z    KC_Z    // Z
#define ES_X    KC_X    // X
#define ES_C    KC_C    // C
#define ES_V    KC_V    // V
#define ES_B    KC_B    // B
#define ES_N    KC_N    // N
#define ES_M    KC_M    // M
#define ES_COMM KC_COMM // ,
#define ES_DOT  KC_DOT  // .
#define ES_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ª │ ! │ " │ · │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ ¿ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ^ │ * │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ ¨ │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define ES_FORD S(ES_MORD) // ª
#define ES_EXLM S(ES_1)    // !
#define ES_DQUO S(ES_2)    // "
#define ES_BULT S(ES_3)    // ·
#define ES_DLR  S(ES_4)    // $
#define ES_PERC S(ES_5)    // %
#define ES_AMPR S(ES_6)    // &
#define ES_SLSH S(ES_7)    // /
#define ES_LPRN S(ES_8)    // (
#define ES_RPRN S(ES_9)    // )
#define ES_EQL  S(ES_0)    // =
#define ES_QUES S(ES_QUOT) // ?
#define ES_IQUE S(ES_IEXL) // ¿
// Row 2
#define ES_CIRC S(ES_GRV)  // ^ (dead)
#define ES_ASTR S(ES_PLUS) // *
// Row 3
#define ES_DIAE S(ES_ACUT) // ¨ (dead)
// Row 4
#define ES_RABK S(ES_LABK) // >
#define ES_SCLN S(KC_COMM) // ;
#define ES_COLN S(KC_DOT)  // :
#define ES_UNDS S(ES_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ \ │ | │ @ │ # │ ~ │ € │ ¬ │   │   │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ { │ } │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define ES_BSLS ALGR(ES_MORD) // (backslash)
#define ES_PIPE ALGR(ES_1)    // |
#define ES_AT   ALGR(ES_2)    // @
#define ES_HASH ALGR(ES_3)    // #
#define ES_TILD ALGR(ES_4)    // ~
#define ES_EURO ALGR(ES_5)    // €
#define ES_NOT  ALGR(ES_6)    // ¬
// Row 2
#define ES_LBRC ALGR(ES_GRV)  // [
#define ES_RBRC ALGR(ES_PLUS) // ]
// Row 3
#define ES_LCBR ALGR(ES_ACUT) // {
#define ES_RCBR ALGR(ES_CCED) // }
