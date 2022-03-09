/* Copyright 2020 Boardsource
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

#define ___ KC_NO

/*
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐┌───┐    ┌───────┐
 *              │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0E ││0F │    │0D     │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤├───┤    └─┬─────┤
 *              │10   │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │1E   ││1F │      │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤├───┤   ┌──┴┐2D  │ ISO Enter
 *  LShift      │20    │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D      ││2F │   │1E │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘└───┘   └───┴────┘
 * │31      │   │31  │30 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D    │┌───┐
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴──┬┴──┬┴──┬───┘│3E │
 *              │40  │41  │43  │44      │46  │48        │4A │4B │4C │┌───┼───┼───┐
 *              └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┘│4D │4E │4F │
 *                                                                   └───┴───┴───┘
 *                             ┌────────────────────────┬─────┬─────┐
 *                 6.25u Space │46                      │4A   │4B   │ RWKL
 *                             └────────────────────────┴─────┴─────┘
 */

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      K2D, K2F, \
    K31, K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3E,      \
    K40, K41,      K43, K44,      K46,      K48,      K4A, K4B, K4C, K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, ___, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, ___, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, ___, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E, ___ }, \
    { K40, K41, ___, K43, K44, ___, K46, ___, K48, ___, K4A, K4B, K4C, K4D, K4E, K4F }  \
}

#define LAYOUT_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,      K0F, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      K2D, K2F, \
    K31,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3E,      \
    K40, K41,      K43,           K46,                K4A, K4B, K4C, K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, ___, K0F }, \
    { K10, ___, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, ___, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, ___, K2F }, \
    { ___, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E, ___ }, \
    { K40, K41, ___, K43, ___, ___, K46, ___, ___, ___, K4A, K4B, K4C, K4D, K4E, K4F }  \
}

#define LAYOUT_ansi_split_bs_space( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      K2D, K2F, \
    K31,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3E,      \
    K40, K41,      K43, K44,      K46,      K48,      K4A, K4B, K4C, K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, ___, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, ___, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, ___, K2F }, \
    { ___, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E, ___ }, \
    { K40, K41, ___, K43, K44, ___, K46, ___, K48, ___, K4A, K4B, K4C, K4D, K4E, K4F }  \
}

#define LAYOUT_iso( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,      K0F, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K1E, K2D, K2F, \
    K31, K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3E,      \
    K40, K41,      K43,           K46,                K4A, K4B, K4C, K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, ___, K0F }, \
    { K10, ___, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, ___, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, ___, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E, ___ }, \
    { K40, K41, ___, K43, ___, ___, K46, ___, ___, ___, K4A, K4B, K4C, K4D, K4E, K4F }  \
}

#define LAYOUT_iso_split_bs_space( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K1E, K2D, K2F, \
    K31, K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3E,      \
    K40, K41,      K43, K44,      K46,      K48,      K4A, K4B, K4C, K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, ___, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, ___, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, ___, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E, ___ }, \
    { K40, K41, ___, K43, K44, ___, K46, ___, K48, ___, K4A, K4B, K4C, K4D, K4E, K4F }  \
}
