/* Copyright 2019 MechMerlin
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,      k2F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3D,      k3E, k3F, \
    k40, k41,      k43,      k45,      k47, k48,      k4A, k4B,      k4D, k4E, k4F  \
) \
{ \
    { k00, k01,   k02,   k03, k04,   k05, k06,   k07, k08, k09,   k0A, k0B, k0C,   k0D, k0E,   k0F }, \
    { k10, KC_NO, k12,   k13, k14,   k15, k16,   k17, k18, k19,   k1A, k1B, k1C,   k1D, k1E,   k1F }, \
    { k20, KC_NO, k22,   k23, k24,   k25, k26,   k27, k28, k29,   k2A, k2B, k2C,   k2D, KC_NO, k2F }, \
    { k30, k31,   k32,   k33, k34,   k35, k36,   k37, k38, k39,   k3A, k3B, KC_NO, k3D, k3E,   k3F }, \
    { k40, k41,   KC_NO, k43, KC_NO, k45, KC_NO, k47, k48, KC_NO, k4A, k4B, KC_NO, k4D, k4E,   k4F }, \
}

#define LAYOUT_65_ansi_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D,      k0F, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,      k2F, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3D,      k3E, k3F, \
    k40, k41,      k43,                k47,           k4A, k4B,      k4D, k4E, k4F  \
) \
{ \
    { k00, k01,   k02,   k03, k04,   k05,   k06,   k07, k08,   k09,   k0A, k0B, k0C,   k0D,   KC_NO, k0F }, \
    { k10, KC_NO, k12,   k13, k14,   k15,   k16,   k17, k18,   k19,   k1A, k1B, k1C,   k1D,   k1E,   k1F }, \
    { k20, KC_NO, k22,   k23, k24,   k25,   k26,   k27, k28,   k29,   k2A, k2B, k2C,   k2D,   KC_NO, k2F }, \
    { k30, KC_NO, k32,   k33, k34,   k35,   k36,   k37, k38,   k39,   k3A, k3B, KC_NO, k3D,   k3E,   k3F }, \
    { k40, k41,   KC_NO, k43, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, k4A, k4B, KC_NO, k4D,   k4E,   k4F }, \
}

#define LAYOUT_65_iso_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,    K0D,   K0F,   \
    K10,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,         K1F,   \
    K20,    K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K1E, K2D,   K2F,   \
    K30,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,     K3E, K3F,   \
    K40,  K41,  K43,              K47,                K4A,  K4B,     K4D, K4E, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   KC_NO, K0F   }, \
    { K10,   KC_NO, K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { K20,   KC_NO, K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   KC_NO, K3D,   K3E,   K3F   }, \
    { K40,   K41,   KC_NO, K43,   KC_NO, KC_NO, KC_NO, K47,   KC_NO, KC_NO, K4A,   K4B,   KC_NO, K4D,   K4E,   K4F   }, \
}
