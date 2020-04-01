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
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ ₩ │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘     │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │          │
 * ├─────┬──┴┬──┴──┬┴──┬┴───┴───┴───┴──┬┴──┬┴───┴┬──┴┬───┬─────┤
 * │     │   │     │Hnj│               │H↔Y│     │   │   │     │
 * └─────┴───┴─────┴───┴───────────────┴───┴─────┴───┴───┴─────┘
 */
// Row 1
#define KR_GRV  KC_GRV  // `
#define KR_1    KC_1    // 1
#define KR_2    KC_2    // 2
#define KR_3    KC_3    // 3
#define KR_4    KC_4    // 4
#define KR_5    KC_5    // 5
#define KR_6    KC_6    // 6
#define KR_7    KC_7    // 7
#define KR_8    KC_8    // 8
#define KR_9    KC_9    // 9
#define KR_0    KC_0    // 0
#define KR_MINS KC_MINS // -
#define KR_CIRC KC_EQL  // =
#define KR_WON  KC_BSLS // ₩
// Row 2
#define KR_Q    KC_Q    // Q
#define KR_W    KC_W    // W
#define KR_E    KC_E    // E
#define KR_R    KC_R    // R
#define KR_T    KC_T    // T
#define KR_Y    KC_Y    // Y
#define KR_U    KC_U    // U
#define KR_I    KC_I    // I
#define KR_O    KC_O    // O
#define KR_P    KC_P    // P
#define KR_LBRC KC_LBRC // [
#define KR_RBRC KC_RBRC // ]
// Row 3
#define KR_A    KC_A    // A
#define KR_S    KC_S    // S
#define KR_D    KC_D    // D
#define KR_F    KC_F    // F
#define KR_G    KC_G    // G
#define KR_H    KC_H    // H
#define KR_J    KC_J    // J
#define KR_K    KC_K    // K
#define KR_L    KC_L    // L
#define KR_SCLN KC_SCLN // ;
#define KR_QUOT KC_QUOT // '
// Row 4
#define KR_Z    KC_Z    // Z
#define KR_X    KC_X    // X
#define KR_C    KC_C    // C
#define KR_V    KC_V    // V
#define KR_B    KC_B    // B
#define KR_N    KC_N    // N
#define KR_M    KC_M    // M
#define KR_COMM KC_COMM // ,
#define KR_DOT  KC_DOT  // .
#define KR_SLSH KC_SLSH // /
// Row 5
#define KR_HANJ KC_LANG2 // Hanja (한자)
#define KR_HAEN KC_LANG1 // Han ↔ Yeong (한 ↔ 영)

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │ | │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘     │
 * │      │   │   │   │   │   │   │   │   │   │ : │ " │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├─────┬──┴┬──┴──┬┴──┬┴───┴───┴───┴──┬┴──┬┴───┴┬──┴┬───┬─────┤
 * │     │   │     │   │               │   │     │   │   │     │
 * └─────┴───┴─────┴───┴───────────────┴───┴─────┴───┴───┴─────┘
 */
// Row 1
#define KR_TILD S(KR_GRV)  // ~
#define KR_EXLM S(KR_1)    // !
#define KR_AT   S(KR_2)    // @
#define KR_HASH S(KR_3)    // #
#define KR_DLR  S(KR_4)    // $
#define KR_PERC S(KR_5)    // %
#define KR_CIRC S(KR_6)    // ^
#define KR_AMPR S(KR_7)    // &
#define KR_ASTR S(KR_8)    // *
#define KR_LPRN S(KR_9)    // (
#define KR_RPRN S(KR_0)    // )
#define KR_UNDS S(KR_MINS) // _
#define KR_PLUS S(KR_EQL)  // +
#define KR_PIPE S(KR_WON)  // |
// Row 2
#define KR_LCBR S(KR_LBRC) // {
#define KR_RCBR S(KR_RBRC) // }
// Row 3
#define KR_COLN S(KR_SCLN) // :
#define KR_DQUO S(KR_COLN) // "
// Row 4
#define KR_LABK S(KR_COMM) // <
#define KR_RABK S(KR_DOT)  // >
#define KR_QUES S(KR_SLSH) // ?
