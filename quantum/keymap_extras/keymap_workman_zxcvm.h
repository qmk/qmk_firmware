/* Copyright 2018 Jacob Jerrell
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
 
/* Workman ZXCVM layout - defaults CVM keys to their QWERTY positions
 * to make this layout easier to use with other QWERTY-like layouts
 * installed on the same machine (mainly because of CTRL+X, CTRL+C
 * and CTRL+V shortcuts).
 */

#pragma once

#include "keymap.h"

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ D │ R │ W │ B │ J │ F │ U │ P │ ; │ [ │ ] │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ A │ S │ H │ T │ G │ Y │ N │ E │ O │ I │ ' │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ Z │ X │ M │ C │ V │ K │ L │ , │ . │ / │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define WK_GRV  KC_GRV  // `
#define WK_1    KC_1    // 1
#define WK_2    KC_2    // 2
#define WK_3    KC_3    // 3
#define WK_4    KC_4    // 4
#define WK_5    KC_5    // 5
#define WK_6    KC_6    // 6
#define WK_7    KC_7    // 7
#define WK_8    KC_8    // 8
#define WK_9    KC_9    // 9
#define WK_0    KC_0    // 0
#define WK_MINS KC_MINS // -
#define WK_EQL  KC_EQL  // =
// Row 2
#define WK_Q    KC_Q    // Q
#define WK_D    KC_W    // D
#define WK_R    KC_E    // R
#define WK_W    KC_R    // W
#define WK_B    KC_T    // B
#define WK_J    KC_Y    // J
#define WK_F    KC_U    // F
#define WK_U    KC_I    // U
#define WK_P    KC_O    // P
#define WK_SCLN KC_P    // ;
#define WK_LBRC KC_LBRC // [
#define WK_RBRC KC_RBRC // ]
#define WK_BSLS KC_BSLS // (backslash)
// Row 3
#define WK_A    KC_A    // A
#define WK_S    KC_S    // S
#define WK_H    KC_D    // H
#define WK_T    KC_F    // T
#define WK_G    KC_G    // G
#define WK_Y    KC_H    // Y
#define WK_N    KC_J    // N
#define WK_E    KC_K    // E
#define WK_O    KC_L    // O
#define WK_I    KC_SCLN // I
#define WK_QUOT KC_QUOT // '
// Row 4
#define WK_Z    KC_Z    // Z
#define WK_X    KC_X    // X
#define WK_C    KC_C    // C
#define WK_V    KC_V    // V
#define WK_M    KC_B    // M
#define WK_K    KC_N    // K
#define WK_L    KC_M    // L
#define WK_COMM KC_COMM // ,
#define WK_DOT  KC_DOT  // .
#define WK_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │ : │ { │ } │  |  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │ " │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define WK_TILD S(WK_GRV)  // ~
#define WK_EXLM S(WK_1)    // !
#define WK_AT   S(WK_2)    // @
#define WK_HASH S(WK_3)    // #
#define WK_DLR  S(WK_4)    // $
#define WK_PERC S(WK_5)    // %
#define WK_CIRC S(WK_6)    // ^
#define WK_AMPR S(WK_7)    // &
#define WK_ASTR S(WK_8)    // *
#define WK_LPRN S(WK_9)    // (
#define WK_RPRN S(WK_0)    // )
#define WK_UNDS S(WK_MINS) // _
#define WK_PLUS S(WK_EQL)  // +
// Row 2
#define WK_COLN S(WK_SCLN) // :
#define WK_LCBR S(WK_LBRC) // {
#define WK_RCBR S(WK_RBRC) // }
#define WK_PIPE S(WK_BSLS) // |
// Row 3
#define WK_DQUO S(WK_QUOT) // "
// Row 4
#define WK_LABK S(WK_COMM) // <
#define WK_RABK S(WK_DOT)  // >
#define WK_QUES S(WK_SLSH) // ?
