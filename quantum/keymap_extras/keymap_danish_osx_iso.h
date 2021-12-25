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
 * │ $ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │       │
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
#define DK_DLR  KC_GRV  // $
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
#define DK_ARNG KC_QUOT // Å
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
#define DK_OSTR KC_LBRC // Ø
#define DK_QUOT KC_NUHS // '
// Row 4
#define DK_LABK KC_GRV  // <
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
 * │ § │ ! │ " │ # │ € │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
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
#define DK_SECT S(DK_DLR)  // §
#define DK_EXLM S(DK_1)    // !
#define DK_DQUO S(DK_2)    // "
#define DK_HASH S(DK_3)    // #
#define DK_EURO S(DK_4)    // €
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

/* Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │  │ ¡ │ “ │ § │ £ │ ∞ │ ™ │ ¶ │ [ │ ] │ ≠ │ ± │ ' │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ ° │ ∑ │ é │ ® │ † │ ¥ │ ü │ | │ œ │ π │ ‘ │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ ª │ ß │ ∂ │ ƒ │ © │ « │ ‹ │ ∆ │ ¬ │ ä │ ö │ @ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≤ │ Ω │ … │ ç │ √ │ ∫ │ ñ │ µ │ ‚ │ · │ – │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DK_APPL  A(DK_SECT)  //  (Apple logo)
#define DK_IEXL  A(DK_1)     // ¡
#define DK_LDQU  A(DK_2)     // “
                             // § (DK_SECT is already defined)
#define DK_PND   A(DK_4)     // £
#define DK_INFN  A(DK_5)     // ∞
#define DK_TM    A(DK_6)     // ™
#define DK_PILC  A(DK_7)     // ¶
#define DK_LBRC  A(DK_8)     // [
#define DK_RBRC  A(DK_9)     // ]
#define DK_NEQL  A(DK_0)     // ≠
#define DK_PLMN  A(DK_PLUS)  // ±
                             // ' (DK_QUOT is already defined)
// Row 2 
#define DK_DEG   A(DK_Q)     // °
#define DK_NARS  A(DK_W)     // ∑
#define DK_LEAC  A(DK_E)     // é
#define DK_REGD  A(DK_R)     // ®
#define DK_DAGG  A(DK_T)     // †
#define DK_YEN   A(DK_Y)     // ¥
#define DK_UDIA  A(DK_U)     // ü
#define DK_PIPE  A(DK_I)     // |
#define DK_OE    A(DK_O)     // œ
#define DK_PI    A(DK_P)     // π
#define DK_LSQU  A(DK_ARNG)  // ‘
#define DK_TILD  A(DK_DIAE)  // ~ (dead)
// Row 3 
#define DK_FORD  A(DK_A)     // ª
#define DK_SS    A(DK_S)     // ß
#define DK_PDIF  A(DK_D)     // ∂
#define DK_FHK   A(DK_F)     // ƒ
#define DK_COPY  A(DK_G)     // ©
#define DK_LDAQ  A(DK_H)     // «
#define DK_LSAQ  A(DK_J)     // ‹
#define DK_INCR  A(DK_K)     // ∆
#define DK_NOT   A(DK_L)     // ¬
#define DK_ADIA  A(DK_AE)    // ä
#define DK_ODIA  A(DK_OSTR)  // ö
#define DK_AT    A(DK_QUOT)  // @
// Row 4
#define DK__LTEQ A(DK_LABK)  // ≤
#define DK_OMEG  A(DK_Z)     // Ω
#define DK_ELLP  A(DK_X)     // …
#define DK_CCED  A(DK_C)     // ç
#define DK_SQRT  A(DK_V)     // √
#define DK_INTG  A(DK_B)     // ∫
#define DK_NTIL  A(DK_N)     // ñ
#define DK_MICR  A(DK_M)     // µ
#define DK_SLQU  A(DK_COMM)  // ‚
#define DK_MDDT  A(DK_DOT)   // ·
#define DK_NDSH  A(DK_MINS)  // –

/* Shift+Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ' │ ¯ │ ” │ $ │ ¢ │ ‰ │ ˜ │ \ │ { │ } │ ≈ │ ¿ │ ⁄ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ • │ ˚ │   │ Â │ ‡ │ Ÿ │   │ ı │   │ ∏ │ ’ │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Ê │ ˇ │ ˘ │ ﬁ │ Á │ » │ › │ ˝ │ ﬂ │   │   │ º │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≥ │ ¸ │ ˙ │   │ ◊ │ Ë │   │ ˛ │ „ │ ÷ │ — │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
                              // ' (DK_QUOT is already defined)
#define DK_MACR S(A(DK_1))    // ¯
#define DK_RDQU S(A(DK_2))    // ”
                              // $ (DK_DLR is already defined)
#define DK_CENT S(A(DK_4))    // ¢
#define DK_PERM S(A(DK_5))    // ‰
#define DK_STIL S(A(DK_6))    // ˜
#define DK_BSLS S(A(DK_7))    // (backslash)
#define DK_LCBR S(A(DK_8))    // {
#define DK_RCBR S(A(DK_9))    // }
#define DK_AEQL S(A(DK_0))    // ≈
#define DK_IQUE S(A(DK_PLUS)) // ¿
#define DK_FRSL S(A(DK_GRV))  // ⁄
// Row 2
#define DK_BULT S(A(DK_Q))    // •
#define DK_RNGA S(A(DK_W))    // ˚
#define DK_CACI S(A(DK_R))    // Â
#define DK_DDAG S(A(DK_T))    // ‡
#define DK_CYDI S(A(DK_Y))    // Ÿ
#define DK_DLSI S(A(DK_I))    // ı
#define DK_NARP S(A(DK_P))    // ∏
#define DK_RSQU S(A(DK_ARNG)) // ’
                              // ^ (DK_CIRC is already defined)
// Row 3
#define DK_ECIR S(A(DK_A))    // Ê
#define DK_CARN S(A(DK_S))    // ˇ
#define DK_BREV S(A(DK_D))    // ˘
#define DK_FI   S(A(DK_F))    // ﬁ
#define DK_CAAC S(A(DK_G))    // Á
#define DK_RDAQ S(A(DK_H))    // »
#define DK_RSAQ S(A(DK_J))    // ›
#define DK_DACU S(A(DK_K))    // ˝
#define DK_FL   S(A(DK_L))    // ﬂ
#define DK_MORD S(A(DK_QUOT)) // º
// Row 4
#define DK_GTEQ S(A(DK_LABK)) // ≥
#define DK_CEDL S(A(DK_Z))    // ¸
#define DK_DOTA S(A(DK_X))    // ˙
#define DK_LOZN S(A(DK_V))    // ◊
#define DK_CEDI S(A(DK_B))    // Ë
#define DK_OGON S(A(DK_M))    // ˛
#define DK_DLQU S(A(DK_COMM)) // „
#define DK_DIV  S(A(DK_DOT))  // ÷
#define DK_MDSH S(A(DK_MINS)) // —
