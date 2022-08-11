/* Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0E,      K0F,   \
    K10,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E,    K1F,   \
    K20,    K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,        K2F,   \
    K31,       K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,     K3E, K3F,   \
    K40,  K41, K43,              K46,               K4A,   K4B,      K4D, K4E, K4F    \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, ___, K0E, K0F   }, \
    { K10, ___, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F   }, \
    { K20, ___, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, ___, K2F   }, \
    { ___, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E, K3F   }, \
    { K40, K41, ___, K43, ___, ___, K46, ___, ___, ___, K4A, K4B, ___, K4D, K4E, K4F   }, \
}
