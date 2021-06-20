/* Copyright 2021
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
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ ' │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SE_SECT KC_GRV  // §
#define SE_1    KC_1    // 1
#define SE_2    KC_2    // 2
#define SE_3    KC_3    // 3
#define SE_4    KC_4    // 4
#define SE_5    KC_5    // 5
#define SE_6    KC_6    // 6
#define SE_7    KC_7    // 7
#define SE_8    KC_8    // 8
#define SE_9    KC_9    // 9
#define SE_0    KC_0    // 0
#define SE_PLUS KC_MINS // +
#define SE_ACUT KC_EQL  // ´ (dead)
// Row 2
#define SE_Q    KC_Q    // Q
#define SE_W    KC_W    // W
#define SE_E    KC_E    // E
#define SE_R    KC_R    // R
#define SE_T    KC_T    // T
#define SE_Y    KC_Y    // Y
#define SE_U    KC_U    // U
#define SE_I    KC_I    // I
#define SE_O    KC_O    // O
#define SE_P    KC_P    // P
#define SE_ARNG KC_LBRC // Å
#define SE_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define SE_A    KC_A    // A
#define SE_S    KC_S    // S
#define SE_D    KC_D    // D
#define SE_F    KC_F    // F
#define SE_G    KC_G    // G
#define SE_H    KC_H    // H
#define SE_J    KC_J    // J
#define SE_K    KC_K    // K
#define SE_L    KC_L    // L
#define SE_ODIA KC_SCLN // Ö
#define SE_ADIA KC_QUOT // Ä
#define SE_QUOT KC_NUHS // '
// Row 4
#define SE_LABK KC_NUBS // <
#define SE_Z    KC_Z    // Z
#define SE_X    KC_X    // X
#define SE_C    KC_C    // C
#define SE_V    KC_V    // V
#define SE_B    KC_B    // B
#define SE_N    KC_N    // N
#define SE_M    KC_M    // M
#define SE_COMM KC_COMM // ,
#define SE_DOT  KC_DOT  // .
#define SE_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │ ! │ " │ # │ € │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
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
#define SE_DEG S(SE_SECT)  // °
#define SE_EXLM S(SE_1)    // !
#define SE_DQUO S(SE_2)    // "
#define SE_HASH S(SE_3)    // #
#define SE_CURR S(SE_4)    // €
#define SE_PERC S(SE_5)    // %
#define SE_AMPR S(SE_6)    // &
#define SE_SLSH S(SE_7)    // /
#define SE_LPRN S(SE_8)    // (
#define SE_RPRN S(SE_9)    // )
#define SE_EQL  S(SE_0)    // =
#define SE_QUES S(SE_PLUS) // ?
#define SE_GRV  S(SE_ACUT) // `
// Row 2
#define SE_CIRC S(SE_DIAE) // ^ (dead)
// Row 3
#define SE_ASTR S(SE_QUOT) // *
// Row 4
#define SE_RABK S(SE_LABK) // >
#define SE_SCLN S(SE_COMM) // ;
#define SE_COLN S(SE_DOT)  // :
#define SE_UNDS S(SE_MINS) // _

/* Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¶ │ © │ @ │ £ │ $ │ ∞ │   │ | │ [ │ ] │ ≈ │ ± │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ • │ Ω │ é │ ® │ † │ µ │ ü │ ı │ œ │ π │ ˙ │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │  │ ß │ ∂ │ ƒ │ ¸ │ ˛ │ √ │ ª │ ﬁ │ ø │ æ │ ™ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≤ │ ÷ │   │ ç │ ‹ │ › │ ‘ │ ’ │ ‚ │ … │ – │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1 
#define SE_PILC A(SE_SECT) // ¶
#define SE_COPY A(SE_1)    // ©
#define SE_AT   A(SE_2)    // @
#define SE_PND  A(SE_3)    // £
#define SE_DLR  A(SE_4)    // $
#define SE_INFN A(SE_5)    // ∞
#define SE_PIPE A(SE_7)    // |
#define SE_LBRC A(SE_8)    // [
#define SE_RBRC A(SE_9)    // ]
#define SE_AEQL A(SE_0)    // ≈
#define SE_PLMN A(SE_PLUS) // ±
// Row 2
#define SE_BULT A(SE_Q)    // •
#define SE_OMEG A(SE_W)    // Ω
#define SE_EACU A(SE_E)    // é
#define SE_REGD A(SE_R)    // ®
#define SE_DAGG A(SE_T)    // †
#define SE_MICR A(SE_Y)    // µ
#define SE_UDIA A(SE_U)    // ü
#define SE_DLSI A(SE_I)    // ı
#define SE_OE   A(SE_O)    // œ
#define SE_PI   A(SE_P)    // π
#define SE_DOTA A(SE_ARNG) // ˙
#define SE_TILD A(SE_DIAE) // ~ (dead)
// Row 3
#define SE_APPL A(SE_A)    //  (Apple logo)
#define SE_SS   A(SE_S)    // ß
#define SE_PDIF A(SE_D)    // ∂
#define SE_FHK  A(SE_F)    // ƒ
#define SE_CEDL A(SE_G)    // ¸
#define SE_OGON A(SE_H)    // ˛
#define SE_SQRT A(SE_J)    // √
#define SE_FORD A(SE_K)    // ª
#define SE_FI   A(SE_L)    // ﬁ
#define SE_OSTR A(SE_ODIA) // ø
#define SE_AE   A(SE_ADIA) // æ
#define SE_TM   A(SE_QUOT) // ™
// Row 4
#define SE_LTEQ A(SE_LABK) // ≤
#define SE_DIV  A(SE_Z)    // ÷
#define SE_CCCE A(SE_C)    // ç
#define SE_LSAQ A(SE_V)    // ‹
#define SE_RSAQ A(SE_B)    // ›
#define SE_LSQU A(SE_N)    // ‘
#define SE_RSQU A(SE_M)    // ’
#define SE_SLQU A(SE_COMM) // ‚
#define SE_ELLP A(SE_DOT)  // …
#define SE_NDSH A(SE_MINS) // –

/* Shift+Alted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │   │ ¡ │   │ ¥ │ ¢ │ ‰ │   │ \ │ { │ } │ ≠ │ ¿ │   │     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬───┤
 * │     │   │   │   │   │ ‡ │   │   │   │   │   │ ˚ │   │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐  │
 * │      │ ◊ │ ∑ │ ∆ │ ∫ │ ¯ │ ˘ │ ¬ │ º │   │   │   │   │  │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴──┤
 * │    │   │ ⁄ │ ˇ │   │ « │ » │ “ │ ” │ „ │ · │ — │        │
 * ├────┴┬──┴─┬─┴───┼───┴───┴───┴───┴───┴───┼───┴─┬─┴──┬─────┤
 * │     │    │     │                       │     │    │     │
 * └─────┴────┴─────┴───────────────────────┴─────┴────┴─────┘
 */
