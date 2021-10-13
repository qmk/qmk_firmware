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
 * │ / │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ ^ │ Ç │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ È │ À │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ Ù │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ É │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CA_SLSH KC_GRV  // /
#define CA_1    KC_1    // 1
#define CA_2    KC_2    // 2
#define CA_3    KC_3    // 3
#define CA_4    KC_4    // 4
#define CA_5    KC_5    // 5
#define CA_6    KC_6    // 6
#define CA_7    KC_7    // 7
#define CA_8    KC_8    // 8
#define CA_9    KC_9    // 9
#define CA_0    KC_0    // 0
#define CA_MINS KC_MINS // -
#define CA_EQL  KC_EQL  // =
// Row 2
#define CA_Q    KC_Q    // Q
#define CA_W    KC_W    // W
#define CA_E    KC_E    // E
#define CA_R    KC_R    // R
#define CA_T    KC_T    // T
#define CA_Y    KC_Y    // Y
#define CA_U    KC_U    // U
#define CA_I    KC_I    // I
#define CA_O    KC_O    // O
#define CA_P    KC_P    // P
#define CA_CIRC KC_LBRC // ^ (dead)
#define CA_CCED KC_RBRC // Ç
// Row 3
#define CA_A    KC_A    // A
#define CA_S    KC_S    // S
#define CA_D    KC_D    // D
#define CA_F    KC_F    // F
#define CA_G    KC_G    // G
#define CA_H    KC_H    // H
#define CA_J    KC_J    // J
#define CA_K    KC_K    // K
#define CA_L    KC_L    // L
#define CA_SCLN KC_SCLN // ;
#define CA_EGRV KC_QUOT // É
#define CA_AGRV KC_NUHS // À
// Row 4
#define CA_UGRV KC_NUBS // Ù
#define CA_Z    KC_Z    // Z
#define CA_X    KC_X    // X
#define CA_C    KC_C    // C
#define CA_V    KC_V    // V
#define CA_B    KC_B    // B
#define CA_N    KC_N    // N
#define CA_M    KC_M    // M
#define CA_COMM KC_COMM // ,
#define CA_DOT  KC_DOT  // .
#define CA_EACU KC_SLSH // É

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ \ │ ! │ @ │ # │ $ │ % │ ? │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ¨ │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ : │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │ ' │ " │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CA_BSLS S(CA_SLSH) // (backslash)
#define CA_EXLM S(CA_1)    // !
#define CA_AT   S(CA_2)    // @
#define CA_HASH S(CA_3)    // #
#define CA_DLR  S(CA_4)    // $
#define CA_PERC S(CA_5)    // %
#define CA_QUES S(CA_6)    // ?
#define CA_AMPR S(CA_7)    // &
#define CA_ASTR S(CA_8)    // *
#define CA_LPRN S(CA_9)    // (
#define CA_RPRN S(CA_0)    // )
#define CA_UNDS S(CA_MINS) // _
#define CA_PLUS S(CA_EQL)  // +
// Row 2
#define CA_DIAE S(CA_CIRC) // ¨ (dead)
// Row 3
#define CA_COLN S(CA_SCLN) // :
// Row 4
#define CA_QUOT S(CA_COMM) // '
#define CA_DQUO S(CA_DOT)  // "

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ | │   │   │   │ ¤ │   │   │ { │ } │ [ │ ] │   │ ¬ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │   │ ` │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ ° │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │ « │ » │   │   │   │   │   │ < │ > │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CA_PIPE ALGR(CA_SLSH) // |
#define CA_CURR ALGR(CA_4)    // ¤
#define CA_LCBR ALGR(CA_7)    // {
#define CA_RCBR ALGR(CA_8)    // }
#define CA_LBRC ALGR(CA_9)    // [
#define CA_RBRC ALGR(CA_0)    // ]
#define CA_NOT  ALGR(CA_EQL)  // ¬
// Row 2
#define CA_EURO ALGR(CA_E)    // €
#define CA_GRV  ALGR(CA_CIRC) // ` (dead)
#define CA_DTIL ALGR(CA_CCED) // ~ (dead)
// Row 3
#define CA_DEG  ALGR(CA_SCLN) // °
// Row 4
#define CA_LDAQ ALGR(CA_Z)    // «
#define CA_RDAQ ALGR(CA_X)    // »
#define CA_LABK ALGR(CA_COMM) // <
#define CA_RABK ALGR(CA_DOT)  // >

