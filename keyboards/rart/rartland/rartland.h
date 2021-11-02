/* Copyright 2021 Alabahuy
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
 *                                                                  ┌────────┐
 *                                                     2u Backspace │0D      │
 *                                                                  └────────┘
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 *              │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │1D │4D │
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤      ┌─────┐
 *              │10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │2D   │4C │      │     │ ISO
 * 2.25u        ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤   ┌──┴┐2D  │ Enter
 * LShift       │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C      │4B │   │2C │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤   └───┴────┘
 * │30      │   │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3C    │3D │4A │
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 *              │40  │41  │42  │43                      │44 │45 │46 │47 │48 │49 │
 *              └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 *               └────────────────(a)──────────────────┘└────(b)────┘
 *
 *            (a) 1.5 / 1.5 / 7                         (b)
 *            ┌─────┬─────┬───────────────────────────┐ ┌─────┬─────┐
 *            │40   │41   │43                         │ │44   │46   │ 1.5 / 1.5
 *            └─────┴─────┴───────────────────────────┘ └─────┴─────┘
 *                                                      ┌────┬────┐
 *                                                      │44  │45  │ 1.25 / 1.25 (0.5u gap)
 *                                                      └────┴────┘
 */

#define LAYOUT_all( \
   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K1D, K4D, \
   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K2D,      K4C, \
   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,           K4B, \
   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,      K4A, \
   K40, K41, K42,                K43,                K44, K45, K46, K47, K48, K49 \
) { \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
  { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
  { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D } \
}

#define LAYOUT_65_ansi( \
   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K4D, \
   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K2D, K4C, \
   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2C, K4B, \
   K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K4A, \
   K40, K41, K42,                K43,           K44, K45, K46, K47, K48, K49 \
) { \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, XXX }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
  { K30, XXX, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
  { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D } \
}

#define LAYOUT_65_iso( \
   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K4D, \
   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,      K4C, \
   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K4B, \
   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K4A, \
   K40, K41, K42,                K43,           K44, K45, K46, K47, K48, K49 \
) { \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, XXX }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
  { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
  { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D } \
}
