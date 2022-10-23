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
 * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ [ │ ] │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ ' │ , │ . │ P │ Y │ F │ G │ C │ R │ L │ / │ = │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ A │ O │ E │ U │ I │ D │ H │ T │ N │ S │ - │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ ; │ Q │ J │ K │ X │ B │ M │ W │ V │ Z │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DV_GRV  KC_GRV  // `
#define DV_1    KC_1    // 1
#define DV_2    KC_2    // 2
#define DV_3    KC_3    // 3
#define DV_4    KC_4    // 4
#define DV_5    KC_5    // 5
#define DV_6    KC_6    // 6
#define DV_7    KC_7    // 7
#define DV_8    KC_8    // 8
#define DV_9    KC_9    // 9
#define DV_0    KC_0    // 0
#define DV_LBRC KC_MINS // [
#define DV_RBRC KC_EQL  // ]
// Row 2
#define DV_QUOT KC_Q    // '
#define DV_COMM KC_W    // ,
#define DV_DOT  KC_E    // .
#define DV_P    KC_R    // P
#define DV_Y    KC_T    // Y
#define DV_F    KC_Y    // F
#define DV_G    KC_U    // G
#define DV_C    KC_I    // C
#define DV_R    KC_O    // R
#define DV_L    KC_P    // L
#define DV_SLSH KC_LBRC // /
#define DV_EQL  KC_RBRC // =
#define DV_BSLS KC_BSLS // (backslash)
// Row 3
#define DV_A    KC_A    // A
#define DV_O    KC_S    // O
#define DV_E    KC_D    // E
#define DV_U    KC_F    // U
#define DV_I    KC_G    // I
#define DV_D    KC_H    // D
#define DV_H    KC_J    // H
#define DV_T    KC_K    // T
#define DV_N    KC_L    // N
#define DV_S    KC_SCLN // S
#define DV_MINS KC_QUOT // -
// Row 4
#define DV_SCLN KC_Z    // ;
#define DV_Q    KC_X    // Q
#define DV_J    KC_C    // J
#define DV_K    KC_V    // K
#define DV_X    KC_B    // X
#define DV_B    KC_N    // B
#define DV_M    KC_M    // M
#define DV_W    KC_COMM // W
#define DV_V    KC_DOT  // V
#define DV_Z    KC_SLSH // Z

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ { │ } │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ " │ < │ > │   │   │   │   │   │   │   │ ? │ + │  |  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │ _ │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ : │   │   │   │   │   │   │   │   │   │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DV_TILD S(DV_GRV)  // ~
#define DV_EXLM S(DV_1)    // !
#define DV_AT   S(DV_2)    // @
#define DV_HASH S(DV_3)    // #
#define DV_DLR  S(DV_4)    // $
#define DV_PERC S(DV_5)    // %
#define DV_CIRC S(DV_6)    // ^
#define DV_AMPR S(DV_7)    // &
#define DV_ASTR S(DV_8)    // *
#define DV_LPRN S(DV_9)    // (
#define DV_RPRN S(DV_0)    // )
#define DV_LCBR S(DV_LBRC) // {
#define DV_RCBR S(DV_RBRC) // }
// Row 2
#define DV_DQUO S(DV_QUOT) // "
#define DV_LABK S(DV_COMM) // <
#define DV_RABK S(DV_DOT)  // >
#define DV_QUES S(DV_SLSH) // ?
#define DV_PLUS S(DV_EQL)  // +
#define DV_PIPE S(DV_BSLS) // |
// Row 3
#define DV_UNDS S(DV_MINS) // _
// Row 4
#define DV_COLN S(DV_SCLN) // :
