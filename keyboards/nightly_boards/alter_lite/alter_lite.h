	/* Copyright 2020 DeskDaily
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
      K00,  K01, K02, K03, K04, K05, K06, K07,              K08, K09, K0A, K0B, K0C, K0D, K0E, K0F,       \
     K10,  K11,    K12,  K13, K14, K15, K16,             K18, K19, K1A, K1B,   K1C, K1D, K1E, K1F,        \
    K20,  K21,     K23,   K24, K25, K26, K27,              K28, K29, K2A, K2B,   K2C, K2D, K2F,           \
         K31,       K33,     K34, K35, K36, K37,        K38, K39, K3A, K3B,     K3C, K3D, K3E,     K3F,   \
         K41,              K44,    K45,      K46,       K48,          K4B,                     K4E        \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO, K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { K20,   K21,   KC_NO, K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F   }, \
    { KC_NO, K31,   KC_NO, K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F   }, \
    { KC_NO, K41,   KC_NO, KC_NO, K44,   K45,   K46,   KC_NO, K48,   KC_NO, KC_NO, K4B,   KC_NO, KC_NO, K4E,   KC_NO }, \
}
