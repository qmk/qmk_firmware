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
 * │ ` │ Ą │ Č │ Ę │ Ė │ Į │ Š │ Ų │ Ū │ 9 │ 0 │ - │ Ž │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LT_GRV  KC_GRV  // `
#define LT_AOGO KC_1    // Ą
#define LT_CCAR KC_2    // Č
#define LT_EOGO KC_3    // Ę
#define LT_EDOT KC_4    // Ė
#define LT_IOGO KC_5    // Į
#define LT_SCAR KC_6    // Š
#define LT_UOGO KC_7    // Ų
#define LT_UMAC KC_8    // Ū
#define LT_9    KC_9    // 9
#define LT_0    KC_0    // 0
#define LT_MINS KC_MINS // -
#define LT_ZCAR KC_EQL  // Ž
// Row 2
#define LT_Q    KC_Q    // Q
#define LT_W    KC_W    // W
#define LT_E    KC_E    // E
#define LT_R    KC_R    // R
#define LT_T    KC_T    // T
#define LT_Y    KC_Y    // Y
#define LT_U    KC_U    // U
#define LT_I    KC_I    // I
#define LT_O    KC_O    // O
#define LT_P    KC_P    // P
#define LT_LBRC KC_LBRC // [
#define LT_RBRC KC_RBRC // ]
// Row 3
#define LT_A    KC_A    // A
#define LT_S    KC_S    // S
#define LT_D    KC_D    // D
#define LT_F    KC_F    // F
#define LT_G    KC_G    // G
#define LT_H    KC_H    // H
#define LT_J    KC_J    // J
#define LT_K    KC_K    // K
#define LT_L    KC_L    // L
#define LT_SCLN KC_SCLN // ;
#define LT_QUOT KC_QUOT // '
#define LT_BSLS KC_BSLS // (backslash)
// Row 4
#define LT_Z    KC_Z    // Z
#define LT_X    KC_X    // X
#define LT_C    KC_C    // C
#define LT_V    KC_V    // V
#define LT_B    KC_B    // B
#define LT_N    KC_N    // N
#define LT_M    KC_M    // M
#define LT_COMM KC_COMM // ,
#define LT_DOT  KC_DOT  // .
#define LT_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │   │   │   │   │   │   │   │   │ ( │ ) │ _ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │  |  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │ : │ " │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LT_TILD S(LT_GRV)  // ~
#define LT_LPRN S(LT_9)    // (
#define LT_RPRN S(LT_0)    // )
#define LT_UNDS S(LT_MINS) // _
// Row 2
#define LT_LCBR S(LT_LBRC) // {
#define LT_RCBR S(LT_RBRC) // }
// Row 3
#define LT_COLN S(LT_SCLN) // :
#define LT_DQUO S(LT_QUOT) // "
#define LT_PIPE S(LT_BSLS) // |
// Row 4
#define LT_LABK S(LT_COMM) // <
#define LT_RABK S(LT_DOT)  // >
#define LT_QUES S(LT_SLSH) // ?

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │   │   │   │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LT_1    ALGR(LT_AOGO) // 1
#define LT_2    ALGR(LT_CCAR) // 2
#define LT_3    ALGR(LT_EOGO) // 3
#define LT_4    ALGR(LT_EDOT) // 4
#define LT_5    ALGR(LT_IOGO) // 5
#define LT_6    ALGR(LT_SCAR) // 6
#define LT_7    ALGR(LT_UOGO) // 7
#define LT_8    ALGR(LT_UMAC) // 8
#define LT_EQL  ALGR(LT_ZCAR) // =
// Row 2
#define LT_EURO ALGR(LT_E)    // €

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │   │   │   │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LT_EXLM S(ALGR(LT_AOGO)) // !
#define LT_AT   S(ALGR(LT_CCAR)) // @
#define LT_HASH S(ALGR(LT_EOGO)) // #
#define LT_DLR  S(ALGR(LT_EDOT)) // $
#define LT_PERC S(ALGR(LT_IOGO)) // %
#define LT_CIRC S(ALGR(LT_SCAR)) // ^
#define LT_AMPR S(ALGR(LT_UOGO)) // &
#define LT_ASTR S(ALGR(LT_UMAC)) // *
#define LT_PLUS S(ALGR(LT_ZCAR)) // +
