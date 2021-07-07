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
 * │ ² │ & │ é │ " │ ' │ ( │ § │ è │ ! │ ç │ à │ ) │ - │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ A │ Z │ E │ R │ T │ Y │ U │ I │ O │ P │ ^ │ $ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Q │ S │ D │ F │ G │ H │ J │ K │ L │ M │ ù │ µ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ W │ X │ C │ V │ B │ N │ , │ ; │ : │ = │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define BE_SUP2 KC_GRV  // ²
#define BE_AMPR KC_1    // &
#define BE_EACU KC_2    // é
#define BE_DQUO KC_3    // "
#define BE_QUOT KC_4    // '
#define BE_LPRN KC_5    // (
#define BE_SECT KC_6    // §
#define BE_EGRV KC_7    // è
#define BE_EXLM KC_8    // !
#define BE_CCED KC_9    // ç
#define BE_AGRV KC_0    // à
#define BE_RPRN KC_MINS // )
#define BE_MINS KC_EQL  // -
// Row 2
#define BE_A    KC_Q    // A
#define BE_Z    KC_W    // Z
#define BE_E    KC_E    // E
#define BE_R    KC_R    // R
#define BE_T    KC_T    // T
#define BE_Y    KC_Y    // Y
#define BE_U    KC_U    // U
#define BE_I    KC_I    // I
#define BE_O    KC_O    // O
#define BE_P    KC_P    // P
#define BE_DCIR KC_LBRC // ^ (dead)
#define BE_DLR  KC_RBRC // $
// Row 3
#define BE_Q    KC_A    // Q
#define BE_S    KC_S    // S
#define BE_D    KC_D    // D
#define BE_F    KC_F    // F
#define BE_G    KC_G    // G
#define BE_H    KC_H    // H
#define BE_J    KC_J    // J
#define BE_K    KC_K    // K
#define BE_L    KC_L    // L
#define BE_M    KC_SCLN // M
#define BE_UGRV KC_QUOT // ù
#define BE_MICR KC_NUHS // µ
// Row 4
#define BE_LABK KC_NUBS // <
#define BE_W    KC_Z    // W
#define BE_X    KC_X    // X
#define BE_C    KC_C    // C
#define BE_V    KC_V    // V
#define BE_B    KC_B    // B
#define BE_N    KC_N    // N
#define BE_COMM KC_M    // ,
#define BE_SCLN KC_COMM // ;
#define BE_COLN KC_DOT  // :
#define BE_EQL  KC_SLSH // =

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ³ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ _ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ¨ │ * │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ % │ £ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │ ? │ . │ / │ + │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define BE_SUP3 S(BE_SUP2) // ³
#define BE_1    S(BE_AMPR) // 1
#define BE_2    S(BE_EACU) // 2
#define BE_3    S(BE_DQUO) // 3
#define BE_4    S(BE_QUOT) // 4
#define BE_5    S(BE_LPRN) // 5
#define BE_6    S(BE_SECT) // 6
#define BE_7    S(BE_EGRV) // 7
#define BE_8    S(BE_EXLM) // 8
#define BE_9    S(BE_CCED) // 9
#define BE_0    S(BE_AGRV) // 0
#define BE_DEG  S(BE_RPRN) // °
#define BE_UNDS S(BE_MINS) // _
// Row 2
#define BE_DIAE S(BE_DCIR) // ¨ (dead)
#define BE_ASTR S(BE_DLR)  // *
// Row 3
#define BE_PERC S(BE_UGRV) // %
#define BE_PND  S(BE_MICR) // £
// Row 4
#define BE_RABK S(BE_LABK) // >
#define BE_QUES S(BE_COMM) // ?
#define BE_DOT  S(BE_SCLN) // .
#define BE_SLSH S(BE_COLN) // /
#define BE_PLUS S(BE_EQL)  // +

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ | │ @ │ # │   │   │ ^ │   │   │ { │ } │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │   │   │   │   │   │   │   │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │ ´ │ ` │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ \ │   │   │   │   │   │   │   │   │   │ ~ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define BE_PIPE ALGR(BE_AMPR) // |
#define BE_AT   ALGR(BE_EACU) // @
#define BE_HASH ALGR(BE_DQUO) // #
#define BE_CIRC ALGR(BE_SECT) // ^
#define BE_LCBR ALGR(BE_CCED) // {
#define BE_RCBR ALGR(BE_AGRV) // }
// Row 2
#define BE_EURO ALGR(BE_E)    // €
#define BE_LBRC ALGR(BE_DCIR) // [
#define BE_RBRC ALGR(BE_DLR)  // ]
// Row 3
#define BE_ACUT ALGR(BE_UGRV) // ´ (dead)
#define BE_GRV  ALGR(BE_MICR) // ` (dead)
// Row 4
#define BE_BSLS ALGR(BE_LABK) // (backslash)
#define BE_TILD ALGR(BE_EQL)  // ~

// DEPRECATED
#define BE_AMP  BE_AMPR
#define BE_APOS BE_QUOT
#define BE_PARA BE_SECT
#define BE_MU   BE_MICR
#define BE_LESS BE_LABK
#define BE_OVRR BE_DEG
#define BE_UMLT BE_DIAE
#define BE_GRTR BE_RABK
#define BE_LSBR BE_LBRC
#define BE_RSBR BE_RBRC
#define BE_TILT BE_TILD
