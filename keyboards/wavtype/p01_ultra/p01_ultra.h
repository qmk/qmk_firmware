/* Copyright 2021 wavtype
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

#define _x_ KC_NO

#include "quantum.h"

/*              ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 *              │00 │   │02 │03 │04 │05 │ │06 │07 │08 │09 │ │0B │0C │0D │0E │ │0F │0G │0H │
 *              └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐      ┌───────┐
 *              │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │3E │ │1F │1G │1H │      │1D     │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤      └─┬─────┤
 *              │20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D   │ │2F │2G │2H │        │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘     ┌──┴┐3D  │ ISO Enter
 *  LShift      │30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D      │                   │2D │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐       ┌─┴───┴────┤
 * │40      │   │40  │4B │41 │42 │43 │44 │45 │46 │47 │48 │49 │4A │4D    │4E │     │4G │       │4D        │ 2.75u RShift
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤ ┌───┼───┼───┐   └──────────┘
 *              │50  │51  │52  │56                      │59  │5A  │5C  │5E  │ │5F │5G │5H │
 *              └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
 *              ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 *              │50   │51 │52   │56                         │5A   │5C │5E   │ Tsangan/WKL
 *              └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 */

#define LAYOUT_tkl_ansi( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09,      K0B, K0C, K0D, K0E, K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,                     \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,           K4D,           K4G,      \
    K50, K51, K52,                K56,           K59, K5A,      K5C,      K5E, K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, _x_, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, _x_, _x_, K4D, _x_, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, K59, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}

#define LAYOUT_tkl_ansi_split_bs_rshift( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09, K0B, K0C, K0D, K0E,        K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K3E,   K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,        K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,                       \
    K40,      K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4D, K4E,             K4G,      \
    K50, K51, K52,                K56,                K59, K5A, K5C, K5E,        K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, K3E, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, _x_, _x_, K4D, K4E, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, K59, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}

#define LAYOUT_tkl_ansi_tsangan( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09,      K0B, K0C, K0D, K0E, K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,                     \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,           K4D,           K4G,      \
    K50, K51, K52,                K56,                K5A,      K5C,      K5E, K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, _x_, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, _x_, _x_, K4D, _x_, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, _x_, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}

#define LAYOUT_tkl_ansi_tsangan_split_bs_rshift( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09, K0B, K0C, K0D, K0E,        K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K3E,   K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,        K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,                       \
    K40,      K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4D, K4E,             K4G,      \
    K50, K51, K52,                K56,                     K5A, K5C, K5E,        K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, K3E, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, _x_, _x_, K4D, K4E, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, _x_, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}

#define LAYOUT_tkl_iso( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09,      K0B, K0C, K0D, K0E, K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,           K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K2D, K3D,                     \
    K40, K4B, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4D,           K4G,      \
    K50, K51, K52,                K56,           K59, K5A,      K5C,      K5E, K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, _x_, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, _x_, K4D, _x_, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, K59, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}

#define LAYOUT_tkl_iso_split_bs_rshift( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09, K0B, K0C, K0D, K0E,        K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K3E,   K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,             K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K2D, K3D,                       \
    K40, K4B, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4D, K4E,             K4G,      \
    K50, K51, K52,                K56,                K59, K5A, K5C, K5E,        K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, K3E, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, _x_, K4D, K4E, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, K59, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}

#define LAYOUT_tkl_iso_tsangan( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09,      K0B, K0C, K0D, K0E, K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,           K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K2D,                     \
    K40, K4B, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4D,           K4G,      \
    K50, K51, K52,                K56,                K5A,      K5C,      K5E, K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, _x_, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, _x_, K4D, _x_, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, _x_, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}

#define LAYOUT_tkl_iso_tsangan_split_bs_rshift( \
    K00,      K02, K03, K04, K05, K06, K07, K08, K09, K0B, K0C, K0D, K0E,        K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K3E,   K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,             K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K2D,                       \
    K40, K4B, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4D, K4E,             K4G,      \
    K50, K51, K52,                K56,                     K5A, K5C, K5E,        K5F, K5G, K5H  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, K3E, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, _x_, K4D, K4E, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, _x_, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}
