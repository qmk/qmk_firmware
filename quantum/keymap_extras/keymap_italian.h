/* Copyright 2015-2016 Matthias Schmidtt
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
 * │ \ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │ ì │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ è │ + │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ò │ à │ ù │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IT_BSLS KC_GRV  // (backslash)
#define IT_1    KC_1    // 1
#define IT_2    KC_2    // 2
#define IT_3    KC_3    // 3
#define IT_4    KC_4    // 4
#define IT_5    KC_5    // 5
#define IT_6    KC_6    // 6
#define IT_7    KC_7    // 7
#define IT_8    KC_8    // 8
#define IT_9    KC_9    // 9
#define IT_0    KC_0    // 0
#define IT_QUOT KC_MINS // '
#define IT_IGRV KC_EQL  // ì
// Row 2
#define IT_Q    KC_Q    // Q
#define IT_W    KC_W    // W
#define IT_E    KC_E    // E
#define IT_R    KC_R    // R
#define IT_T    KC_T    // T
#define IT_Y    KC_Y    // Y
#define IT_U    KC_U    // U
#define IT_I    KC_I    // I
#define IT_O    KC_O    // O
#define IT_P    KC_P    // P
#define IT_EGRV KC_LBRC // è
#define IT_PLUS KC_RBRC // +
// Row 3
#define IT_A    KC_A    // A
#define IT_S    KC_S    // S
#define IT_D    KC_D    // D
#define IT_F    KC_F    // F
#define IT_G    KC_G    // G
#define IT_H    KC_H    // H
#define IT_J    KC_J    // J
#define IT_K    KC_K    // K
#define IT_L    KC_L    // L
#define IT_OGRV KC_SCLN // ò
#define IT_AGRV KC_QUOT // à
#define IT_UGRV KC_NUHS // ù
// Row 4
#define IT_LABK KC_NUBS // <
#define IT_Z    KC_Z    // Z
#define IT_X    KC_X    // X
#define IT_C    KC_C    // C
#define IT_B    KC_B    // B
#define IT_V    KC_V    // V
#define IT_N    KC_N    // N
#define IT_M    KC_M    // M
#define IT_COMM KC_COMM // ,
#define IT_DOT  KC_DOT  // .
#define IT_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ | │ ! │ " │ £ │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ ^ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ é │ * │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ ç │ ° │ § │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define IT_PIPE S(IT_BSLS) // |
#define IT_EXLM S(IT_1)    // !
#define IT_DQUO S(IT_2)    // "
#define IT_PND  S(IT_3)    // £
#define IT_DLR  S(IT_4)    // $
#define IT_PERC S(IT_5)    // %
#define IT_AMPR S(IT_6)    // &
#define IT_SLSH S(IT_7)    // /
#define IT_LPRN S(IT_8)    // (
#define IT_RPRN S(IT_9)    // )
#define IT_EQL  S(IT_0)    // =
#define IT_QUES S(IT_QUOT) // ?
#define IT_CIRC S(IT_IGRV) // ^
// Row 2
#define IT_EACU S(IT_EGRV) // é
#define IT_ASTR S(IT_PLUS) // *
// Row 3
#define IT_CCED S(IT_OGRV) // ç
#define IT_DEG  S(IT_AGRV) // °
#define IT_SECT S(IT_UGRV) // §
// Row 4
#define IT_RABK S(IT_LABK) // >
#define IT_COLN S(IT_DOT)  // :
#define IT_SCLN S(IT_COMM) // ;
#define IT_UNDS S(IT_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │   │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ @ │ # │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 2
#define IT_EURO ALGR(IT_E)       // €
#define IT_LBRC ALGR(IT_EGRV)    // [
#define IT_RBRC ALGR(IT_PLUS)    // ]
// Row 3
#define IT_AT   ALGR(IT_OGRV)    // @
#define IT_HASH ALGR(IT_AGRV)    // #

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 2
#define IT_LCBR S(ALGR(IT_EGRV)) // {
#define IT_RCBR S(ALGR(IT_PLUS)) // }

// DEPRECATED
#define IT_BKSL IT_BSLS
#define IT_QUOT IT_APOS
#define IT_IACC IT_IGRV
#define IT_EACC IT_EGRV
#define IT_OACC IT_OGRV
#define IT_AACC IT_AGRV
#define IT_UACC IT_UGRV
#define IT_LESS IT_LABK
#define IT_DQOT IT_DQUO
#define IT_STRL IT_PND
#define IT_QST  IT_QUES
#define IT_CRC  IT_CIRC
#define IT_MORE IT_RABK
#define IT_SHRP IT_HASH

#define IT_X_PLUS X_RBRACKET
#define IT_ACUT
