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
 * │ „ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Ă │ Î │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ș │ Ț │ Â │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define RO_DLQU KC_GRV  // „
#define RO_1    KC_1    // 1
#define RO_2    KC_2    // 2
#define RO_3    KC_3    // 3
#define RO_4    KC_4    // 4
#define RO_5    KC_5    // 5
#define RO_6    KC_6    // 6
#define RO_7    KC_7    // 7
#define RO_8    KC_8    // 8
#define RO_9    KC_9    // 9
#define RO_0    KC_0    // 0
#define RO_MINS KC_MINS // -
#define RO_EQL  KC_EQL  // =
// Row 2
#define RO_Q    KC_Q    // Q
#define RO_W    KC_W    // W
#define RO_E    KC_E    // E
#define RO_R    KC_R    // R
#define RO_T    KC_T    // T
#define RO_Y    KC_Y    // Y
#define RO_U    KC_U    // U
#define RO_I    KC_I    // I
#define RO_O    KC_O    // O
#define RO_P    KC_P    // P
#define RO_ABRV KC_LBRC // Ă
#define RO_ICIR KC_RBRC // Î
// Row 3
#define RO_A    KC_A    // A
#define RO_S    KC_S    // S
#define RO_D    KC_D    // D
#define RO_F    KC_F    // F
#define RO_G    KC_G    // G
#define RO_H    KC_H    // H
#define RO_J    KC_J    // J
#define RO_K    KC_K    // K
#define RO_L    KC_L    // L
#define RO_SCOM KC_SCLN // Ș
#define RO_TCOM KC_QUOT // Ț
#define RO_ACIR KC_NUHS // Â
// Row 4
#define RO_BSLS KC_NUBS // (backslash)
#define RO_Z    KC_Z    // Z
#define RO_X    KC_X    // X
#define RO_C    KC_C    // C
#define RO_V    KC_V    // V
#define RO_B    KC_B    // B
#define RO_N    KC_N    // N
#define RO_M    KC_M    // M
#define RO_COMM KC_COMM // ,
#define RO_DOT  KC_DOT  // .
#define RO_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ” │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │   │   │   │   │   │   │   │ ; │ : │ ? │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define RO_RDQU S(RO_DLQU) // ”
#define RO_EXLM S(RO_1)    // !
#define RO_AT   S(RO_2)    // @
#define RO_HASH S(RO_3)    // #
#define RO_DLR  S(RO_4)    // $
#define RO_PERC S(RO_5)    // %
#define RO_CIRC S(RO_6)    // ^
#define RO_AMPR S(RO_7)    // &
#define RO_ASTR S(RO_8)    // *
#define RO_LPRN S(RO_9)    // (
#define RO_RPRN S(RO_0)    // )
#define RO_UNDS S(RO_MINS) // _
#define RO_PLUS S(RO_EQL)  // +
// Row 4
#define RO_PIPE S(RO_BSLS) // |
#define RO_SCLN S(RO_COMM) // ;
#define RO_COLN S(RO_DOT)  // :
#define RO_QUES S(RO_SLSH) // ?

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ` │ ~ │ ˇ │ ^ │ ˘ │ ° │ ˛ │ ` │ ˙ │ ´ │ ˝ │ ¨ │ ¸ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │ § │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │ ß │ Đ │   │   │   │   │   │ Ł │   │ ' │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │ © │   │   │   │   │ < │ > │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define RO_GRV  ALGR(RO_DLQU) // `
#define RO_DTIL ALGR(RO_1)    // ~ (dead)
#define RO_CARN ALGR(RO_2)    // ˇ (dead)
#define RO_DCIR ALGR(RO_3)    // ^ (dead)
#define RO_BREV ALGR(RO_4)    // ˘ (dead)
#define RO_RNGA ALGR(RO_5)    // ° (dead)
#define RO_OGON ALGR(RO_6)    // ˛ (dead)
#define RO_DGRV ALGR(RO_7)    // ` (dead)
#define RO_DOTA ALGR(RO_8)    // ˙ (dead)
#define RO_ACUT ALGR(RO_9)    // ´ (dead)
#define RO_DACU ALGR(RO_0)    // ˝ (dead)
#define RO_DIAE ALGR(RO_MINS) // ¨ (dead)
#define RO_CEDL ALGR(RO_EQL)  // ¸ (dead)
// Row 2
#define RO_EURO ALGR(RO_E)    // €
#define RO_SECT ALGR(RO_P)    // §
#define RO_LBRC ALGR(RO_ABRV) // [
#define RO_RBRC ALGR(RO_ICIR) // ]
// Row 3
#define RO_SS   ALGR(RO_S)    // ß
#define RO_DSTR ALGR(RO_D)    // Đ
#define RO_LSTR ALGR(RO_L)    // Ł
#define RO_QUOT ALGR(RO_TCOM) // '
// Row 4
#define RO_COPY ALGR(RO_C)    // ©
#define RO_LABK ALGR(RO_COMM) // <
#define RO_RABK ALGR(RO_DOT)  // >

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │   │   │   │   │   │   │   │   │   │   │ – │ ± │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ " │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │ « │ » │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define RO_TILD S(ALGR(RO_DLQU)) // ~
#define RO_NDSH S(ALGR(RO_MINS)) // –
#define RO_PLMN S(ALGR(RO_EQL))  // ±
// Row 2
#define RO_LCBR S(ALGR(RO_ABRV)) // {
#define RO_RCBR S(ALGR(RO_ICIR)) // }
// Row 3
#define RO_DQUO S(ALGR(RO_TCOM)) // "
// Row 4
#define RO_LDAQ S(ALGR(RO_COMM)) // «
#define RO_RDAQ S(ALGR(RO_DOT))  // »
