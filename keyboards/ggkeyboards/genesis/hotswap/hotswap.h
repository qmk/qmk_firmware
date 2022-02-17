/* Copyright 2021 Steven Phillips (Spooknik)
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

// clang-format off
#define LAYOUT_tkl_ansi( \
    K00,      K01, K02, K03, K04,   K05, K06, K07, K08,    K09, K0A, K0B, K0C,  K0F, K0G, K0H,  \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,       K2F, K2G, K2H,  \
    K30,   K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,     K3F, K3G, K3H,  \
    K40,    K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D,                         \
    K51,       K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C,                K5G,       \
    K60,  K61,  K63,              K66,                K6A,  K6B,  K6C,  K6D,    K6F, K6G, K6H   \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, KC_NO, K0F,   K0G,   K0H   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F,   K2G,   K2H   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   KC_NO, K3F,   K3G,   K3H   }, \
    { K40,   KC_NO, K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A,   K4B,   K4C,   K4D,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58,   K59,   K5A,   K5B,   K5C,   KC_NO, KC_NO, KC_NO, K5G,   KC_NO }, \
    { K60,   K61,   KC_NO, K63,   KC_NO, KC_NO, K66,   KC_NO, KC_NO, KC_NO, K6A,   K6B,   K6C,   K6D,   KC_NO, K6F,   K6G,   K6H   } \
}
