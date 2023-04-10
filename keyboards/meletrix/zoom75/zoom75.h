/* Copyright 2023 meletrix
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


/* Standard Arrangement                                       knob          keys
 * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐        ┌───┬───┐
 * │00 ││01 │02 │03 │04 ││05 │06 │07 │08 ││09 │0a │0b │0c ││0d │ ◯      │0d │0e │
 * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘        └───┴───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │3d │1e │              ISO
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤            ┌─────┐
 * │20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d   │2e │            │2d   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤         ┌──┴┐    │
 * │30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c      │3e │         │3c │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┘         └───┴────┘
 * │40  │41 │42 │43 │44 │45 │46 │47 │48 │49 │4a │4b │4c    │4d │
 * ├────┼───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┐
 * │50  │51  │52  │55      │56  │57        │59  │5a  │ │5c │5d │5e │
 * └────┴────┴────┴────────┴────┴──────────┴────┴────┘ └───┴───┴───┘
 */

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,  K53, K0E, K54, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K3D, K1E,       \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      K2E,       \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,           K3E,       \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D,                 \
    K50, K51, K52,           K55, K56, K57,      K59, K5A,      K5C, K5D, K5E             \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E   }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A,   K4B,   K4C,   K4D,   KC_NO }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   KC_NO, K59,   K5A,   KC_NO, K5C,   K5D,   K5E   }, \
}
