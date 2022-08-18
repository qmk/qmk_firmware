/* Copyright 2022 Feker
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#define XXX KC_NO

/*
 * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┐
 * │00 ││01 │02 │03 │04 ││05 │06 │07 │08 ││09 │0A │0B │0C ││0D │ │4F │
 * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┐
 * │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D     │ │1F │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
 * │20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D   │ │2F │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
 * │30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D      │ │3E │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘ ├───┤
 * │40      │42 │43 │44 │45 │46 │47 │48 │49 │4A │4B │4D    │┌───┐│3F │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┘│4E │└───┘
 * │50  │51  │52  │56                      │5C │5A │59 │┌───┼───┼───┐
 * └────┴────┴────┴────────────────────────┴───┴───┴───┘│5D │5E │5F │
 *                                                      └───┴───┴───┘
 */

#define LAYOUT( \
    K00,  K01, K02, K03, K04,  K05, K06, K07, K08,  K09, K0A, K0B, K0C,  K0D,  K4F, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,   K1D,    K1F, \
     K20,  K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,   K2D,  K2F, \
      K30,   K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,    K3D,    K3E, \
        K40,   K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,   K4D,   K4E, K3F, \
    K50,  K51,  K52,               K56,               K5C, K5A, K59, K5D, K5E, K5F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, XXX }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, XXX, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, XXX, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, XXX, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, XXX, K4D, K4E, K4F }, \
    { K50, K51, K52, XXX, XXX, XXX, K56, XXX, XXX, K59, K5A, XXX, K5C, K5D, K5E, K5F }  \
}
