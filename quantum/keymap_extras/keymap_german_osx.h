/* Copyright 2016 Stephen Bösebeck
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
 * │ ^ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ß │ ´ │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ Ü │ + │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ # │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define DE_CIRC KC_GRV  // ^ (dead)
#define DE_1    KC_1    // 1
#define DE_2    KC_2    // 2
#define DE_3    KC_3    // 3
#define DE_4    KC_4    // 4
#define DE_5    KC_5    // 5
#define DE_6    KC_6    // 6
#define DE_7    KC_7    // 7
#define DE_8    KC_8    // 8
#define DE_9    KC_9    // 9
#define DE_0    KC_0    // 0
#define DE_SS   KC_MINS // ß
#define DE_ACUT KC_EQL  // ´ (dead)
// Row 2
#define DE_Q    KC_Q    // Q
#define DE_W    KC_W    // W
#define DE_E    KC_E    // E
#define DE_R    KC_R    // R
#define DE_T    KC_T    // T
#define DE_Z    KC_Y    // Z
#define DE_U    KC_U    // U
#define DE_I    KC_I    // I
#define DE_O    KC_O    // O
#define DE_P    KC_P    // P
#define DE_UDIA KC_LBRC // Ü
#define DE_PLUS KC_RBRC // +
// Row 3
#define DE_A    KC_A    // A
#define DE_S    KC_S    // S
#define DE_D    KC_D    // D
#define DE_F    KC_F    // F
#define DE_G    KC_G    // G
#define DE_H    KC_H    // H
#define DE_J    KC_J    // J
#define DE_K    KC_K    // K
#define DE_L    KC_L    // L
#define DE_ODIA KC_SCLN // Ö
#define DE_ADIA KC_QUOT // Ä
#define DE_HASH KC_NUHS // #
// Row 4
#define DE_LABK KC_NUBS // <
#define DE_Y    KC_Z    // Y
#define DE_X    KC_X    // X
#define DE_C    KC_C    // C
#define DE_V    KC_V    // V
#define DE_B    KC_B    // B
#define DE_N    KC_N    // N
#define DE_M    KC_M    // M
#define DE_COMM KC_COMM // ,
#define DE_DOT  KC_DOT  // .
#define DE_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │ ° │ ! │ " │ § │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ ` │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ * │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ ' │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define DE_DEG  S(DE_CIRC) // °
#define DE_EXLM S(DE_1)    // !
#define DE_DQUO S(DE_2)    // "
#define DE_SECT S(DE_3)    // §
#define DE_DLR  S(DE_4)    // $
#define DE_PERC S(DE_5)    // %
#define DE_AMPR S(DE_6)    // &
#define DE_SLSH S(DE_7)    // /
#define DE_LPRN S(DE_8)    // (
#define DE_RPRN S(DE_9)    // )
#define DE_EQL  S(DE_0)    // =
#define DE_QUES S(DE_SS)   // ?
#define DE_GRV  S(DE_ACUT) // ` (dead)
// Row 2
#define DE_ASTR S(DE_PLUS) // *
// Row 3
#define DE_QUOT S(DE_HASH) // '
// Row 4
#define DE_RABK S(DE_LABK) // >
#define DE_SCLN S(DE_COMM) // ;
#define DE_COLN S(DE_DOT)  // :
#define DE_UNDS S(DE_MINS) // _

/* Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │ „ │ ¡ │ “ │ ¶ │ ¢ │ [ │ ] │ | │ { │ } │ ≠ │ ¿ │   │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │ « │ ∑ │ € │ ® │ † │ Ω │ ¨ │ ⁄ │ Ø │ π │ • │ ± │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ Å │ ‚ │ ∂ │ ƒ │ © │ ª │ º │ ∆ │ @ │ Œ │ Æ │ ‘ │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ ≤ │ ¥ │ ≈ │ Ç │ √ │ ∫ │ ~ │ µ │ ∞ │ … │ – │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define DE_DLQU A(DE_CIRC) // „
#define DE_IEXL A(DE_1)    // ¡
#define DE_LDQU A(DE_2)    // “
#define DE_PILC A(DE_3)    // ¶
#define DE_CENT A(DE_4)    // ¢
#define DE_LBRC A(DE_5)    // [
#define DE_RBRC A(DE_6)    // ]
#define DE_PIPE A(DE_7)    // |
#define DE_LCBR A(DE_8)    // {
#define DE_RCBR A(DE_9)    // }
#define DE_NEQL A(DE_0)    // ≠
#define DE_IQUE A(DE_SS)   // ¿
// Row 2
#define DE_LDAQ A(DE_Q)    // «
#define DE_NARS A(DE_W)    // ∑
#define DE_EURO A(DE_E)    // €
#define DE_REGD A(DE_R)    // ®
#define DE_DAGG A(DE_T)    // †
#define DE_OMEG A(DE_Z)    // Ω
#define DE_DIAE A(DE_U)    // ¨ (dead)
#define DE_FRSL A(DE_I)    // ⁄
#define DE_OSTR A(DE_O)    // Ø
#define DE_PI   A(DE_P)    // π
#define DE_BULT A(DE_UDIA) // •
#define DE_PLMN A(DE_PLUS) // ±
// Row 3
#define DE_ARNG A(DE_A)    // Å
#define DE_SLQU A(DE_S)    // ‚
#define DE_PDIF A(DE_D)    // ∂
#define DE_FHK  A(DE_F)    // ƒ
#define DE_COPY A(DE_G)    // ©
#define DE_FORD A(DE_H)    // ª
#define DE_MORD A(DE_J)    // º
#define DE_INCR A(DE_K)    // ∆
#define DE_AT   A(DE_L)    // @
#define DE_OE   A(DE_ODIA) // Œ
#define DE_AE   A(DE_ADIA) // Æ
#define DE_LSQU A(DE_HASH) // ‘
// Row 4
#define DE_LTEQ A(DE_LABK) // ≤
#define DE_YEN  A(DE_Y)    // ¥
#define DE_AEQL A(DE_X)    // ≈
#define DE_CCCE A(DE_C)    // Ç
#define DE_SQRT A(DE_V)    // √
#define DE_INTG A(DE_B)    // ∫
#define DE_TILD A(DE_N)    // ~ (dead)
#define DE_MICR A(DE_M)    // µ
#define DE_INFN A(DE_COMM) // ∞
#define DE_ELLP A(DE_DOT)  // …
#define DE_NDSH A(DE_MINS) // –

/* Shift+Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │   │ ¬ │ ” │   │ £ │ ﬁ │   │ \ │ ˜ │ · │ ¯ │ ˙ │ ˚ │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │ » │   │ ‰ │ ¸ │ ˝ │ ˇ │ Á │ Û │   │ ∏ │   │  │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │   │ Í │ ™ │ Ï │ Ì │ Ó │ ı │   │ ﬂ │   │   │   │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ ≥ │ ‡ │ Ù │   │ ◊ │ ‹ │ › │ ˘ │ ˛ │ ÷ │ — │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define DE_NOT  S(A(DE_1))    // ¬
#define DE_RDQU S(A(DE_2))    // ”
#define DE_PND  S(A(DE_4))    // £
#define DE_FI   S(A(DE_5))    // ﬁ
#define DE_BSLS S(A(DE_7))    // (backslash)
#define DE_STIL S(A(DE_8))    // ˜
#define DE_MDDT S(A(DE_9))    // ·
#define DE_MACR S(A(DE_0))    // ¯
#define DE_DOTA S(A(DE_SS))   // ˙
#define DE_RNGA S(A(DE_ACUT)) // ˚
// Row 2
#define DE_RDAQ S(A(DE_Q))    // »
#define DE_PERM S(A(DE_E))    // ‰
#define DE_CEDL S(A(DE_R))    // ¸
#define DE_DACU S(A(DE_T))    // ˝
#define DE_CARN S(A(DE_Z))    // ˇ
#define DE_AACU S(A(DE_U))    // Á
#define DE_UCIR S(A(DE_I))    // Û
#define DE_NARP S(A(DE_P))    // ∏
#define DE_APPL S(A(DE_PLUS)) //  (Apple logo)
// Row 3
#define DE_IACU S(A(DE_S))    // Í
#define DE_TM   S(A(DE_D))    // ™
#define DE_IDIA S(A(DE_F))    // Ï
#define DE_IGRV S(A(DE_G))    // Ì
#define DE_OACU S(A(DE_H))    // Ó
#define DE_DLSI S(A(DE_J))    // ı
#define DE_FL   S(A(DE_L))    // ﬂ
// Row 4
#define DE_GTEQ S(A(DE_LABK)) // ≥
#define DE_DDAG S(A(DE_Y))    // ‡
#define DE_UGRV S(A(DE_X))    // Ù
#define DE_LOZN S(A(DE_V))    // ◊
#define DE_LSAQ S(A(DE_B))    // ‹
#define DE_RSAQ S(A(DE_N))    // ›
#define DE_BREV S(A(DE_M))    // ˘
#define DE_OGON S(A(DE_COMM)) // ˛
#define DE_DIV  S(A(DE_DOT))  // ÷
#define DE_MDSH S(A(DE_MINS)) // —

// DEPRECATED
#define DE_OSX_CIRC DE_CIRC
#define DE_OSX_1    DE_1
#define DE_OSX_2    DE_2
#define DE_OSX_3    DE_3
#define DE_OSX_4    DE_4
#define DE_OSX_5    DE_5
#define DE_OSX_6    DE_6
#define DE_OSX_7    DE_7
#define DE_OSX_8    DE_8
#define DE_OSX_9    DE_9
#define DE_OSX_0    DE_0
#define DE_OSX_SS   DE_SS
#define DE_OSX_ACUT DE_ACUT
#define DE_OSX_Q    DE_Q
#define DE_OSX_W    DE_W
#define DE_OSX_E    DE_E
#define DE_OSX_R    DE_R
#define DE_OSX_T    DE_T
#define DE_OSX_Z    DE_Z
#define DE_OSX_U    DE_U
#define DE_OSX_I    DE_I
#define DE_OSX_O    DE_O
#define DE_OSX_P    DE_P
#define DE_OSX_UE   DE_UDIA
#define DE_OSX_PLUS DE_PLUS
#define DE_OSX_A    DE_A
#define DE_OSX_S    DE_S
#define DE_OSX_D    DE_D
#define DE_OSX_F    DE_F
#define DE_OSX_G    DE_G
#define DE_OSX_H    DE_H
#define DE_OSX_J    DE_J
#define DE_OSX_K    DE_K
#define DE_OSX_L    DE_L
#define DE_OSX_OE   DE_ODIA
#define DE_OSX_AE   DE_ADIA
#define DE_OSX_HASH DE_HASH
#define DE_OSX_LESS DE_LABK
#define DE_OSX_Y    DE_Y
#define DE_OSX_X    DE_X
#define DE_OSX_C    DE_C
#define DE_OSX_V    DE_V
#define DE_OSX_B    DE_B
#define DE_OSX_N    DE_N
#define DE_OSX_M    DE_M
#define DE_OSX_COMM DE_COMM
#define DE_OSX_DOT  DE_DOT
#define DE_OSX_MINS DE_MINS

#define DE_OSX_RING DE_DEG
#define DE_OSX_EXLM DE_EXLM
#define DE_OSX_DQOT DE_DQUO
#define DE_OSX_PARA DE_SECT
#define DE_OSX_DLR  DE_DLR
#define DE_OSX_PERC DE_PERC
#define DE_OSX_AMPR DE_AMPR
#define DE_OSX_SLSH DE_SLSH
#define DE_OSX_LPRN DE_LPRN
#define DE_OSX_RPRN DE_RPRN
#define DE_OSX_EQL  DE_EQL
#define DE_OSX_QST  DE_QUES
#define DE_OSX_GRV  DE_GRV
#define DE_OSX_ASTR DE_ASTR
#define DE_OSX_QUOT DE_QUOT
#define DE_OSX_MORE DE_RABK
#define DE_OSX_COLN DE_COLN
#define DE_OSX_SCLN DE_SCLN
#define DE_OSX_UNDS DE_UNDS

#define DE_OSX_LBRC DE_LBRC
#define DE_OSX_RBRC DE_RBRC
#define DE_OSX_PIPE DE_PIPE
#define DE_OSX_LCBR DE_LCBR
#define DE_OSX_RCBR DE_RCBR
#define DE_OSX_AT   DE_AT
#define DE_OSX_EURO DE_EURO
#define DE_OSX_TILD DE_TILD
#define DE_OSX_BSLS DE_BSLS
