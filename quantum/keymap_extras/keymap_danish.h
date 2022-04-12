/* Copyright 2019
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
 * │ ½ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Æ │ Ø │ ' │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DK_HALF KC_GRV  // ½
#define DK_1    KC_1    // 1
#define DK_2    KC_2    // 2
#define DK_3    KC_3    // 3
#define DK_4    KC_4    // 4
#define DK_5    KC_5    // 5
#define DK_6    KC_6    // 6
#define DK_7    KC_7    // 7
#define DK_8    KC_8    // 8
#define DK_9    KC_9    // 9
#define DK_0    KC_0    // 0
#define DK_PLUS KC_MINS // +
#define DK_ACUT KC_EQL  // ´ (dead)
// Row 2
#define DK_Q    KC_Q    // Q
#define DK_W    KC_W    // W
#define DK_E    KC_E    // E
#define DK_R    KC_R    // R
#define DK_T    KC_T    // T
#define DK_Y    KC_Y    // Y
#define DK_U    KC_U    // U
#define DK_I    KC_I    // I
#define DK_O    KC_O    // O
#define DK_P    KC_P    // P
#define DK_ARNG KC_LBRC // Å
#define DK_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define DK_A    KC_A    // A
#define DK_S    KC_S    // S
#define DK_D    KC_D    // D
#define DK_F    KC_F    // F
#define DK_G    KC_G    // G
#define DK_H    KC_H    // H
#define DK_J    KC_J    // J
#define DK_K    KC_K    // K
#define DK_L    KC_L    // L
#define DK_AE   KC_SCLN // Æ
#define DK_OSTR KC_QUOT // Ø
#define DK_QUOT KC_NUHS // '
// Row 4
#define DK_LABK KC_NUBS // <
#define DK_Z    KC_Z    // Z
#define DK_X    KC_X    // X
#define DK_C    KC_C    // C
#define DK_V    KC_V    // V
#define DK_B    KC_B    // B
#define DK_N    KC_N    // N
#define DK_M    KC_M    // M
#define DK_COMM KC_COMM // ,
#define DK_DOT  KC_DOT  // .
#define DK_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ § │ ! │ " │ # │ ¤ │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ^ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ * │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DK_SECT S(DK_HALF) // §
#define DK_EXLM S(DK_1)    // !
#define DK_DQUO S(DK_2)    // "
#define DK_HASH S(DK_3)    // #
#define DK_CURR S(DK_4)    // ¤
#define DK_PERC S(DK_5)    // %
#define DK_AMPR S(DK_6)    // &
#define DK_SLSH S(DK_7)    // /
#define DK_LPRN S(DK_8)    // (
#define DK_RPRN S(DK_9)    // )
#define DK_EQL  S(DK_0)    // =
#define DK_QUES S(DK_PLUS) // ?
#define DK_GRV  S(DK_ACUT) // ` (dead)
// Row 2
#define DK_CIRC S(DK_DIAE) // ^ (dead)
// Row 3
#define DK_ASTR S(DK_QUOT) // *
// Row 4
#define DK_RABK S(DK_LABK) // >
#define DK_SCLN S(DK_COMM) // ;
#define DK_COLN S(DK_DOT)  // :
#define DK_UNDS S(DK_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ @ │ £ │ $ │ € │   │ { │ [ │ ] │ } │   │ | │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │   │   │   │   │   │   │ µ │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DK_AT   ALGR(DK_2)    // @
#define DK_PND  ALGR(DK_3)    // £
#define DK_DLR  ALGR(DK_4)    // $
#define DK_EURO ALGR(DK_5)    // €
#define DK_LCBR ALGR(DK_7)    // {
#define DK_LBRC ALGR(DK_8)    // [
#define DK_RBRC ALGR(DK_9)    // ]
#define DK_RCBR ALGR(DK_0)    // }
#define DK_PIPE ALGR(DK_ACUT) // |
// Row 2
#define DK_TILD ALGR(DK_DIAE) // ~ (dead)
// Row 4
#define DK_BSLS ALGR(DK_LABK) // (backslash)
#define DK_MICR ALGR(DK_M)    // µ