/* Right Ctrl symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ¹ │ ² │ ³ │ ¼ │ ½ │ ¾ │   │   │   │   │   │ ¸ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Ω │ Ł │ Œ │ ¶ │ Ŧ │ ← │ ↓ │ → │ Ø │ Þ │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Æ │ ß │ Ð │   │ Ŋ │ Ħ │ Ĳ │ ĸ │ Ŀ │ ´ │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │ ¢ │ “ │ ” │ ŉ │ μ │ ― │ ˙ │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CA_SUP1 RCTL(CA_1)    // ¹
#define CA_SUP2 RCTL(CA_2)    // ²
#define CA_SUP3 RCTL(CA_3)    // ³
#define CA_QRTR RCTL(CA_4)    // ¼
#define CA_HALF RCTL(CA_5)    // ½
#define CA_TQTR RCTL(CA_6)    // ¾
#define CA_CEDL RCTL(CA_EQL)  // ¸ (dead)
// Row 2
#define CA_OMEG RCTL(CA_Q)    // Ω
#define CA_LSTR RCTL(CA_W)    // Ł
#define CA_OE   RCTL(CA_E)    // Œ
#define CA_PARA RCTL(CA_R)    // ¶
#define CA_TSTR RCTL(CA_T)    // Ŧ
#define CA_LARR RCTL(CA_Y)    // ←
#define CA_DARR RCTL(CA_U)    // ↓
#define CA_RARR RCTL(CA_I)    // →
#define CA_OSTR RCTL(CA_O)    // Ø
#define CA_THRN RCTL(CA_P)    // Þ
#define CA_TILD RCTL(CA_CCED) // ~
// Row 3
#define CA_AE   RCTL(CA_A)    // Æ
#define CA_SS   RCTL(CA_S)    // ß
#define CA_ETH  RCTL(CA_D)    // Ð
#define CA_ENG  RCTL(CA_G)    // Ŋ
#define CA_HSTR RCTL(CA_H)    // Ħ
#define CA_IJ   RCTL(CA_J)    // Ĳ
#define CA_KRA  RCTL(CA_K)    // ĸ
#define CA_LMDT RCTL(CA_L)    // Ŀ
#define CA_ACUT RCTL(CA_SCLN) // ´ (dead)
// Row 4
#define CA_CENT RCTL(CA_C)    // ¢
#define CA_LDQU RCTL(CA_V)    // “
#define CA_RDQU RCTL(CA_B)    // ”
#define CA_APSN RCTL(CA_N)    // ŉ
#define CA_MICR RCTL(CA_M)    // μ
#define CA_HRZB RCTL(CA_COMM) // ―
#define CA_DOTA RCTL(CA_DOT)  // ˙ (dead)

/* Shift+Right Ctrl symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ - │ ¡ │   │ £ │   │ ⅜ │ ⅝ │ ⅞ │ ™ │ ± │   │ ¿ │ ˛ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │ ® │   │ ¥ │ ↑ │ ı │   │   │ ° │ ¯ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │ § │   │ ª │   │   │   │   │   │ ˝ │ ˇ │ ˘ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ¦ │   │   │ © │ ‘ │ ’ │ ♪ │ º │ × │ ÷ │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CA_SHYP RCTL(S(CA_SLSH)) // ­ (soft hyphen)
#define CA_IEXL RCTL(S(CA_1))    // ¡
#define CA_PND  RCTL(S(CA_3))    // £
#define CA_TEIG RCTL(S(CA_5))    // ⅜
#define CA_FEIG RCTL(S(CA_6))    // ⅝
#define CA_SEIG RCTL(S(CA_7))    // ⅞
#define CA_TM   RCTL(S(CA_8))    // ™
#define CA_PLMN RCTL(S(CA_9))    // ±
#define CA_IQUE RCTL(S(CA_MINS)) // ¿
#define CA_OGON RCTL(S(CA_EQL))  // ˛ (dead)
// Row 2
#define CA_REGD RCTL(S(CA_R))    // ®
#define CA_YEN  RCTL(S(CA_Y))    // ¥
#define CA_UARR RCTL(S(CA_U))    // ↑
#define CA_DLSI RCTL(S(CA_I))    // ı
#define CA_RNGA RCTL(S(CA_CIRC)) // ° (dead)
#define CA_MACR RCTL(S(CA_CCED)) // ¯ (dead)
// Row 3
#define CA_SECT RCTL(S(CA_S))    // §
#define CA_FORD RCTL(S(CA_F))    // ª
#define CA_DACU RCTL(S(CA_SCLN)) // ˝ (dead)
#define CA_CARN RCTL(S(CA_EGRV)) // ˇ (dead)
#define CA_BREV RCTL(S(CA_AGRV)) // ˘ (dead)
// Row 4
#define CA_BRKP RCTL(S(CA_UGRV)) // ¦
#define CA_COPY RCTL(S(CA_C))    // ©
#define CA_LSQU RCTL(S(CA_V))    // ‘
#define CA_RSQU RCTL(S(CA_B))    // ’
#define CA_ENOT RCTL(S(CA_N))    // ♪
#define CA_MORD RCTL(S(CA_M))    // º
#define CA_MUL  RCTL(S(CA_COMM)) // ×
#define CA_DIV  RCTL(S(CA_DOT))  // ÷
