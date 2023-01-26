/* Copyright 2021 dayatz
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

#include "quantum.h"
#define _X_ KC_NO

/*                                             ┌───────┐
 *                                             │0B     │ 2u Backspace
 *                                             └───────┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
 * │10  │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B    │
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
 * │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B  │
 * ├─────┬┴──┬┴───┴┬──┴───┴─┬─┴───┴───┴┬──┴──┬┴──┬┴────┤
 * │30   │31 │32   │33      │37        │3A   │3B │3C   │
 * └─────┴───┴─────┴────────┴──────────┴─────┴───┴─────┘
 * ┌─────┬─────┬───────────────────────────┬─────┬─────┐
 * │30   │31   │36                         │3B   │3C   │ 7u Space
 * └─────┴─────┴───────────────────────────┴─────┴─────┘
 */

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K33,           K36, K37,           K3A, K3B, K3C \
) { \
    { K00,  K01,  K02,  K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C }, \
    { K10,  K11,  K12,  K13, K14, K15, K16, K17, K18, K19, K1A, K1B, _X_ }, \
    { K20,  K21,  K22,  K23, K24, K25, K26, K27, K28, K29, K2A, K2B, _X_ }, \
    { K30,  K31,  K32,  K33, _X_, _X_, K36, K37, _X_, _X_, K3A, K3B, K3C } \
}

#define LAYOUT_7u_space( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31,                K36,                     K3B, K3C  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, _X_ }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, _X_ }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, _X_ }, \
    { K30, K31, _X_, _X_, _X_, _X_, K36, _X_, _X_, _X_, _X_, K3B, K3C }  \
}

#define LAYOUT_7u_space_split_bs( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31,                K36,                     K3B, K3C  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, _X_ }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, _X_ }, \
    { K30, K31, _X_, _X_, _X_, _X_, K36, _X_, _X_, _X_, _X_, K3B, K3C }  \
}

#define LAYOUT_split_space( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32,           K33, K37,           K3A, K3B, K3C  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, _X_ }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, _X_ }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, _X_ }, \
    { K30, K31, K32, K33, _X_, _X_, _X_, K37, _X_, _X_, K3A, K3B, K3C }  \
}

#define LAYOUT_split_space_split_bs( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32,           K33, K37,           K3A, K3B, K3C  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, _X_ }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, _X_ }, \
    { K30, K31, K32, K33, _X_, _X_, _X_, K37, _X_, _X_, K3A, K3B, K3C }  \
}
