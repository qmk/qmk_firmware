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
 * │ ˇ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Ü │ Õ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ ' │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define EE_CARN KC_GRV  // ˇ (dead)
#define EE_1    KC_1    // 1
#define EE_2    KC_2    // 2
#define EE_3    KC_3    // 3
#define EE_4    KC_4    // 4
#define EE_5    KC_5    // 5
#define EE_6    KC_6    // 6
#define EE_7    KC_7    // 7
#define EE_8    KC_8    // 8
#define EE_9    KC_9    // 9
#define EE_0    KC_0    // 0
#define EE_PLUS KC_MINS // +
#define EE_ACUT KC_EQL  // ´ (dead)
// Row 2
#define EE_Q    KC_Q    // Q
#define EE_W    KC_W    // W
#define EE_E    KC_E    // E
#define EE_R    KC_R    // R
#define EE_T    KC_T    // T
#define EE_Y    KC_Y    // Y
#define EE_U    KC_U    // U
#define EE_I    KC_I    // I
#define EE_O    KC_O    // O
#define EE_P    KC_P    // P
#define EE_UDIA KC_LBRC // Ü
#define EE_OTIL KC_RBRC // Õ
// Row 3
#define EE_A    KC_A    // A
#define EE_S    KC_S    // S
#define EE_D    KC_D    // D
#define EE_F    KC_F    // F
#define EE_G    KC_G    // G
#define EE_H    KC_H    // H
#define EE_J    KC_J    // J
#define EE_K    KC_K    // K
#define EE_L    KC_L    // L
#define EE_ODIA KC_SCLN // Ö
#define EE_ADIA KC_QUOT // Ä
#define EE_QUOT KC_NUHS // '
// Row 4
#define EE_LABK KC_NUBS // <
#define EE_Z    KC_Z    // Z
#define EE_X    KC_X    // X
#define EE_C    KC_C    // C
#define EE_V    KC_V    // V
#define EE_B    KC_B    // B
#define EE_N    KC_N    // N
#define EE_M    KC_M    // M
#define EE_COMM KC_COMM // ,
#define EE_DOT  KC_DOT  // .
#define EE_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ " │ # │ ¤ │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ * │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define EE_TILD S(EE_CARN) // ~ (dead)
#define EE_EXLM S(EE_1)    // !
#define EE_DQUO S(EE_2)    // "
#define EE_HASH S(EE_3)    // #
#define EE_CURR S(EE_4)    // ¤
#define EE_PERC S(EE_5)    // %
#define EE_AMPR S(EE_6)    // &
#define EE_SLSH S(EE_7)    // /
#define EE_LPRN S(EE_8)    // (
#define EE_RPRN S(EE_9)    // )
#define EE_EQL  S(EE_0)    // =
#define EE_QUES S(EE_PLUS) // ?
#define EE_GRV  S(EE_ACUT) // ` (dead)
// Row 3
#define EE_ASTR S(EE_QUOT) // *
// Row 4
#define EE_RABK S(EE_LABK) // >
#define EE_SCLN S(EE_COMM) // ;
#define EE_COLN S(EE_DOT)  // :
#define EE_UNDS S(EE_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ @ │ £ │ $ │ € │   │ { │ [ │ ] │ } │ \ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ § │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │ š │   │   │   │   │   │   │   │   │ ^ │ ½ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │ ž │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define EE_AT   ALGR(EE_2)    // @
#define EE_PND  ALGR(EE_3)    // £
#define EE_DLR  ALGR(EE_4)    // $
#define EE_EURO ALGR(EE_5)    // €
#define EE_LCBR ALGR(EE_7)    // {
#define EE_LBRC ALGR(EE_8)    // [
#define EE_RBRC ALGR(EE_9)    // ]
#define EE_RCBR ALGR(EE_0)    // }
#define EE_BSLS ALGR(EE_PLUS) // (backslash)
// Row 2
#define EE_SECT ALGR(EE_OTIL) // §
// Row 3
#define EE_SCAR ALGR(EE_S)    // š
#define EE_CIRC ALGR(EE_ADIA) // ^ (dead)
#define EE_HALF ALGR(EE_QUOT) // ½
// Row 4
#define EE_PIPE ALGR(EE_LABK) // |
#define EE_ZCAR ALGR(EE_Z)    // ž
