/* Copyright 2016 Sébastien Pérochon
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
 * │ @ │ & │ é │ " │ ' │ ( │ § │ è │ ! │ ç │ à │ ) │ - │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │ A │ Z │ E │ R │ T │ Y │ U │ I │ O │ P │ ^ │ $ │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ Q │ S │ D │ F │ G │ H │ J │ K │ L │ M │ ù │ ` │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ < │ W │ X │ C │ V │ B │ N │ , │ ; │ : │ = │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define FR_AT   KC_GRV  // @
#define FR_AMPR KC_1    // &
#define FR_LEAC KC_2    // é
#define FR_DQUO KC_3    // "
#define FR_QUOT KC_4    // '
#define FR_LPRN KC_5    // (
#define FR_SECT KC_6    // §
#define FR_LEGR KC_7    // è
#define FR_EXLM KC_8    // !
#define FR_LCCE KC_9    // ç
#define FR_LAGR KC_0    // à
#define FR_RPRN KC_MINS // )
#define FR_MINS KC_EQL  // -
// Row 2
#define FR_A    KC_Q    // A
#define FR_Z    KC_W    // Z
#define FR_E    KC_E    // E
#define FR_R    KC_R    // R
#define FR_T    KC_T    // T
#define FR_Y    KC_Y    // Y
#define FR_U    KC_U    // U
#define FR_I    KC_I    // I
#define FR_O    KC_O    // O
#define FR_P    KC_P    // P
#define FR_CIRC KC_LBRC // ^
#define FR_DLR  KC_RBRC // $
// Row 3
#define FR_Q    KC_A    // Q
#define FR_S    KC_S    // S
#define FR_D    KC_D    // D
#define FR_F    KC_F    // F
#define FR_G    KC_G    // G
#define FR_H    KC_H    // H
#define FR_J    KC_J    // J
#define FR_K    KC_K    // K
#define FR_L    KC_L    // L
#define FR_M    KC_SCLN // M
#define FR_LUGR KC_QUOT // ù
#define FR_GRV  KC_NUHS // `
// Row 4
#define FR_LABK KC_NUBS // <
#define FR_W    KC_Z    // W
#define FR_X    KC_X    // X
#define FR_C    KC_C    // C
#define FR_V    KC_V    // V
#define FR_B    KC_B    // B
#define FR_N    KC_N    // N
#define FR_COMM KC_M    // ,
#define FR_SCLN KC_COMM // ;
#define FR_COLN KC_DOT  // :
#define FR_EQL  KC_SLSH // =

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │ # │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ _ │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ¨ │ * │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │   │   │   │   │   │   │   │   │   │   │ % │ £ │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ > │   │   │   │   │   │   │ ? │ . │ / │ + │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define FR_HASH S(FR_AT)   // #
#define FR_1    S(FR_AMPR) // 1
#define FR_2    S(FR_LEAC) // 2
#define FR_3    S(FR_DQUO) // 3
#define FR_4    S(FR_QUOT) // 4
#define FR_5    S(FR_LPRN) // 5
#define FR_6    S(FR_SECT) // 6
#define FR_7    S(FR_LEGR) // 7
#define FR_8    S(FR_EXLM) // 8
#define FR_9    S(FR_LCCE) // 9
#define FR_0    S(FR_LAGR) // 0
#define FR_DEG  S(FR_RPRN) // °
#define FR_UNDS S(FR_MINS) // _
// Row 2
#define FR_DIAE S(FR_CIRC) // ¨ (dead)
#define FR_ASTR S(FR_DLR)  // *
// Row 3
#define FR_PERC S(FR_LUGR) // %
#define FR_PND  S(FR_GRV)  // £
// Row 4
#define FR_RABK S(FR_LABK) // >
#define FR_QUES S(FR_COMM) // ?
#define FR_DOT  S(FR_SCLN) // .
#define FR_SLSH S(FR_COLN) // /
#define FR_PLUS S(FR_EQL)  // +

/* Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │ • │  │ ë │ “ │ ‘ │ { │ ¶ │ « │ ¡ │ Ç │ Ø │ } │ — │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │ Æ │ Â │ Ê │ ® │ † │ Ú │ º │ î │ Œ │ π │ Ô │ € │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ ‡ │ Ò │ ∂ │ ƒ │ ﬁ │ Ì │ Ï │ È │ ¬ │ µ │ Ù │   │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ ≤ │ ‹ │ ≈ │ © │ ◊ │ ß │ ~ │ ∞ │ … │ ÷ │ ≠ │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define FR_BULT A(FR_AT)   // •
#define FR_APPL A(FR_AMPR) //  (Apple logo)
#define FR_LEDI A(FR_LEAC) // ë
#define FR_LDQU A(FR_DQUO) // “
#define FR_LSQU A(FR_QUOT) // ‘
#define FR_LCBR A(FR_LPRN) // {
#define FR_PILC A(FR_SECT) // ¶
#define FR_LDAQ A(FR_LEGR) // «
#define FR_IEXL A(FR_EXLM) // ¡
#define FR_CCCE A(FR_LCCE) // Ç
#define FR_OSTR A(FR_LAGR) // Ø
#define FR_RCBR A(FR_RPRN) // }
#define FR_MDSH A(FR_MINS) // —
// Row 2
#define FR_AE   A(FR_A)    // Æ
#define FR_CACI A(FR_Z)    // Â
#define FR_ECIR A(FR_E)    // Ê
#define FR_REGD A(FR_R)    // ®
#define FR_DAGG A(FR_T)    // †
#define FR_CUAC A(FR_Y)    // Ú
#define FR_MORD A(FR_U)    // º
#define FR_LICI A(FR_I)    // î
#define FR_OE   A(FR_O)    // Œ
#define FR_PI   A(FR_P)    // π
#define FR_OCIR A(FR_CIRC) // Ô
#define FR_EURO A(FR_DLR)  // €
// Row 3
#define FR_DDAG A(FR_Q)    // ‡
#define FR_COGR A(FR_S)    // Ò
#define FR_PDIF A(FR_D)    // ∂
#define FR_FHK  A(FR_F)    // ƒ
#define FR_FI   A(FR_G)    // ﬁ
#define FR_CIGR A(FR_H)    // Ì
#define FR_CIDI A(FR_J)    // Ï
#define FR_CEGR A(FR_K)    // È
#define FR_NOT  A(FR_L)    // ¬
#define FR_MICR A(FR_M)    // µ
#define FR_CUGR A(FR_LUGR) // Ù
// Row 4
#define FR_LTEQ A(FR_LABK) // ≤
#define FR_LSAQ A(FR_W)    // ‹
#define FR_AEQL A(FR_X)    // ≈
#define FR_COPY A(FR_C)    // ©
#define FR_LOZN A(FR_V)    // ◊
#define FR_SS   A(FR_B)    // ß
#define FR_TILD A(FR_N)    // ~ (dead)
#define FR_INFN A(FR_COMM) // ∞
#define FR_ELLP A(FR_SCLN) // …
#define FR_DIV  A(FR_COLN) // ÷
#define FR_NEQL A(FR_EQL)  // ≠

/* Shift+Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │ Ÿ │ ´ │ „ │   │   │ [ │ å │ » │ Û │ Á │   │ ] │ – │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │   │ Å │   │ ‚ │ ™ │   │ ª │ ï │   │ ∏ │   │ ¥ │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ Ω │ ∑ │ ∆ │ · │ ﬂ │ Î │ Í │ Ë │ | │ Ó │ ‰ │   │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │ ≥ │ › │ ⁄ │ ¢ │ √ │ ∫ │ ı │ ¿ │   │ \ │ ± │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define FR_CYDI S(A(FR_AT))   // Ÿ
#define FR_ACUT S(A(FR_AMPR)) // ´ (dead)
#define FR_DLQU S(A(FR_LEAC)) // „
#define FR_LBRC S(A(FR_LPRN)) // [
#define FR_LARI S(A(FR_SECT)) // å
#define FR_RDAQ S(A(FR_LEGR)) // »
#define FR_CUCI S(A(FR_EXLM)) // Û
#define FR_CAAC S(A(FR_LCCE)) // Á
#define FR_RBRC S(A(FR_RPRN)) // ]
#define FR_NDSH S(A(FR_MINS)) // –
// Row 2
#define FR_CARI S(A(FR_Z))    // Å
#define FR_SLQU S(A(FR_R))    // ‚
#define FR_TM   S(A(FR_T))    // ™
#define FR_FORD S(A(FR_U))    // ª
#define FR_LIDI S(A(FR_I))    // ï
#define FR_NARP S(A(FR_P))    // ∏
#define FR_YEN  S(A(FR_DLR))  // ¥
// Row 3
#define FR_OMEG S(A(FR_Q))    // Ω
#define FR_NARS S(A(FR_S))    // ∑
#define FR_INCR S(A(FR_D))    // ∆
#define FR_MDDT S(A(FR_F))    // ·
#define FR_FL   S(A(FR_G))    // ﬂ
#define FR_CICI S(A(FR_H))    // Î
#define FR_CIAC S(A(FR_J))    // Í
#define FR_CEDI S(A(FR_K))    // Ë
#define FR_PIPE S(A(FR_L))    // |
#define FR_COAC S(A(FR_M))    // Ó
#define FR_PERM S(A(FR_LUGR)) // ‰
// Row 4
#define FR_GTEQ S(A(FR_LABK)) // ≥
#define FR_RSAQ S(A(FR_W))    // ›
#define FR_FRSL S(A(FR_X))    // ⁄
#define FR_CENT S(A(FR_C))    // ¢
#define FR_SQRT S(A(FR_V))    // √
#define FR_INTG S(A(FR_B))    // ∫
#define FR_DLSI S(A(FR_N))    // ı
#define FR_IQUE S(A(FR_COMM)) // ¿
#define FR_BSLS S(A(FR_COLN)) // (backslash)
#define FR_PLMN S(A(FR_EQL))  // ±

// DEPRECATED
#define FR_AMP  FR_AMPR
#define FR_EACU FR_LEAC
#define FR_APOS FR_QUOT
#define FR_EGRV FR_LEGR
#define FR_CCED FR_LCCE
#define FR_AGRV FR_LAGR
#define FR_UGRV FR_LUGR
#define FR_LESS FR_LABK
#define FR_UMLT FR_DIAE
#define FR_GRTR FR_RABK
