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
 * │ ; │ + │ ě │ š │ č │ ř │ ž │ ý │ á │ í │ é │ = │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ ú │ ) │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ů │ § │ ¨ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CZ_SCLN KC_GRV  // ;
#define CZ_PLUS KC_1    // +
#define CZ_ECAR KC_2    // ě
#define CZ_SCAR KC_3    // š
#define CZ_CCAR KC_4    // č
#define CZ_RCAR KC_5    // ř
#define CZ_ZCAR KC_6    // ž
#define CZ_YACU KC_7    // ý
#define CZ_AACU KC_8    // á
#define CZ_IACU KC_9    // í
#define CZ_EACU KC_0    // é
#define CZ_EQL  KC_MINS // =
#define CZ_ACUT KC_EQL  // ´ (dead)
// Row 2
#define CZ_Q    KC_Q    // Q
#define CZ_W    KC_W    // W
#define CZ_E    KC_E    // E
#define CZ_R    KC_R    // R
#define CZ_T    KC_T    // T
#define CZ_Z    KC_Y    // Z
#define CZ_U    KC_U    // U
#define CZ_I    KC_I    // I
#define CZ_O    KC_O    // O
#define CZ_P    KC_P    // P
#define CZ_UACU KC_LBRC // ú
#define CZ_RPRN KC_RBRC // )
// Row 3
#define CZ_A    KC_A    // A
#define CZ_S    KC_S    // S
#define CZ_D    KC_D    // D
#define CZ_F    KC_F    // F
#define CZ_G    KC_G    // G
#define CZ_H    KC_H    // H
#define CZ_J    KC_J    // J
#define CZ_K    KC_K    // K
#define CZ_L    KC_L    // L
#define CZ_URNG KC_SCLN // ů
#define CZ_SECT KC_QUOT // §
#define CZ_DIAE KC_NUHS // ¨ (dead)
// Row 4
#define CZ_BSLS KC_NUBS // (backslash)
#define CZ_Y    KC_Z    // Y
#define CZ_X    KC_X    // X
#define CZ_C    KC_C    // C
#define CZ_V    KC_V    // V
#define CZ_B    KC_B    // B
#define CZ_N    KC_N    // N
#define CZ_M    KC_M    // M
#define CZ_COMM KC_COMM // ,
#define CZ_DOT  KC_DOT  // .
#define CZ_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ % │ ˇ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ / │ ( │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ " │ ! │ ' │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │   │   │   │   │   │   │   │ ? │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CZ_RNGA S(CZ_SCLN) // ° (dead)
#define CZ_1    S(CZ_PLUS) // 1
#define CZ_2    S(CZ_ECAR) // 2
#define CZ_3    S(CZ_SCAR) // 3
#define CZ_4    S(CZ_CCAR) // 4
#define CZ_5    S(CZ_RCAR) // 5
#define CZ_6    S(CZ_ZCAR) // 6
#define CZ_7    S(CZ_YACU) // 7
#define CZ_8    S(CZ_AACU) // 8
#define CZ_9    S(CZ_IACU) // 9
#define CZ_0    S(CZ_EACU) // 0
#define CZ_PERC S(CZ_PLUS) // %
#define CZ_CARN S(CZ_ACUT) // ˇ (dead)
// Row 2
#define CZ_SLSH S(CZ_UACU) // /
#define CZ_LPRN S(CZ_RPRN) // (
// Row 3
#define CZ_DQUO S(CZ_URNG) // "
#define CZ_EXLM S(CZ_SECT) // !
#define CZ_QUOT S(CZ_DIAE) // '
// Row 4
#define CZ_PIPE S(CZ_BSLS) // |
#define CZ_QUES S(CZ_COMM) // ?
#define CZ_COLN S(CZ_DOT)  // :
#define CZ_UNDS S(CZ_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ~ │   │ ^ │ ˘ │   │ ˛ │ ` │ ˙ │   │ ˝ │   │ ¸ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │   │ ÷ │ × │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │ đ │ Đ │ [ │ ] │   │   │ ł │ Ł │ $ │ ß │ ¤ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │ # │ & │ @ │ { │ } │   │ < │ > │ * │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CZ_TILD ALGR(CZ_PLUS) // ~
#define CZ_CIRC ALGR(CZ_SCAR) // ^ (dead)
#define CZ_BREV ALGR(CZ_CCAR) // ˘ (dead)
#define CZ_OGON ALGR(CZ_ZCAR) // ˛ (dead)
#define CZ_GRV  ALGR(CZ_YACU) // ` (dead)
#define CZ_DOTA ALGR(CZ_AACU) // ˙ (dead)
#define CZ_DACU ALGR(CZ_EACU) // ˝ (dead)
#define CZ_CEDL ALGR(CZ_ACUT) // ¸ (dead)
// Row 2
#define CZ_EURO ALGR(CZ_E)    // €
#define CZ_DIV  ALGR(CZ_UACU) // ÷
#define CZ_MUL  ALGR(CZ_RPRN) // ×
// Row 3
#define CZ_LDST ALGR(CZ_S)    // đ
#define CZ_CDST ALGR(CZ_D)    // Đ
#define CZ_LBRC ALGR(CZ_F)    // [
#define CZ_RBRC ALGR(CZ_G)    // ]
#define CZ_LLST ALGR(CZ_K)    // ł
#define CZ_CLST ALGR(CZ_L)    // Ł
#define CZ_DLR  ALGR(CZ_URNG) // $
#define CZ_SS   ALGR(CZ_SECT) // ß
#define CZ_CURR ALGR(CZ_DIAE) // ¤
// Row 4
#define CZ_HASH ALGR(CZ_X)    // #
#define CZ_AMPR ALGR(CZ_C)    // &
#define CZ_AT   ALGR(CZ_V)    // @
#define CZ_LCBR ALGR(CZ_B)    // {
#define CZ_RCBR ALGR(CZ_N)    // }
#define CZ_LABK ALGR(CZ_COMM) // <
#define CZ_RABK ALGR(CZ_DOT)  // >
#define CZ_ASTR ALGR(CZ_MINS) // *
