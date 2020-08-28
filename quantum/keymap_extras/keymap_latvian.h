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
 * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ \ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LV_GRV  KC_GRV  // `
#define LV_1    KC_1    // 1
#define LV_2    KC_2    // 2
#define LV_3    KC_3    // 3
#define LV_4    KC_4    // 4
#define LV_5    KC_5    // 5
#define LV_6    KC_6    // 6
#define LV_7    KC_7    // 7
#define LV_8    KC_8    // 8
#define LV_9    KC_9    // 9
#define LV_0    KC_0    // 0
#define LV_MINS KC_MINS // -
#define LV_EQL  KC_EQL  // =
// Row 2
#define LV_Q    KC_Q    // Q
#define LV_W    KC_W    // W
#define LV_E    KC_E    // E
#define LV_R    KC_R    // R
#define LV_T    KC_T    // T
#define LV_Y    KC_Y    // Y
#define LV_U    KC_U    // U
#define LV_I    KC_I    // I
#define LV_O    KC_O    // O
#define LV_P    KC_P    // P
#define LV_LBRC KC_LBRC // [
#define LV_RBRC KC_RBRC // ]
// Row 3
#define LV_A    KC_A    // A
#define LV_S    KC_S    // S
#define LV_D    KC_D    // D
#define LV_F    KC_F    // F
#define LV_G    KC_G    // G
#define LV_H    KC_H    // H
#define LV_J    KC_J    // J
#define LV_K    KC_K    // K
#define LV_L    KC_L    // L
#define LV_SCLN KC_SCLN // ;
#define LV_QUOT KC_QUOT // ' (dead)
#define LV_BSLS KC_NUHS // (backslash)
// Row 4
#define LV_NUBS KC_NUBS // (backslash)
#define LV_Z    KC_Z    // Z
#define LV_X    KC_X    // X
#define LV_C    KC_C    // C
#define LV_V    KC_V    // V
#define LV_B    KC_B    // B
#define LV_N    KC_N    // N
#define LV_M    KC_M    // M
#define LV_COMM KC_COMM // ,
#define LV_DOT  KC_DOT  // .
#define LV_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ : │ " │ | │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LV_TILD S(LV_GRV)  // ~
#define LV_EXLM S(LV_1)    // !
#define LV_AT   S(LV_2)    // @
#define LV_HASH S(LV_3)    // #
#define LV_DLR  S(LV_4)    // $
#define LV_PERC S(LV_5)    // %
#define LV_CIRC S(LV_6)    // ^
#define LV_AMPR S(LV_7)    // &
#define LV_ASTR S(LV_8)    // *
#define LV_LPRN S(LV_9)    // (
#define LV_RPRN S(LV_0)    // )
#define LV_UNDS S(LV_MINS) // _
#define LV_PLUS S(LV_EQL)  // +
// Row 2
#define LV_LCBR S(LV_LBRC) // {
#define LV_RCBR S(LV_RBRC) // }
// Row 3
#define LV_COLN S(LV_SCLN) // :
#define LV_DQUO S(LV_QUOT) // " (dead)
#define LV_PIPE S(LV_BSLS) // |
// Row 4
#define LV_LABK S(LV_COMM) // <
#define LV_RABK S(LV_DOT)  // >
#define LV_QUES S(LV_SLSH) // ?

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ - │   │ « │ » │ € │   │ ’ │   │   │   │   │ – │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ Ē │ Ŗ │   │   │ Ū │ Ī │ Ō │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Ā │ Š │   │   │ Ģ │   │   │ Ķ │ Ļ │   │ ´ │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │ Ž │   │ Č │   │   │ Ņ │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LV_SHYP ALGR(LV_GRV)  // - (soft hyphen)
#define LV_NBSP ALGR(LV_1)    //   (non-breaking space)
#define LV_LDAQ ALGR(LV_2)    // «
#define LV_RDAQ ALGR(LV_3)    // »
#define LV_EURO ALGR(LV_4)    // €
#define LV_RSQU ALGR(LV_6)    // ’
#define LV_NDSH ALGR(LV_MINS) // –
// Row 2
#define LV_EMAC ALGR(LV_E)    // Ē
#define LV_RCED ALGR(LV_R)    // Ŗ
#define LV_UMAC ALGR(LV_U)    // Ū
#define LV_IMAC ALGR(LV_I)    // Ī
#define LV_OMAC ALGR(LV_O)    // Ō
// Row 3
#define LV_AMAC ALGR(LV_A)    // Ā
#define LV_SCAR ALGR(LV_S)    // Š
#define LV_GCED ALGR(LV_G)    // Ģ
#define LV_KCED ALGR(LV_K)    // Ķ
#define LV_LCED ALGR(LV_L)    // Ļ
#define LV_ACUT ALGR(LV_QUOT) // ´ (dead)
// Row 4
#define LV_ZCAR ALGR(LV_Z)    // Ž
#define LV_CCAR ALGR(LV_Z)    // Č
#define LV_NCED ALGR(LV_Z)    // Ņ

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │   │   │ § │ ° │   │ ± │ × │   │   │ — │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ ¨ │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define LV_SECT S(ALGR(LV_4))    // §
#define LV_DEG  S(ALGR(LV_5))    // °
#define LV_PLMN S(ALGR(LV_7))    // ±
#define LV_MUL  S(ALGR(LV_8))    // ×
#define LV_MDSH S(ALGR(LV_MINS)) // —
// Row 3
#define LV_DIAE S(ALGR(LV_QUOT)) // ¨ (dead)
