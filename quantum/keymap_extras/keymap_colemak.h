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
 * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ F │ P │ G │ J │ L │ U │ Y │ ; │ [ │ ] │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ A │ R │ S │ T │ D │ H │ N │ E │ I │ O │ ' │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ Z │ X │ C │ V │ B │ K │ M │ , │ . │ / │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CM_GRV  KC_GRV  // `
#define CM_1    KC_1    // 1
#define CM_2    KC_2    // 2
#define CM_3    KC_3    // 3
#define CM_4    KC_4    // 4
#define CM_5    KC_5    // 5
#define CM_6    KC_6    // 6
#define CM_7    KC_7    // 7
#define CM_8    KC_8    // 8
#define CM_9    KC_9    // 9
#define CM_0    KC_0    // 0
#define CM_MINS KC_MINS // -
#define CM_EQL  KC_EQL  // =
// Row 2
#define CM_Q    KC_Q    // Q
#define CM_W    KC_W    // W
#define CM_F    KC_E    // F
#define CM_P    KC_R    // P
#define CM_G    KC_T    // G
#define CM_J    KC_Y    // J
#define CM_L    KC_U    // L
#define CM_U    KC_I    // U
#define CM_Y    KC_O    // Y
#define CM_SCLN KC_P    // ;
#define CM_LBRC KC_LBRC // [
#define CM_RBRC KC_RBRC // ]
#define CM_BSLS KC_BSLS // (backslash)
// Row 3
#define CM_A    KC_A    // A
#define CM_R    KC_S    // R
#define CM_S    KC_D    // S
#define CM_T    KC_F    // T
#define CM_D    KC_G    // D
#define CM_H    KC_H    // H
#define CM_N    KC_J    // N
#define CM_E    KC_K    // E
#define CM_I    KC_L    // I
#define CM_O    KC_SCLN // O
#define CM_QUOT KC_QUOT // '
// Row 4
#define CM_Z    KC_Z    // Z
#define CM_X    KC_X    // X
#define CM_C    KC_C    // C
#define CM_V    KC_V    // V
#define CM_B    KC_B    // B
#define CM_K    KC_N    // K
#define CM_M    KC_M    // M
#define CM_COMM KC_COMM // ,
#define CM_DOT  KC_DOT  // .
#define CM_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │ : │ { │ } │  |  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │ " │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CM_TILD S(CM_GRV)  // ~
#define CM_EXLM S(CM_1)    // !
#define CM_AT   S(CM_2)    // @
#define CM_HASH S(CM_3)    // #
#define CM_DLR  S(CM_4)    // $
#define CM_PERC S(CM_5)    // %
#define CM_CIRC S(CM_6)    // ^
#define CM_AMPR S(CM_7)    // &
#define CM_ASTR S(CM_8)    // *
#define CM_LPRN S(CM_9)    // (
#define CM_RPRN S(CM_0)    // )
#define CM_UNDS S(CM_MINS) // _
#define CM_PLUS S(CM_EQL)  // +
// Row 2
#define CM_COLN S(CM_SCLN) // :
#define CM_LCBR S(CM_LBRC) // {
#define CM_RCBR S(CM_RBRC) // }
#define CM_PIPE S(CM_BSLS) // |
// Row 3
#define CM_DQUO S(CM_QUOT) // "
// Row 4
#define CM_LABK S(CM_COMM) // <
#define CM_RABK S(CM_DOT)  // >
#define CM_QUES S(CM_SLSH) // /

// DEPRECATED
#define KC_CM_Q    CM_Q
#define KC_CM_W    CM_W
#define KC_CM_F    CM_F
#define KC_CM_P    CM_P
#define KC_CM_G    CM_G
#define KC_CM_J    CM_J
#define KC_CM_L    CM_L
#define KC_CM_U    CM_U
#define KC_CM_Y    CM_Y
#define KC_CM_SCLN CM_SCLN
#define KC_CM_A    CM_A
#define KC_CM_R    CM_R
#define KC_CM_S    CM_S
#define KC_CM_T    CM_T
#define KC_CM_D    CM_D
#define KC_CM_H    CM_H
#define KC_CM_N    CM_N
#define KC_CM_E    CM_E
#define KC_CM_I    CM_I
#define KC_CM_O    CM_O
#define KC_CM_Z    CM_Z
#define KC_CM_X    CM_X
#define KC_CM_C    CM_C
#define KC_CM_V    CM_V
#define KC_CM_B    CM_B
#define KC_CM_K    CM_K
#define KC_CM_M    CM_M
#define KC_CM_COMM CM_COMM
#define KC_CM_DOT  CM_DOT
#define KC_CM_SLSH CM_SLSH
