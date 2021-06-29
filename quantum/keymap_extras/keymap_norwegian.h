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
#define NWG_PIPE KC_GRV  // |
#define NWG_1    KC_1    // 1
#define NWG_2    KC_2    // 2
#define NWG_3    KC_3    // 3
#define NWG_4    KC_4    // 4
#define NWG_5    KC_5    // 5
#define NWG_6    KC_6    // 6
#define NWG_7    KC_7    // 7
#define NWG_8    KC_8    // 8
#define NWG_9    KC_9    // 9
#define NWG_0    KC_0    // 0
#define NWG_PLUS KC_MINS // +
#define NWG_BSLS KC_EQL  // (backslash)
// Row 2
#define NWG_Q    KC_Q    // Q
#define NWG_W    KC_W    // W
#define NWG_E    KC_E    // E
#define NWG_R    KC_R    // R
#define NWG_T    KC_T    // T
#define NWG_Y    KC_Y    // Y
#define NWG_U    KC_U    // U
#define NWG_I    KC_I    // I
#define NWG_O    KC_O    // O
#define NWG_P    KC_P    // P
#define NWG_ARNG KC_LBRC // Å
#define NWG_DIAE KC_RBRC // ¨ (dead)
// Row 3
#define NWG_A    KC_A    // A
#define NWG_S    KC_S    // S
#define NWG_D    KC_D    // D
#define NWG_F    KC_F    // F
#define NWG_G    KC_G    // G
#define NWG_H    KC_H    // H
#define NWG_J    KC_J    // J
#define NWG_K    KC_K    // K
#define NWG_L    KC_L    // L
#define NWG_OSTR KC_SCLN // Ø
#define NWG_AE   KC_QUOT // Æ
#define NWG_QUOT KC_NUHS // '
// Row 4
#define NWG_LABK KC_NUBS // <
#define NWG_Z    KC_Z    // Z
#define NWG_X    KC_X    // X
#define NWG_C    KC_C    // C
#define NWG_V    KC_V    // V
#define NWG_B    KC_B    // B
#define NWG_N    KC_N    // N
#define NWG_M    KC_M    // M
#define NWG_COMM KC_COMM // ,
#define NWG_DOT  KC_DOT  // .
#define NWG_MINS KC_SLSH // -

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
#define NWG_SECT S(NWG_PIPE) // §
#define NWG_EXLM S(NWG_1)    // !
#define NWG_DQUO S(NWG_2)    // "
#define NWG_HASH S(NWG_3)    // #
#define NWG_CURR S(NWG_4)    // ¤
#define NWG_PERC S(NWG_5)    // %
#define NWG_AMPR S(NWG_6)    // &
#define NWG_SLSH S(NWG_7)    // /
#define NWG_LPRN S(NWG_8)    // (
#define NWG_RPRN S(NWG_9)    // )
#define NWG_EQL  S(NWG_0)    // =
#define NWG_QUES S(NWG_PLUS) // ?
#define NWG_GRV  S(NWG_BSLS) // ` (dead)
// Row 2
#define NWG_CIRC S(NWG_DIAE) // ^ (dead)
// Row 3
#define NWG_ASTR S(NWG_QUOT) // *
// Row 4
#define NWG_RABK S(NWG_LABK) // >
#define NWG_SCLN S(NWG_COMM) // ;
#define NWG_COLN S(NWG_DOT)  // :
#define NWG_UNDS S(NWG_MINS) // _

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

#define NWG_AT   ALGR(NWG_2)    // @
#define NWG_PND  ALGR(NWG_3)    // £
#define NWG_DLR  ALGR(NWG_4)    // $
#define NWG_EURO ALGR(NWG_5)    // €
#define NWG_LCBR ALGR(NWG_7)    // {
#define NWG_LBRC ALGR(NWG_8)    // [
#define NWG_RBRC ALGR(NWG_9)    // ]
#define NWG_RCBR ALGR(NWG_0)    // }
#define NWG_ACUT ALGR(NWG_BSLS) // ´ (dead)
// Row 2
#define NWG_TILD ALGR(NWG_DIAE) // ~ (dead)
// Row 4
#define NWG_MICR ALGR(NWG_M)    // µ

// DEPRECATED
#define NWG_AM       NWG_ARNG
#define NWG_AA       NWG_ARNG
#define NWG_OSLH     NWG_OSTR
#define NWG_APOS     NWG_QUOT
#define NWG_LESS     NWG_LABK
#define NWG_QUO2     NWG_DQUO
#define NWG_BULT     NWG_CURR
#define NWG_GRTR     NWG_RABK
#define NWG_MU       NWG_MICR
// Norwegian macOS symbols
#define NWG_ACUT_MAC NWG_BSLS       // ´
#define NWG_APOS_MAC NWG_LABK       // '
#define NWG_AT_MAC   NWG_QUOT       // @
#define NWG_BSLS_MAC S(ALGR(NWG_7)) // (backslash)
#define NWG_DLR_MAC  S(NWG_4)       // $
#define NWG_GRV_MAC  ALGR(NWG_BSLS) // `
#define NWG_GRTR_MAC S(NWG_PIPE)    // >
#define NWG_LCBR_MAC S(ALGR(NWG_8)) // {
#define NWG_LESS_MAC NWG_PIPE       // <
#define NWG_PIPE_MAC ALGR(NWG_7)    // |
#define NWG_RCBR_MAC S(ALGR(NWG_9)) // }
