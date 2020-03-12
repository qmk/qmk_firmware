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
 * │ \ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ « │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ + │ ´ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ç │ º │ ~ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define PT_BSLS KC_GRV  // (backslash)
#define PT_1    KC_1    // 1
#define PT_2    KC_2    // 2
#define PT_3    KC_3    // 3
#define PT_4    KC_4    // 4
#define PT_5    KC_5    // 5
#define PT_6    KC_6    // 6
#define PT_7    KC_7    // 7
#define PT_8    KC_8    // 8
#define PT_9    KC_9    // 9
#define PT_0    KC_0    // 0
#define PT_QUOT KC_MINS // '
#define PT_LDAQ KC_EQL  // «
// Row 2
#define PT_Q    KC_Q    // Q
#define PT_W    KC_W    // W
#define PT_E    KC_E    // E
#define PT_R    KC_R    // R
#define PT_T    KC_T    // T
#define PT_Y    KC_Y    // Y
#define PT_U    KC_U    // U
#define PT_I    KC_I    // I
#define PT_O    KC_O    // O
#define PT_P    KC_P    // P
#define PT_PLUS KC_LBRC // +
#define PT_ACUT KC_RBRC // ´ (dead)
// Row 3
#define PT_A    KC_A    // A
#define PT_S    KC_S    // S
#define PT_D    KC_D    // D
#define PT_F    KC_F    // F
#define PT_G    KC_G    // G
#define PT_H    KC_H    // H
#define PT_J    KC_J    // J
#define PT_K    KC_K    // K
#define PT_L    KC_L    // L
#define PT_CCED KC_SCLN // Ç
#define PT_MORD KC_QUOT // º
#define PT_TILD KC_NUHS // ~ (dead)
// Row 4
#define PT_LABK KC_NUBS // <
#define PT_Z    KC_Z    // Z
#define PT_X    KC_X    // X
#define PT_C    KC_C    // C
#define PT_V    KC_V    // V
#define PT_B    KC_B    // B
#define PT_N    KC_N    // N
#define PT_M    KC_M    // M
#define PT_COMM KC_COMM // ,
#define PT_DOT  KC_DOT  // .
#define PT_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ | │ ! │ " │ # │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ » │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ * │ ` │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ ª │ ^ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define PT_PIPE S(PT_BSLS) // |
#define PT_EXLM S(PT_1)    // !
#define PT_DQUO S(PT_2)    // "
#define PT_HASH S(PT_3)    // #
#define PT_DLR  S(PT_4)    // $
#define PT_PERC S(PT_5)    // %
#define PT_AMPR S(PT_6)    // &
#define PT_SLSH S(PT_7)    // /
#define PT_LPRN S(PT_8)    // (
#define PT_RPRN S(PT_9)    // )
#define PT_EQL  S(PT_0)    // =
#define PT_QUES S(PT_QUOT) // ?
#define PT_RDAQ S(PT_LDAQ) // »
// Row 2
#define PT_ASTR S(PT_PLUS) // *
#define PT_GRV  S(PT_ACUT) // ` (dead)
// Row 3
#define PT_FORD S(PT_MORD) // ª
#define PT_CIRC S(PT_TILD) // ^ (dead)
// Row 4
#define PT_RABK S(PT_LABK) // >
#define PT_SCLN S(PT_COMM) // ;
#define PT_COLN S(PT_DOT)  // :
#define PT_UNDS S(PT_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ @ │ £ │ § │ € │   │ { │ [ │ ] │ } │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ¨ │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define PT_AT   ALGR(PT_2)    // @
#define PT_PND  ALGR(PT_3)    // £
#define PT_SECT ALGR(PT_4)    // §
#define PT_EURO ALGR(PT_5)    // €
#define PT_LCBR ALGR(PT_7)    // {
#define PT_LBRC ALGR(PT_8)    // [
#define PT_RBRC ALGR(PT_9)    // ]
#define PT_RCBR ALGR(PT_0)    // }
// Row 2
#define PT_DIAE ALGR(PT_PLUS) // ¨ (dead)
