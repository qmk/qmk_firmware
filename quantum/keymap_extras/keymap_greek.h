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
 * │     │ ; │ ς │ Ε │ Ρ │ Τ │ Υ │ Θ │ Ι │ Ο │ Π │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Α │ Σ │ Δ │ Φ │ Γ │ Η │ Ξ │ Κ │ Λ │ ΄ │ ' │ \ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │ Ζ │ Χ │ Ψ │ Ω │ Β │ Ν │ Μ │ , │ . │ / │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define GR_GRV  KC_GRV  // `
#define GR_1    KC_1    // 1
#define GR_2    KC_2    // 2
#define GR_3    KC_3    // 3
#define GR_4    KC_4    // 4
#define GR_5    KC_5    // 5
#define GR_6    KC_6    // 6
#define GR_7    KC_7    // 7
#define GR_8    KC_8    // 8
#define GR_9    KC_9    // 9
#define GR_0    KC_0    // 0
#define GR_MINS KC_MINS // -
#define GR_EQL  KC_EQL  // =
// Row 2
#define GR_SCLN KC_Q    // ;
#define GR_FSIG KC_W    // ς
#define GR_EPSL KC_E    // Ε
#define GR_RHO  KC_R    // Ρ
#define GR_TAU  KC_T    // Τ
#define GR_UPSL KC_Y    // Υ
#define GR_THET KC_U    // Θ
#define GR_IOTA KC_I    // Ι
#define GR_OMCR KC_O    // Ο
#define GR_PI   KC_P    // Π
#define GR_LBRC KC_LBRC // [
#define GR_RBRC KC_RBRC // ]
// Row 3
#define GR_ALPH KC_A    // Α
#define GR_SIGM KC_S    // Σ
#define GR_DELT KC_D    // Δ
#define GR_PHI  KC_F    // Φ
#define GR_GAMM KC_G    // Γ
#define GR_ETA  KC_H    // Η
#define GR_XI   KC_J    // Ξ
#define GR_KAPP KC_K    // Κ
#define GR_LAMB KC_L    // Λ
#define GR_TONS KC_SCLN // ΄ (dead)
#define GR_QUOT KC_QUOT // '
#define GR_BSLS KC_NUHS // (backslash)
// Row 4
#define GR_ZETA KC_Z    // Ζ
#define GR_CHI  KC_X    // Χ
#define GR_PSI  KC_C    // Ψ
#define GR_OMEG KC_V    // Ω
#define GR_BETA KC_B    // Β
#define GR_NU   KC_N    // Ν
#define GR_MU   KC_M    // Μ
#define GR_COMM KC_COMM // ,
#define GR_DOT  KC_DOT  // .
#define GR_SLSH KC_SLSH // /

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ : │ ΅ │   │   │   │   │   │   │   │   │ { │ } │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ ¨ │ " │ | │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define GR_TILD S(GR_GRV)  // ~
#define GR_EXLM S(GR_1)    // !
#define GR_AT   S(GR_2)    // @
#define GR_HASH S(GR_3)    // #
#define GR_DLR  S(GR_4)    // $
#define GR_PERC S(GR_5)    // %
#define GR_CIRC S(GR_6)    // ^
#define GR_AMPR S(GR_7)    // &
#define GR_ASTR S(GR_8)    // *
#define GR_LPRN S(GR_9)    // (
#define GR_RPRN S(GR_0)    // )
#define GR_UNDS S(GR_MINS) // _
#define GR_PLUS S(GR_EQL)  // +
// Row 2
#define GR_COLN S(GR_SCLN) // :
#define GR_DIAT S(GR_FSIG) // ΅ (dead)
#define GR_LCBR S(GR_LBRC) // {
#define GR_RCBR S(GR_RBRC) // }
// Row 3
#define GR_DIAE S(GR_TONS) // ¨ (dead)
#define GR_DQUO S(GR_QUOT) // "
#define GR_PIPE S(GR_BSLS) // |
// Row 4
#define GR_LABK S(GR_COMM) // <
#define GR_RABK S(GR_DOT)  // >
#define GR_QUES S(GR_SLSH) // ?

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ ² │ ³ │ £ │ § │ ¶ │   │ ¤ │ ¦ │ ° │ ± │ ½ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │ € │ ® │   │ ¥ │   │   │   │   │ « │ » │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ ¬ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │ © │   │   │   │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define GR_SUP2 ALGR(GR_2)    // ²
#define GR_SUP3 ALGR(GR_3)    // ³
#define GR_PND  ALGR(GR_4)    // £
#define GR_SECT ALGR(GR_5)    // §
#define GR_PILC ALGR(GR_6)    // ¶
#define GR_CURR ALGR(GR_8)    // ¤
#define GR_BRKP ALGR(GR_9)    // ¦
#define GR_DEG  ALGR(GR_0)    // °
#define GR_PLMN ALGR(GR_MINS) // ±
#define GR_HALF ALGR(GR_EQL)  // ½
// Row 2
#define GR_EURO ALGR(GR_EPSL) // €
#define GR_REGD ALGR(GR_RHO)  // ®
#define GR_YEN  ALGR(GR_UPSL) // ¥
#define GR_LDAQ ALGR(GR_LBRC) // «
#define GR_RDAQ ALGR(GR_RBRC) // »
// Row 3
#define GR_NOT  ALGR(GR_BSLS) // ¬
// Row 4
#define GR_COPY ALGR(GR_PSI)  // ©
