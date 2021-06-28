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
 * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ´ │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define US_DGRV KC_GRV  // ` (dead)
#define US_1    KC_1    // 1
#define US_2    KC_2    // 2
#define US_3    KC_3    // 3
#define US_4    KC_4    // 4
#define US_5    KC_5    // 5
#define US_6    KC_6    // 6
#define US_7    KC_7    // 7
#define US_8    KC_8    // 8
#define US_9    KC_9    // 9
#define US_0    KC_0    // 0
#define US_MINS KC_MINS // -
#define US_EQL  KC_EQL  // =
// Row 2
#define US_Q    KC_Q    // Q
#define US_W    KC_W    // W
#define US_E    KC_E    // E
#define US_R    KC_R    // R
#define US_T    KC_T    // T
#define US_Y    KC_Y    // Y
#define US_U    KC_U    // U
#define US_I    KC_I    // I
#define US_O    KC_O    // O
#define US_P    KC_P    // P
#define US_LBRC KC_LBRC // [
#define US_RBRC KC_RBRC // ]
#define US_BSLS KC_BSLS // (backslash)
// Row 3
#define US_A    KC_A    // A
#define US_S    KC_S    // S
#define US_D    KC_D    // D
#define US_F    KC_F    // F
#define US_G    KC_G    // G
#define US_H    KC_H    // H
#define US_J    KC_J    // J
#define US_K    KC_K    // K
#define US_L    KC_L    // L
#define US_SCLN KC_SCLN // ;
#define US_ACUT KC_QUOT // ´ (dead)
// Row 4
#define US_Z    KC_Z    // Z
#define US_X    KC_X    // X
#define US_C    KC_C    // C
#define US_V    KC_V    // V
#define US_B    KC_B    // B
#define US_N    KC_N    // N
#define US_M    KC_M    // M
#define US_COMM KC_COMM // ,
#define US_DOT  KC_DOT  // .
#define US_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │  |  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │ : │ ¨ │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define US_DTIL S(US_DGRV) // ~ (dead)
#define US_EXLM S(US_1)    // !
#define US_AT   S(US_2)    // @
#define US_HASH S(US_3)    // #
#define US_DLR  S(US_4)    // $
#define US_PERC S(US_5)    // %
#define US_DCIR S(US_6)    // ^ (dead)
#define US_AMPR S(US_7)    // &
#define US_ASTR S(US_8)    // *
#define US_LPRN S(US_9)    // (
#define US_RPRN S(US_0)    // )
#define US_UNDS S(US_MINS) // _
#define US_PLUS S(US_EQL)  // +
// Row 2
#define US_LCBR S(US_LBRC) // {
#define US_RCBR S(US_RBRC) // }
#define US_PIPE S(US_BSLS) // |
// Row 3
#define US_COLN S(US_SCLN) // :
#define US_DIAE S(US_ACUT) // ¨ (dead)
// Row 4
#define US_LABK S(US_COMM) // <
#define US_RABK S(US_DOT)  // >
#define US_QUES S(US_SLSH) // ?

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ¡ │ ² │ ³ │ ¤ │ € │ ¼ │ ½ │ ¾ │ ‘ │ ’ │ ¥ │ × │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Ä │ Å │ É │ ® │ Þ │ Ü │ Ú │ Í │ Ó │ Ö │ « │ » │  ¬  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ Á │ ß │ Ð │   │   │   │   │   │ Ø │ ¶ │ ´ │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ Æ │   │ © │   │   │ Ñ │ µ │ Ç │   │ ¿ │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define US_IEXL ALGR(US_1)    // ¡
#define US_SUP2 ALGR(US_2)    // ²
#define US_SUP3 ALGR(US_3)    // ³
#define US_CURR ALGR(US_4)    // ¤
#define US_EURO ALGR(US_5)    // €
#define US_QRTR ALGR(US_6)    // ¼
#define US_HALF ALGR(US_7)    // ½
#define US_TQTR ALGR(US_8)    // ¾
#define US_LSQU ALGR(US_9)    // ‘
#define US_RSQU ALGR(US_0)    // ’
#define US_YEN  ALGR(US_MINS) // ¥
#define US_MUL  ALGR(US_EQL)  // ×
// Row 2
#define US_ADIA ALGR(US_Q)    // Ä
#define US_ARNG ALGR(US_W)    // Å
#define US_EACU ALGR(US_E)    // É
#define US_REGD ALGR(US_R)    // ®
#define US_THRN ALGR(US_T)    // Þ
#define US_UDIA ALGR(US_Y)    // Ü
#define US_UACU ALGR(US_U)    // Ú
#define US_IACU ALGR(US_I)    // Í
#define US_OACU ALGR(US_O)    // Ó
#define US_ODIA ALGR(US_P)    // Ö
#define US_LDAQ ALGR(US_LBRC) // «
#define US_RDAQ ALGR(US_RBRC) // »
#define US_NOT  ALGR(US_BSLS) // ¬
// Row 3
#define US_AACU ALGR(US_A)    // Á
#define US_SS   ALGR(US_S)    // ß
#define US_ETH  ALGR(US_D)    // Ð
#define US_OSTR ALGR(US_L)    // Ø
#define US_PILC ALGR(US_SCLN) // ¶
#define US_NDAC ALGR(US_ACUT) // ´
// Row 4
#define US_AE   ALGR(US_Z)    // Æ
#define US_COPY ALGR(US_C)    // ©
#define US_NTIL ALGR(US_N)    // Ñ
#define US_MICR ALGR(US_M)    // µ
#define US_CCED ALGR(US_COMM) // Ç
#define US_IQUE ALGR(US_SLSH) // ¿

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ¹ │   │   │ £ │   │   │   │   │   │   │   │ ÷ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │  ¦  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │ § │   │   │   │   │   │   │   │ ° │ ¨ │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │ ¢ │   │   │   │   │   │   │   │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define US_SUP1 S(ALGR(US_1))    // ¹
#define US_PND  S(ALGR(US_4))    // £
#define US_DIV  S(ALGR(US_EQL))  // ÷
// Row 2
#define US_BRKP S(ALGR(US_BSLS)) // ¦
// Row 3
#define US_SECT S(ALGR(US_S))    // §
#define US_DEG  S(ALGR(US_SCLN)) // °
#define US_NDDR S(ALGR(US_ACUT)) // ¨
// Row 4
#define US_CENT S(ALGR(US_C))    // ¢
