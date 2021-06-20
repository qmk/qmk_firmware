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
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ + │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ º │ ´ │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ç │ ~ │ \ │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define PT_SECT KC_GRV  // §
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
#define PT_PLUS KC_EQL  // +
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
#define PT_MORD KC_LBRC // º
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
#define PT_TILD KC_QUOT // ~ (dead)
#define PT_BSLS KC_NUHS // (backslash)
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
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │ ± │ ! │ " │ # │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ * │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ª │ ` │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │   │   │   │   │   │   │   │   │   │   │ ^ │ | │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define PT_PLMN S(PT_SECT) // ±
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
#define PT_ASTR S(PT_PLUS) // *
// Row 2
#define PT_FORD S(PT_MORD) // ª
#define PT_GRV  S(PT_ACUT) // ` (dead)
// Row 3
#define PT_CIRC S(PT_TILD) // ^ (dead)
#define PT_PIPE S(PT_BSLS) // |
// Row 4
#define PT_RABK S(PT_LABK) // >
#define PT_SCLN S(PT_COMM) // ;
#define PT_COLN S(PT_DOT)  // :
#define PT_UNDS S(PT_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │   │  │ @ │ € │ £ │ ‰ │ ¶ │ ÷ │ [ │ ] │ ≠ │   │   │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │ Œ │ ∑ │ Æ │ ® │ ™ │ ¥ │ † │ ı │ Ø │ π │ ° │ ¨ │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ Å │ ß │ ∂ │ ƒ │ ˙ │ ˇ │ ¯ │ „ │ ‘ │ ¸ │ ˜ │ ‹ │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ ≤ │ Ω │ « │ © │ √ │ ∫ │ ¬ │ µ │ “ │ … │ — │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define PT_APPL ALGR(PT_1)    //  (Apple logo)
#define PT_AT   ALGR(PT_2)    // @
#define PT_EURO ALGR(PT_3)    // €
#define PT_PND  ALGR(PT_4)    // £
#define PT_PERM ALGR(PT_5)    // ‰
#define PT_PILC ALGR(PT_6)    // ¶
#define PT_DIV  ALGR(PT_7)    // ÷
#define PT_LBRC ALGR(PT_8)    // [
#define PT_RBRC ALGR(PT_9)    // ]
#define PT_NEQL ALGR(PT_0)    // ≠
// Row 2
#define PT_OE   ALGR(PT_Q)    // Œ
#define PT_NARS ALGR(PT_W)    // ∑
#define PT_AE   ALGR(PT_E)    // Æ
#define PT_REGD ALGR(PT_R)    // ®
#define PT_TM   ALGR(PT_T)    // ™
#define PT_YEN  ALGR(PT_Y)    // ¥
#define PT_DAGG ALGR(PT_U)    // †
#define PT_DLSI ALGR(PT_I)    // ı
#define PT_OSTR ALGR(PT_O)    // Ø
#define PT_PI   ALGR(PT_P)    // π
#define PT_DEG  ALGR(PT_MORD) // °
#define PT_DIAE ALGR(PT_ACUT) // ¨ (dead)
// Row 3
#define PT_ARNG ALGR(PT_A)    // å
#define PT_SS   ALGR(PT_S)    // ß
#define PT_PDIF ALGR(PT_D)    // ∂
#define PT_FHK  ALGR(PT_F)    // ƒ
#define PT_DOTA ALGR(PT_G)    // ˙
#define PT_CARN ALGR(PT_H)    // ˇ
#define PT_MACR ALGR(PT_J)    // ¯
#define PT_DLQU ALGR(PT_K)    // „
#define PT_LSQU ALGR(PT_L)    // ‘
#define PT_CEDL ALGR(PT_CCED) // ¸
#define PT_STIL ALGR(PT_TILD) // ˜ (dead)
#define PT_LSAQ ALGR(PT_BSLS) // ‹
// Row 4
#define PT_LTEQ ALGR(PT_LABK) // ≤
#define PT_OMEG ALGR(PT_Z)    // Ω
#define PT_LDAQ ALGR(PT_X)    // «
#define PT_COPY ALGR(PT_C)    // ©
#define PT_SQRT ALGR(PT_V)    // √
#define PT_INTG ALGR(PT_B)    // ∫
#define PT_NOT  ALGR(PT_N)    // ¬
#define PT_MICR ALGR(PT_M)    // µ
#define PT_LDQU ALGR(PT_COMM) // “
#define PT_ELLP ALGR(PT_DOT)  // …
#define PT_MDSH ALGR(PT_MINS) // —

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │   │ ¡ │ ﬁ │ ﬂ │ ¢ │ ∞ │ • │ ⁄ │ { │ } │ ≈ │ ¿ │ ◊ │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │   │   │   │   │   │   │ ‡ │ ˚ │   │ ∏ │   │ ˝ │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │   │   │ ∆ │   │   │   │   │ ‚ │ ’ │ ˛ │ ˆ │ › │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ ≥ │   │ » │   │   │   │   │   │ ” │ · │ – │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define PT_IEXL S(ALGR(PT_1))    // ¡
#define PT_FI   S(ALGR(PT_2))    // ﬁ
#define PT_FL   S(ALGR(PT_3))    // ﬂ
#define PT_CENT S(ALGR(PT_4))    // ¢
#define PT_INFN S(ALGR(PT_5))    // ∞
#define PT_BULT S(ALGR(PT_6))    // •
#define PT_FRSL S(ALGR(PT_7))    // ⁄
#define PT_LCBR S(ALGR(PT_8))    // {
#define PT_RCBR S(ALGR(PT_9))    // }
#define PT_AEQL S(ALGR(PT_0))    // ≈
#define PT_IQUE S(ALGR(PT_QUOT)) // ¿
#define PT_LOZN S(ALGR(PT_PLUS)) // ◊
// Row 2
#define PT_DDAG S(ALGR(PT_U))    // ‡
#define PT_RNGA S(ALGR(PT_I))    // ˚
#define PT_NARP S(ALGR(PT_P))    // ∏
#define PT_DACU S(ALGR(PT_ACUT)) // ˝
// Row 3
#define PT_INCR S(ALGR(PT_D))    // ∆
#define PT_SLQU S(ALGR(PT_K))    // ‚
#define PT_RSQU S(ALGR(PT_L))    // ’
#define PT_OGON S(ALGR(PT_CCED)) // ˛
#define PT_DCIR S(ALGR(PT_TILD)) // ˆ (dead)
#define PT_RSAQ S(ALGR(PT_BSLS)) // ›
// Row 4
#define PT_GTEQ S(ALGR(PT_LABK)) // ≥
#define PT_RDAQ S(ALGR(PT_X))    // »
#define PT_RDQU S(ALGR(PT_COMM)) // ”
#define PT_MDDT S(ALGR(PT_DOT))  // ·
#define PT_NDSH S(ALGR(PT_MINS)) // –
