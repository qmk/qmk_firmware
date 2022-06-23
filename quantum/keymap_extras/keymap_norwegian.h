/* Copyright 2016 Jack Humbert
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
 * │ | │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ \ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ø │ Æ │ ' │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define NRW_PIPE KC_GRV  // |
#define NRW_1    KC_1    // 1
#define NRW_2    KC_2    // 2
#define NRW_3    KC_3    // 3
#define NRW_4    KC_4    // 4
#define NRW_5    KC_5    // 5
#define NRW_6    KC_6    // 6
#define NRW_7    KC_7    // 7
#define NRW_8    KC_8    // 8
#define NRW_9    KC_9    // 9
#define NRW_0    KC_0    // 0
#define NRW_PLUS KC_MINS // +
#define NRW_BSLS KC_EQL  // (backslash)
// Row 2
#define NRW_Q    KC_Q    // Q
#define NRW_W    KC_W    // W
#define NRW_E    KC_E    // E
#define NRW_R    KC_R    // R
#define NRW_T    KC_T    // T
#define NRW_Y    KC_Y    // Y
#define NRW_U    KC_U    // U
#define NRW_I    KC_I    // I
#define NRW_O    KC_O    // O
#define NRW_P    KC_P    // P
#define NRW_ARNG KC_LBRC // Å
#define NRW_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define NRW_A    KC_A    // A
#define NRW_S    KC_S    // S
#define NRW_D    KC_D    // D
#define NRW_F    KC_F    // F
#define NRW_G    KC_G    // G
#define NRW_H    KC_H    // H
#define NRW_J    KC_J    // J
#define NRW_K    KC_K    // K
#define NRW_L    KC_L    // L
#define NRW_OSTR KC_SCLN // Ø
#define NRW_AE   KC_QUOT // Æ
#define NRW_QUOT KC_NUHS // '
// Row 4
#define NRW_LABK KC_NUBS // <
#define NRW_Z    KC_Z    // Z
#define NRW_X    KC_X    // X
#define NRW_C    KC_C    // C
#define NRW_V    KC_V    // V
#define NRW_B    KC_B    // B
#define NRW_N    KC_N    // N
#define NRW_M    KC_M    // M
#define NRW_COMM KC_COMM // ,
#define NRW_DOT  KC_DOT  // .
#define NRW_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ § │ ! │ " │ # │ ¤ │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
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
#define NRW_SECT S(NRW_PIPE) // §
#define NRW_EXLM S(NRW_1)    // !
#define NRW_DQUO S(NRW_2)    // "
#define NRW_HASH S(NRW_3)    // #
#define NRW_CURR S(NRW_4)    // ¤
#define NRW_PERC S(NRW_5)    // %
#define NRW_AMPR S(NRW_6)    // &
#define NRW_SLSH S(NRW_7)    // /
#define NRW_LPRN S(NRW_8)    // (
#define NRW_RPRN S(NRW_9)    // )
#define NRW_EQL  S(NRW_0)    // =
#define NRW_QUES S(NRW_PLUS) // ?
#define NRW_GRV  S(NRW_BSLS) // ` (dead)
// Row 2
#define NRW_CIRC S(NRW_DIAE) // ^ (dead)
// Row 3
#define NRW_ASTR S(NRW_QUOT) // *
// Row 4
#define NRW_RABK S(NRW_LABK) // >
#define NRW_SCLN S(NRW_COMM) // ;
#define NRW_COLN S(NRW_DOT)  // :
#define NRW_UNDS S(NRW_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ @ │ £ │ $ │ € │   │ { │ [ │ ] │ } │   │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │ µ │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define NRW_AT   ALGR(NRW_2)    // @
#define NRW_PND  ALGR(NRW_3)    // £
#define NRW_DLR  ALGR(NRW_4)    // $
#define NRW_EURO ALGR(NRW_5)    // €
#define NRW_LCBR ALGR(NRW_7)    // {
#define NRW_LBRC ALGR(NRW_8)    // [
#define NRW_RBRC ALGR(NRW_9)    // ]
#define NRW_RCBR ALGR(NRW_0)    // }
#define NRW_ACUT ALGR(NRW_BSLS) // ´ (dead)
// Row 2
#define NRW_TILD ALGR(NRW_DIAE) // ~ (dead)
// Row 4
#define NRW_MICR ALGR(NRW_M)    // µ

// DEPRECATED
#define NRW_AM       NRW_ARNG
#define NRW_AA       NRW_ARNG
#define NRW_OSLH     NRW_OSTR
#define NRW_APOS     NRW_QUOT
#define NRW_LESS     NRW_LABK
#define NRW_QUO2     NRW_DQUO
#define NRW_BULT     NRW_CURR
#define NRW_GRTR     NRW_RABK
#define NRW_MU       NRW_MICR
// Norwegian macOS symbols
#define NRW_ACUT_MAC NRW_BSLS       // ´
#define NRW_APOS_MAC NRW_LABK       // '
#define NRW_AT_MAC   NRW_QUOT       // @
#define NRW_BSLS_MAC S(ALGR(NRW_7)) // (backslash)
#define NRW_DLR_MAC  S(NRW_4)       // $
#define NRW_GRV_MAC  ALGR(NRW_BSLS) // `
#define NRW_GRTR_MAC S(NRW_PIPE)    // >
#define NRW_LCBR_MAC S(ALGR(NRW_8)) // {
#define NRW_LESS_MAC NRW_PIPE       // <
#define NRW_PIPE_MAC ALGR(NRW_7)    // |
#define NRW_RCBR_MAC S(ALGR(NRW_9)) // }
