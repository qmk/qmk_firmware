/* Copyright 2019 MechMerlin <mechmerlin@gmail.com>
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

#define LAYOUT_all( \
    K00, K01,   K02,      K04, K05, K06, K07,   K09, K0A, K0B, K0C,    K0D, K0E, K0F, K0G,   K0J, K0I, \
    K10, K11,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G,   K1H, K1I, \
    K20, K21,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E,      K2G,   K2H, K2I, \
    K30, K31,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E,      K3G,   K3H, K3I, \
    K40, K41,   K42, k43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C,      K4E, K4F, K4G,  K4H,       \
    K50, K51,   K52, K53, K54,                          K5A,      K5C,      K5E, K5F,  K5G, K5H, K5I   \
) { \
  { K00, K01,   K02, XXX, K04, K05, K06, K07, XXX, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, XXX, K0I, K0J }, \
  { K10, K11,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, XXX }, \
  { K20, K21,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, XXX, K2G, K2H, K2I, XXX }, \
  { K30, K31,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, XXX, K3G, K3H, K3I, XXX }, \
  { K40, K41,   K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, XXX, K4E, K4F, K4G, K4H, XXX, XXX }, \
  { K50, K51,   K52, K53, K54, XXX, XXX, XXX, XXX, XXX, K5A, XXX, K5C, XXX, K5E, K5F, K5G, K5H, K5I, XXX }, \
}


#define LAYOUT( \
    K00, K01,   K02,      K04, K05, K06, K07,   K09, K0A, K0B, K0C,    K0D, K0E, K0F, K0G,   K0J, K0I, \
    K10, K11,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E,      K1G,   K1H, K1I, \
    K20, K21,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E,      K2G,   K2H, K2I, \
    K30, K31,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,           K3G,   K3H, K3I, \
    K40, K41,   K42,      K44, K45, K46, K47, K48, K49, K4A, K4B, K4C,      K4E, K4F,       K4H,       \
    K50, K51,   K52, K53, K54,                          K5A,      K5C,      K5E, K5F,  K5G, K5H, K5I   \
) { \
  { K00, K01,   K02, XXX, K04, K05, K06, K07, XXX, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, XXX, K0I, K0J }, \
  { K10, K11,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, XXX, K1G, K1H, K1I, XXX }, \
  { K20, K21,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, XXX, K2G, K2H, K2I, XXX }, \
  { K30, K31,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, XXX, XXX, K3G, K3H, K3I, XXX }, \
  { K40, K41,   K42, XXX, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, XXX, K4E, K4F, XXX, K4H, XXX, XXX }, \
  { K50, K51,   K52, K53, K54, XXX, XXX, XXX, XXX, XXX, K5A, XXX, K5C, XXX, K5E, K5F, K5G, K5H, K5I, XXX }, \
}
