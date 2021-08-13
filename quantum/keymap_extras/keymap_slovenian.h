/* Copyright 2018 Žan Pevec
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
 * │ ¸ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ Š │ Đ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Č │ Ć │ Ž │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SI_CEDL KC_GRV  // ¸ (dead)
#define SI_1    KC_1    // 1
#define SI_2    KC_2    // 2
#define SI_3    KC_3    // 3
#define SI_4    KC_4    // 4
#define SI_5    KC_5    // 5
#define SI_6    KC_6    // 6
#define SI_7    KC_7    // 7
#define SI_8    KC_8    // 8
#define SI_9    KC_9    // 9
#define SI_0    KC_0    // 0
#define SI_QUOT KC_MINS // '
#define SI_PLUS KC_EQL  // +
// Row 2
#define SI_Q    KC_Q    // Q
#define SI_W    KC_W    // W
#define SI_E    KC_E    // E
#define SI_R    KC_R    // R
#define SI_T    KC_T    // T
#define SI_Z    KC_Y    // Z
#define SI_U    KC_U    // U
#define SI_I    KC_I    // I
#define SI_O    KC_O    // O
#define SI_P    KC_P    // P
#define SI_SCAR KC_LBRC // Š
#define SI_DSTR KC_RBRC // Đ
// Row 3
#define SI_A    KC_A    // A
#define SI_S    KC_S    // S
#define SI_D    KC_D    // D
#define SI_F    KC_F    // F
#define SI_G    KC_G    // G
#define SI_H    KC_H    // H
#define SI_J    KC_J    // J
#define SI_K    KC_K    // K
#define SI_L    KC_L    // L
#define SI_CCAR KC_SCLN // Č
#define SI_CACU KC_QUOT // Ć
#define SI_ZCAR KC_NUHS // Ž
// Row 4
#define SI_LABK KC_NUBS // <
#define SI_Y    KC_Z    // Y
#define SI_X    KC_X    // X
#define SI_C    KC_C    // C
#define SI_V    KC_V    // V
#define SI_B    KC_B    // B
#define SI_N    KC_N    // N
#define SI_M    KC_M    // M
#define SI_COMM KC_COMM // ,
#define SI_DOT  KC_DOT  // .
#define SI_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¨ │ ! │ " │ # │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ * │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SI_DIAE S(SI_CEDL) // ¨ (dead)
#define SI_EXLM S(SI_1)    // !
#define SI_DQUO S(SI_2)    // "
#define SI_HASH S(SI_3)    // #
#define SI_DLR  S(SI_4)    // $
#define SI_PERC S(SI_5)    // %
#define SI_AMPR S(SI_6)    // &
#define SI_SLSH S(SI_7)    // /
#define SI_LPRN S(SI_8)    // (
#define SI_RPRN S(SI_9)    // )
#define SI_EQL  S(SI_0)    // =
#define SI_QUES S(SI_QUOT) // ?
#define SI_ASTR S(SI_PLUS) // *
// Row 4
#define SI_RABK S(SI_LABK) // >
#define SI_SCLN S(SI_COMM) // ;
#define SI_COLN S(SI_DOT)  // :
#define SI_UNDS S(SI_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ~ │ ˇ │ ^ │ ˘ │ ° │ ˛ │ ` │ ˙ │ ´ │ ˝ │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ \ │ | │ € │   │   │   │   │   │   │   │ ÷ │ × │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │ [ │ ] │   │   │ ł │ Ł │   │ ß │ ¤ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │ @ │ { │ } │ § │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SI_TILD ALGR(SI_1)    // ~
#define SI_CARN ALGR(SI_2)    // ˇ (dead)
#define SI_CIRC ALGR(SI_3)    // ^ (dead)
#define SI_BREV ALGR(SI_4)    // ˘ (dead)
#define SI_RNGA ALGR(SI_5)    // ° (dead)
#define SI_OGON ALGR(SI_6)    // ˛ (dead)
#define SI_GRV  ALGR(SI_7)    // `
#define SI_DOTA ALGR(SI_8)    // ˙ (dead)
#define SI_ACUT ALGR(SI_9)    // ´ (dead)
#define SI_DACU ALGR(SI_0)    // ˝ (dead)
// Row 2
#define SI_BSLS ALGR(SI_Q)    // (backslash)
#define SI_PIPE ALGR(SI_W)    // |
#define SI_EURO ALGR(SI_E)    // €
#define SI_DIV  ALGR(SI_SCAR) // ÷
#define SI_MUL  ALGR(SI_DSTR) // ×
// Row 3
#define SI_LBRC ALGR(SI_F)    // [
#define SI_RBRC ALGR(SI_G)    // ]
#define SI_LLST ALGR(SI_K)    // ł
#define SI_CLST ALGR(SI_L)    // Ł
#define SI_SS   ALGR(SI_CACU) // ß
#define SI_CURR ALGR(SI_ZCAR) // ¤
// Row 4
#define SI_AT   ALGR(SI_V)    // @
#define SI_LCBR ALGR(SI_B)    // {
#define SI_RCBR ALGR(SI_N)    // }
#define SI_SECT ALGR(SI_M)    // §

// DEPRECATED
#define SI_QOT  SI_QUOT
#define SI_SV   SI_SCAR
#define SI_CV   SI_CCAR
#define SI_ZV   SI_ZCAR
#define SI_DQOT SI_DQUO
#define SI_QST  SI_QUES
