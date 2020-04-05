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
 * │ ; │ + │ ľ │ š │ č │ ť │ ž │ ý │ á │ í │ é │ = │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ ú │ ä │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ô │ § │ ň │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ & │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SK_SCLN KC_GRV  // ;
#define SK_PLUS KC_1    // +
#define SK_LACU KC_2    // ľ
#define SK_SCAR KC_3    // š
#define SK_CCAR KC_4    // č
#define SK_TACU KC_5    // ť
#define SK_ZCAR KC_6    // ž
#define SK_YACU KC_7    // ý
#define SK_AACU KC_8    // á
#define SK_IACU KC_9    // í
#define SK_EACU KC_0    // é
#define SK_EQL  KC_MINS // =
#define SK_ACUT KC_EQL  // ´ (dead)
// Row 2
#define SK_Q    KC_Q    // Q
#define SK_W    KC_W    // W
#define SK_E    KC_E    // E
#define SK_R    KC_R    // R
#define SK_T    KC_T    // T
#define SK_Z    KC_Y    // Z
#define SK_U    KC_U    // U
#define SK_I    KC_I    // I
#define SK_O    KC_O    // O
#define SK_P    KC_P    // P
#define SK_UACU KC_LBRC // ú
#define SK_ADIA KC_RBRC // ä
// Row 3
#define SK_A    KC_A    // A
#define SK_S    KC_S    // S
#define SK_D    KC_D    // D
#define SK_F    KC_F    // F
#define SK_G    KC_G    // G
#define SK_H    KC_H    // H
#define SK_J    KC_J    // J
#define SK_K    KC_K    // K
#define SK_L    KC_L    // L
#define SK_OCIR KC_SCLN // ô
#define SK_SECT KC_QUOT // §
#define SK_NCAR KC_NUHS // ň
// Row 4
#define SK_AMPR KC_NUBS // &
#define SK_Y    KC_Z    // Y
#define SK_X    KC_X    // X
#define SK_C    KC_C    // C
#define SK_V    KC_V    // V
#define SK_B    KC_B    // B
#define SK_N    KC_N    // N
#define SK_M    KC_M    // M
#define SK_COMM KC_COMM // ,
#define SK_DOT  KC_DOT  // .
#define SK_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ % │ ˇ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ / │ ( │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ " │ ! │ ) │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ * │   │   │   │   │   │   │   │ ? │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SK_RNGA S(SK_SCLN) // ° (dead)
#define SK_1    S(SK_PLUS) // 1
#define SK_2    S(SK_LACU) // 2
#define SK_3    S(SK_SCAR) // 3
#define SK_4    S(SK_CCAR) // 4
#define SK_5    S(SK_TACU) // 5
#define SK_6    S(SK_ZCAR) // 6
#define SK_7    S(SK_YACU) // 7
#define SK_8    S(SK_AACU) // 8
#define SK_9    S(SK_IACU) // 9
#define SK_0    S(SK_EACU) // 0
#define SK_PERC S(SK_EQL)  // %
#define SK_CARN S(SK_ACUT) // ˇ (dead)
// Row 2
#define SK_SLSH S(SK_UACU) // /
#define SK_LPRN S(SK_ADIA) // (
// Row 3
#define SK_DQUO S(SK_OCIR) // "
#define SK_EXLM S(SK_SECT) // !
#define SK_RPRN S(SK_NCAR) // )
// Row 4
#define SK_ASTR S(SK_AMPR) // *
#define SK_QUES S(SK_COMM) // ?
#define SK_COLN S(SK_DOT)  // :
#define SK_UNDS S(SK_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ~ │   │ ^ │ ˘ │ ° │ ˛ │ ` │ ˙ │   │ ˝ │ ¨ │ ¸ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ \ │ | │ € │   │   │   │   │   │   │ ' │ ÷ │ × │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │ đ │ Đ │ [ │ ] │   │   │ ł │ Ł │ $ │ ß │ ¤ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ > │ # │   │ @ │ { │ } │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SK_TILD ALGR(SK_PLUS) // ~
#define SK_CIRC ALGR(SK_LACU) // ^ (dead)
#define SK_BREV ALGR(SK_SCAR) // ˘ (dead)
#define SK_RNGA ALGR(SK_CCAR) // ° (dead)
#define SK_OGON ALGR(SK_TACU) // ˛ (dead)
#define SK_GRV  ALGR(SK_ZCAR) // `
#define SK_DOTA ALGR(SK_YACU) // ˙ (dead)
#define SK_DACU ALGR(SK_EACU) // ˝ (dead)
#define SK_DIAE ALGR(SK_EQL)  // ¨ (dead)
#define SK_CEDL ALGR(SK_ACUT) // ¸ (dead)
// Row 2
#define SK_BSLS ALGR(SK_Q)    // (backslash)
#define SK_PIPE ALGR(SK_W)    // |
#define SK_EURO ALGR(SK_E)    // €
#define SK_QUOT ALGR(SK_P)    // '
#define SK_DIV  ALGR(SK_UACU) // ÷
#define SK_MUL  ALGR(SK_ADIA) // ×
// Row 3
#define SK_LDST ALGR(SK_S)    // đ
#define SK_CDST ALGR(SK_D)    // Đ
#define SK_LBRC ALGR(SK_F)    // [
#define SK_RBRC ALGR(SK_G)    // ]
#define SK_LLST ALGR(SK_K)    // ł
#define SK_CLST ALGR(SK_L)    // Ł
#define SK_DLR  ALGR(SK_OCIR) // $
#define SK_SS   ALGR(SK_SECT) // ß
#define SK_CURR ALGR(SK_NCAR) // ¤
// Row 4
#define SK_LABK ALGR(SK_AMPR) // <
#define SK_RABK ALGR(SK_Y)    // >
#define SK_HASH ALGR(SK_X)    // #
#define SK_AT   ALGR(SK_V)    // @
#define SK_LCBR ALGR(SK_B)    // {
#define SK_RCBR ALGR(SK_N)    // }
