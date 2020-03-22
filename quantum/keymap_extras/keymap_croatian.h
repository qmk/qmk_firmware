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
 * │ ¸ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ Š │ Đ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Č │ Ć │ Ž │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define HR_CEDL KC_GRV  // ¸ (dead)
#define HR_1    KC_1    // 1
#define HR_2    KC_2    // 2
#define HR_3    KC_3    // 3
#define HR_4    KC_4    // 4
#define HR_5    KC_5    // 5
#define HR_6    KC_6    // 6
#define HR_7    KC_7    // 7
#define HR_8    KC_8    // 8
#define HR_9    KC_9    // 9
#define HR_0    KC_0    // 0
#define HR_QUOT KC_MINS // '
#define HR_PLUS KC_EQL  // +
// Row 2
#define HR_Q    KC_Q    // Q
#define HR_W    KC_W    // W
#define HR_E    KC_E    // E
#define HR_R    KC_R    // R
#define HR_T    KC_T    // T
#define HR_Z    KC_Y    // Z
#define HR_U    KC_U    // U
#define HR_I    KC_I    // I
#define HR_O    KC_O    // O
#define HR_P    KC_P    // P
#define HR_SCAR KC_LBRC // Š
#define HR_DSTR KC_RBRC // Đ
// Row 3
#define HR_A    KC_A    // A
#define HR_S    KC_S    // S
#define HR_D    KC_D    // D
#define HR_F    KC_F    // F
#define HR_G    KC_G    // G
#define HR_H    KC_H    // H
#define HR_J    KC_J    // J
#define HR_K    KC_K    // K
#define HR_L    KC_L    // L
#define HR_CCAR KC_SCLN // Č
#define HR_CACU KC_QUOT // Ć
#define HR_ZCAR KC_NUHS // Ž
// Row 4
#define HR_LABK KC_NUBS // <
#define HR_Y    KC_Z    // Y
#define HR_X    KC_X    // X
#define HR_C    KC_C    // C
#define HR_V    KC_V    // V
#define HR_B    KC_B    // B
#define HR_N    KC_N    // N
#define HR_M    KC_M    // M
#define HR_COMM KC_COMM // ,
#define HR_DOT  KC_DOT  // .
#define HR_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¨ │ ! │ " │ # │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ * │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define HR_DIAE S(HR_CEDL) // §
#define HR_EXLM S(HR_1)    // !
#define HR_DQUO S(HR_2)    // "
#define HR_HASH S(HR_3)    // #
#define HR_DLR  S(HR_4)    // $
#define HR_PERC S(HR_5)    // %
#define HR_AMPR S(HR_6)    // &
#define HR_SLSH S(HR_7)    // /
#define HR_LPRN S(HR_8)    // (
#define HR_RPRN S(HR_9)    // )
#define HR_EQL  S(HR_0)    // =
#define HR_QUES S(HR_QUOT) // ?
#define HR_ASTR S(HR_PLUS) // *
// Row 4
#define HR_RABK S(HR_LABK) // >
#define HR_SCLN S(HR_COMM) // ;
#define HR_COLN S(HR_DOT)  // :
#define HR_UNDS S(HR_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ~ │ ˇ │ ^ │ ˘ │ ° │ ˛ │ ` │ ˙ │ ´ │ ˝ │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ \ │ | │ € │   │   │   │   │   │   │   │ ÷ │ × │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │ [ │ ] │   │   │ ł │ Ł │   │ ß │ ¤ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │ @ │ { │ } │ § │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define HR_TILD ALGR(HR_1)    // ~
#define HR_CARN ALGR(HR_2)    // ˇ (dead)
#define HR_CIRC ALGR(HR_3)    // ^ (dead)
#define HR_BREV ALGR(HR_4)    // ˘ (dead)
#define HR_RNGA ALGR(HR_5)    // ° (dead)
#define HR_OGON ALGR(HR_6)    // ˛ (dead)
#define HR_GRV  ALGR(HR_7)    // `
#define HR_DOTA ALGR(HR_8)    // ˙ (dead)
#define HR_ACUT ALGR(HR_9)    // ´ (dead)
#define HR_DACU ALGR(HR_0)    // ˝ (dead)
// Row 2
#define HR_BSLS ALGR(HR_Q)    // (backslash)
#define HR_PIPE ALGR(HR_W)    // |
#define HR_EURO ALGR(HR_E)    // €
#define HR_DIV  ALGR(HR_SCAR) // ÷
#define HR_MUL  ALGR(HR_DSTR) // ×
// Row 3
#define HR_LBRC ALGR(HR_F)    // [
#define HR_RBRC ALGR(HR_G)    // ]
#define HR_LLST ALGR(HR_K)    // ł
#define HR_CLST ALGR(HR_L)    // Ł
#define HR_SS   ALGR(HR_CACU) // ß
#define HR_CURR ALGR(HR_ZCAR) // ¤
// Row 4
#define HR_AT   ALGR(HR_V)    // @
#define HR_LCBR ALGR(HR_B)    // {
#define HR_RCBR ALGR(HR_N)    // }
#define HR_SECT ALGR(HR_M)    // §