// Row 1
#define SE_IEXL S(A(SE_1))    // ¡
#define SE_YEN  S(A(SE_3))    // ¥
#define SE_CENT S(A(SE_4))    // ¢
#define SE_PERM S(A(SE_5))    // ‰
#define SE_BSLS S(A(SE_7))    // (backslash)
#define SE_LCBR S(A(SE_8))    // {
#define SE_RCBR S(A(SE_9))    // }
#define SE_NEQL S(A(SE_0))    // ≠
#define SE_IQUE S(A(SE_PLUS)) // ¿
// Row 2
#define SE_DDAG S(A(SE_T))    // ‡
#define SE_RNGA S(A(SE_ARNG)) // ˚
// Row 3
#define SE_LOZN S(A(SE_A))    // ◊
#define SE_NARS S(A(SE_S))    // ∑
#define SE_INCR S(A(SE_D))    // ∆
#define SE_INTG S(A(SE_F))    // ∫
#define SE_MACR S(A(SE_G))    // ¯
#define SE_BREV S(A(SE_H))    // ˘
#define SE_NOT  S(A(SE_J))    // ¬
#define SE_MORD S(A(SE_K))    // º
// Row 4
#define SE_FRSL S(A(SE_Z))    // ⁄
#define SE_CARN S(A(SE_X))    // ˇ
#define SE_LDAQ S(A(SE_V))    // «
#define SE_RDAQ S(A(SE_B))    // »
#define SE_LDQU S(A(SE_N))    // “
#define SE_RDQU S(A(SE_M))    // ”
#define SE_DLQU S(A(SE_COMM)) // „
#define SE_MDDT S(A(SE_DOT))  // ·
#define SE_MDSH S(A(SE_MINS)) // —

