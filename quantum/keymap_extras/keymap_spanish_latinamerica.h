/* Copyright 2015-2016 Jack Humbert
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
 * │ | │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ ¿ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ ´ │ + │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ñ │ { │ } │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define ES_PIPE KC_GRV  // |
#define ES_1    KC_1    // 1
#define ES_2    KC_2    // 2
#define ES_3    KC_3    // 3
#define ES_4    KC_4    // 4
#define ES_5    KC_5    // 5
#define ES_6    KC_6    // 6
#define ES_7    KC_7    // 7
#define ES_8    KC_8    // 8
#define ES_9    KC_9    // 9
#define ES_0    KC_0    // 0
#define ES_QUOT KC_MINS // '
#define ES_IQUE KC_EQL  // ¿
// Row 2
#define ES_Q    KC_Q    // Q
#define ES_W    KC_W    // W
#define ES_E    KC_E    // E
#define ES_R    KC_R    // R
#define ES_T    KC_T    // T
#define ES_Y    KC_Y    // Y
#define ES_U    KC_U    // U
#define ES_I    KC_I    // I
#define ES_O    KC_O    // O
#define ES_P    KC_P    // P
#define ES_ACUT KC_LBRC // ´ (dead)
#define ES_PLUS KC_RBRC // +
// Row 3
#define ES_A    KC_A    // A
#define ES_S    KC_S    // S
#define ES_D    KC_D    // D
#define ES_F    KC_F    // F
#define ES_G    KC_G    // G
#define ES_H    KC_H    // H
#define ES_J    KC_J    // J
#define ES_K    KC_K    // K
#define ES_L    KC_L    // L
#define ES_NTIL KC_SCLN // Ñ
#define ES_LCBR KC_QUOT // {
#define ES_RCBR KC_NUHS // }
// Row 4
#define ES_LABK KC_NUBS // <
#define ES_Z    KC_Z    // Z
#define ES_X    KC_X    // X
#define ES_C    KC_C    // C
#define ES_V    KC_V    // V
#define ES_B    KC_B    // B
#define ES_N    KC_N    // N
#define ES_M    KC_M    // M
#define ES_COMM KC_COMM // ,
#define ES_DOT  KC_DOT  // .
#define ES_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ º │ ! │ " │ # │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ ¡ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ¨ │ * │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ [ │ ] │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define ES_MORD S(ES_PIPE) // º
#define ES_EXLM S(ES_1)    // !
#define ES_DQUO S(ES_2)    // "
#define ES_HASH S(ES_3)    // #
#define ES_DLR  S(ES_4)    // $
#define ES_PERC S(ES_5)    // %
#define ES_AMPR S(ES_6)    // &
#define ES_SLSH S(ES_7)    // /
#define ES_LPRN S(ES_8)    // (
#define ES_RPRN S(ES_9)    // )
#define ES_EQL  S(ES_0)    // =
#define ES_QUES S(ES_QUOT) // ?
#define ES_IEXL S(ES_IQUE) // ¿
// Row 2
#define ES_DIAE S(ES_ACUT) // ¨ (dead)
#define ES_ASTR S(ES_PLUS) // *
// Row 3
#define ES_LBRC S(ES_LCBR) // [
#define ES_RBRC S(ES_RCBR) // ]
// Row 4
#define ES_RABK S(ES_LABK) // >
#define ES_SCLN S(ES_COMM) // ;
#define ES_COLN S(ES_DOT)  // :
#define ES_UNDS S(ES_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¬ │ ¡ │ “ │ £ │ ¢ │ ∞ │ § │ ¶ │ • │ ª │ º │ \ │ ≠ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ @ │ ∑ │ € │ ® │ † │ ¥ │ ¨ │ ı │ ø │ π │ « │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │ ß │ ∂ │ ƒ │ © │   │   │   │ λ │ ~ │ ^ │ ` │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≤ │   │ ≈ │ ç │ √ │ ∫ │ ~ │ µ │   │ … │ – │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define ES_NOT  ALGR(ES_PIPE) // ¬
#define ES_IEXL ALGR(ES_1)    // ¡
#define ES_LDQU ALGR(ES_2)    // “
#define ES_PND  ALGR(ES_3)    // £
#define ES_CENT ALGR(ES_4)    // ¢
#define ES_INFN ALGR(ES_5)    // ∞
#define ES_SECT ALGR(ES_6)    // §
#define ES_PILC ALGR(ES_7)    // ¶
#define ES_BULT ALGR(ES_8)    // •
#define ES_FORD ALGR(ES_9)    // ª
#define ES_MORD ALGR(ES_0)    // º
#define ES_BSLS ALGR(ES_QUOT) // (backslash)
#define ES_NEQL ALGR(ES_IQUE) // ≠

// Row 2
#define ES_AT   ALGR(ES_Q)    // @
#define ES_NARS ALGR(ES_W)    // ∑
#define ES_EURO ALGR(ES_E)    // €
#define ES_REGD ALGR(ES_R)    // ®
#define ES_DAGG ALGR(ES_T)    // †
#define ES_YEN  ALGR(ES_Y)    // ¥
#define ES_DIAE ALGR(ES_U)    // ¨ (dead)
#define ES_DLSI ALGR(ES_I)    // ı
#define ES_OSTR ALGR(ES_O)    // ø
#define ES_PI   ALGR(ES_P)    // π
#define ES_LDAQ ALGR(ES_ACUT) // «
#define ES_TILD ALGR(ES_PLUS) // ~

// Row 3
#define ES_SS   ALGR(ES_S)    // ß
#define ES_PDIF ALGR(ES_D)    // ∂
#define ES_FHK  ALGR(ES_F)    // ƒ
#define ES_COPY ALGR(ES_G)    // ©
#define ES_LAMB ALGR(ES_L)    // λ
#define ES_TILD ALGR(ES_NTIL) // ~
#define ES_CIRC ALGR(ES_LCBR) // ^
#define ES_GRV  ALGR(ES_RCBR) // `

// Row 4
#define ES_LTEQ ALGR(ES_LABK) // ≤
#define ES_AEQL ALGR(ES_X)    // ≈
#define ES_CCED ALGR(ES_C)    // ç
#define ES_SQRT ALGR(ES_V)    // √
#define ES_INTG ALGR(ES_B)    // ∫
#define ES_TILD ALGR(ES_N)    // ~
#define ES_MICR ALGR(ES_M)    // µ
#define ES_ELLP ALGR(ES_DOT)  // …
#define ES_NDSH ALGR(ES_MINS) // –
