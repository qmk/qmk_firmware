/* Copyright 2021 Yiancar-Designs
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

#define XXX KC_NO

#include "quantum.h"

/*
 *   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 *   │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │
 *   ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 *   │10  │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1D    │
 *   ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┤   ┌────────┐
 *   │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B  │2D │   │2B      │ 2.25u RShift
 *   └────┬─┴─┬─┴──┬┴──┬┴───┴───┼───┴───┴──┬┴──┬┴───┼───┬┴───┘   └────────┘
 *        │31 │32  │33 │   35   │    37    │39 │3A  │3B │
 *        └───┴────┴───┴────────┴──────────┴───┴────┴───┘
 *                 ┌───────────────────────────┐
 *                 │            36             │ 7u Spacebar
 *                 └───────────────────────────┘
 */

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B,      K1D, \
    K20,      K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2D, \
         K31, K32, K33,      K35, K36, K37,      K39, K3A, K3B            \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, XXX, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, K2D }, \
    { XXX, K31, K32, K33, XXX, K35, K36, K37, XXX, K39, K3A, K3B, XXX, XXX }  \
}

#define LAYOUT_split_space( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B,      K1D, \
    K20,      K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2D, \
         K31, K32, K33,      K35,      K37,      K39, K3A, K3B            \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, XXX, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, K2D }, \
    { XXX, K31, K32, K33, XXX, K35, XXX, K37, XXX, K39, K3A, K3B, XXX, XXX }  \
}

#define LAYOUT_7u_space( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B,      K1D, \
    K20,      K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2D, \
         K31, K32,                K36,                K3A, K3B            \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, XXX, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, K2D }, \
    { XXX, K31, K32, XXX, XXX, XXX, K36, XXX, XXX, XXX, K3A, K3B, XXX, XXX }  \
}
