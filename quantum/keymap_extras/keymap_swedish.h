/* Copyright 2017 Andreas Lindhé
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
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ ' │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
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
 * │ ½ │ ! │ " │ # │ ¤ │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ^ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ * │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SE_HALF S(SE_SECT) // ½
#define SE_EXLM S(SE_1)    // !
#define SE_DQUO S(SE_2)    // "
#define SE_HASH S(SE_3)    // #
#define SE_CURR S(SE_4)    // ¤
#define SE_PERC S(SE_5)    // %
#define SE_AMPR S(SE_6)    // &
#define SE_SLSH S(SE_7)    // /
#define SE_LPRN S(SE_8)    // (
#define SE_RPRN S(SE_9)    // )
#define SE_EQL  S(SE_0)    // =
#define SE_QUES S(SE_PLUS) // ?
#define SE_GRV  S(SE_ACUT) // ` (dead)
// Row 2
#define SE_CIRC S(SE_DIAE) // ^ (dead)
// Row 3
#define SE_ASTR S(SE_QUOT) // *
// Row 4
#define SE_RABK S(SE_LABK) // >
#define SE_SCLN S(SE_COMM) // ;
#define SE_COLN S(SE_DOT)  // :
#define SE_UNDS S(SE_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ @ │ £ │ $ │ € │   │ { │ [ │ ] │ } │ \ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │   │   │   │   │   │   │ µ │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define SE_AT   ALGR(SE_2)    // @
#define SE_PND  ALGR(SE_3)    // £
#define SE_DLR  ALGR(SE_4)    // $
#define SE_EURO ALGR(SE_5)    // €
#define SE_LCBR ALGR(SE_7)    // {
#define SE_LBRC ALGR(SE_8)    // [
#define SE_RBRC ALGR(SE_9)    // ]
#define SE_RCBR ALGR(SE_0)    // }
#define SE_BSLS ALGR(SE_PLUS) // (backslash)
// Row 2
#define SE_TILD ALGR(SE_DIAE) // ~ (dead)
// Row 4
#define SE_PIPE ALGR(SE_LABK) // |
#define SE_MICR ALGR(SE_M)    // µ

// DEPRECATED
#include "keymap_nordic.h"

#undef  NO_AE
#undef  NO_CIRC
#undef  NO_OSLH

#define NO_AE   SE_AE
#define NO_CIRC SE_CIRC
#define NO_OSLH SE_ODIA
#define NO_AA   SE_ARNG
#define NO_ASTR SE_ASTR
// Swedish macOS symbols (not vetted)
#define NO_ACUT_MAC SE_ACUT
#define NO_APOS_MAC SE_LABK
#define NO_AT_MAC   SE_ADIA
#define NO_BSLS_MAC S(SE_LCBR)
#define NO_DLR_MAC  SE_CURR
#define NO_GRV_MAC  SE_BSLS
#define NO_GRTR_MAC SE_HALF
#define NO_LCBR_MAC S(SE_LBRC)
#define NO_LESS_MAC SE_SECT
#define NO_PIPE_MAC SE_LCBR
#define NO_RCBR_MAC S(SE_RBRC)
