/* Copyright 2021 customMK
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

#define LAYOUT( \
                  K11,   K61,   K12,   K13, K14, K15, K16, K17, K18,  K19, K1A, K1B,  K1C, K1D, K1E, \
                  K62,   K21,   K22,   K23, K24, K25, K26, K27, K28,  K29, K2A, K2B,  K2C, K2D, K2E, \
    K66,   K31,   K63,          K32,   K33, K34, K35, K36, K37, K38,  K39, K3A, K3B,  K3C, K3D, K3E, \
    K57,   K55,          K41,   K42,   K43, K44, K45, K46, K47, K48,  K49, K4A, K4B,  K4C, K4D, K4E, \
    K52,   K54,   K65,   K51,          K53,           K56, K67, E00A, K59, K5A, E00B, K5C, K5D, K5E \
) { \
    { K11, K12, K13, K14,   K15,  K16, K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E }, \
    { K21, K22, K23, K24,   K25,  K26, K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E }, \
    { K31, K32, K33, K34,   K35,  K36, K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E }, \
    { K41, K42, K43, K44,   K45,  K46, K47,   K48,   K49,   K4A,   K4B,   K4C,   K4D,   K4E },  \
    { K51, K52, K53, K54,   K55,  K56, K57,   E00A,  K59,   K5A,   E00B,  K5C,   K5D,   K5E },  \
    { K61, K62, K63, KC_NO, K65,  K66, K67,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}
