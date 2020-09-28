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
 * │ + │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ / │ - │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ F │ G │ Ğ │ I │ O │ D │ R │ N │ H │ P │ Q │ W │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ U │ İ │ E │ A │ Ü │ T │ K │ M │ L │ Y │ Ş │ X │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ J │ Ö │ V │ C │ Ç │ Z │ S │ B │ . │ , │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define TR_PLUS KC_GRV  // +
#define TR_1    KC_1    // 1
#define TR_2    KC_2    // 2
#define TR_3    KC_3    // 3
#define TR_4    KC_4    // 4
#define TR_5    KC_5    // 5
#define TR_6    KC_6    // 6
#define TR_7    KC_7    // 7
#define TR_8    KC_8    // 8
#define TR_9    KC_9    // 9
#define TR_0    KC_0    // 0
#define TR_SLSH KC_MINS // /
#define TR_MINS KC_EQL  // -
// Row 2
#define TR_F    KC_Q    // F
#define TR_G    KC_W    // G
#define TR_GBRV KC_E    // Ğ
#define TR_I    KC_R    // I
#define TR_O    KC_T    // O
#define TR_D    KC_Y    // D
#define TR_R    KC_U    // R
#define TR_N    KC_I    // N
#define TR_H    KC_O    // H
#define TR_P    KC_P    // P
#define TR_Q    KC_LBRC // Q
#define TR_W    KC_RBRC // W
// Row 3
#define TR_U    KC_A    // U
#define TR_IDOT KC_S    // İ
#define TR_E    KC_D    // E
#define TR_A    KC_F    // A
#define TR_UDIA KC_G    // Ü
#define TR_T    KC_H    // T
#define TR_K    KC_J    // K
#define TR_M    KC_K    // M
#define TR_L    KC_L    // L
#define TR_Y    KC_SCLN // Y
#define TR_SCED KC_QUOT // Ş
#define TR_X    KC_NUHS // X
// Row 4
#define TR_LABK KC_NUBS // <
#define TR_J    KC_Z    // J
#define TR_ODIA KC_X    // Ö
#define TR_V    KC_C    // V
#define TR_C    KC_V    // C
#define TR_CCED KC_B    // Ç
#define TR_Z    KC_N    // Z
#define TR_S    KC_M    // S
#define TR_B    KC_COMM // B
#define TR_DOT  KC_DOT  // .
#define TR_COMM KC_SLSH // ,

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ * │ ! │ " │ ^ │ $ │ % │ & │ ' │ ( │ ) │ = │ ? │ _ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │   │ : │ ; │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define TR_ASTR S(TR_PLUS) // *
#define TR_EXLM S(TR_1)    // !
#define TR_DQUO S(TR_2)    // "
#define TR_CIRC S(TR_3)    // ^ (dead)
#define TR_DLR  S(TR_4)    // $
#define TR_PERC S(TR_5)    // %
#define TR_AMPR S(TR_6)    // &
#define TR_QUOT S(TR_7)    // '
#define TR_LPRN S(TR_8)    // (
#define TR_RPRN S(TR_9)    // )
#define TR_EQL  S(TR_0)    // =
#define TR_QUES S(TR_ASTR) // ?
#define TR_UNDS S(TR_MINS) // _
// Row 4
#define TR_RABK S(TR_LABK) // >
#define TR_COLN S(TR_DOT)  // :
#define TR_SCLN S(TR_COMM) // ;

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¬ │ ¹ │ ² │ # │ ¼ │ ½ │ ¾ │ { │ [ │ ] │ } │ \ │ | │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ @ │   │   │ ¶ │   │ ¥ │   │   │ Ø │ £ │ ¨ │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Æ │ ß │ € │   │   │ ₺ │   │   │   │ ´ │   │ ` │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │ « │ » │ ¢ │   │   │   │ µ │ × │ ÷ │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define TR_NOT  ALGR(TR_PLUS) // ¬
#define TR_SUP1 ALGR(TR_1)    // ¹
#define TR_SUP2 ALGR(TR_2)    // ²
#define TR_HASH ALGR(TR_3)    // #
#define TR_QRTR ALGR(TR_4)    // ¼
#define TR_HALF ALGR(TR_5)    // ½
#define TR_TQTR ALGR(TR_6)    // ¾
#define TR_LCBR ALGR(TR_7)    // {
#define TR_LBRC ALGR(TR_8)    // [
#define TR_RBRC ALGR(TR_9)    // ]
#define TR_RCBR ALGR(TR_0)    // }
#define TR_BSLS ALGR(TR_SLSH) // (backslash)
#define TR_PIPE ALGR(TR_MINS) // |
// Row 2
#define TR_AT   ALGR(TR_F)    // @
#define TR_PILC ALGR(TR_I)    // ¶
#define TR_YEN  ALGR(TR_D)    // ¥
#define TR_OSTR ALGR(TR_H)    // Ø
#define TR_PND  ALGR(TR_P)    // £
#define TR_DIAE ALGR(TR_Q)    // ¨ (dead)
#define TR_TILD ALGR(TR_W)    // ~ (dead)
// Row 3
#define TR_AE   ALGR(TR_U)    // Æ
#define TR_SS   ALGR(TR_IDOT) // ß
#define TR_EURO ALGR(TR_E)    // €
#define TR_LIRA ALGR(TR_T)    // ₺
#define TR_ACUT ALGR(TR_Y)    // ´ (dead)
#define TR_GRV  ALGR(TR_X)    // ` (dead)
// Row 4
#define TR_LDAQ ALGR(TR_J)    // «
#define TR_RDAQ ALGR(TR_ODIA) // »
#define TR_CENT ALGR(TR_V)    // ¢
#define TR_MICR ALGR(TR_S)    // µ
#define TR_MUL  ALGR(TR_B)    // ×
#define TR_DIV  ALGR(TR_DOT)  // ÷
#define TR_SHYP ALGR(TR_COMM) // (soft hyphen)

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │   │ ³ │ ¤ │   │   │   │   │   │   │ ¿ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │ ® │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │ § │   │ ª │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ¦ │   │   │ © │   │   │   │ º │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define TR_SUP3 S(ALGR(TR_3))    // ³
#define TR_CURR S(ALGR(TR_4))    // ¤
#define TR_IQUE S(ALGR(TR_SLSH)) // ¿
// Row 2
#define TR_REGD S(ALGR(TR_I)     // ®
// Row 3
#define TR_SECT S(ALGR(TR_IDOT)) // §
#define TR_FORD S(ALGR(TR_A))    // ª
// Row 4
#define TR_BRKP S(ALGR(TR_LABK)) // ¦
#define TR_COPY S(ALGR(TR_V))    // ©
#define TR_MORD S(ALGR(TR_S))    // º
