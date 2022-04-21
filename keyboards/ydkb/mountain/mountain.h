/* Copyright 2022
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

#define ___ KC_NO

#include "quantum.h"

#define LAYOUT_default( \
    K00, K01, K02, K03, K04, K05, K06,  K49, K4A, K4B, K4C, K4D, K4E, K48, \
    K07, K10, K11, K12, K13, K14,  K39, K3A, K3B, K3C, K3D, K3E, K3F, K38, \
    K17, K20, K21, K22, K16, K15,  K29, K2A, K2B, K2C, K2D, K2E, K28,      \
    K27, K31, K26, K25, K24, K23,  K19, K1A, K1B, K1C, K1D, K1E, K1F, K18, \
    K37,      K35, K34,      K33,  K0A,           K0B,      K0C, K0F, K08  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, ___, K0A, K0B, K0C, ___, ___, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, ___ }, \
    { ___, K31, ___, K33, K34, K35, ___, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F }, \
    { ___, ___, ___, ___, ___, ___, ___, ___, K48, K49, K4A, K4B, K4C, K4D, K4E, ___ }  \
}

#define LAYOUT_split_backspace( \
    K00, K01, K02, K03, K04, K05, K06,  K49, K4A, K4B, K4C, K4D, K4E, K4F, K48, \
    K07, K10, K11, K12, K13, K14,  K39, K3A, K3B, K3C, K3D, K3E, K3F, K38,      \
    K17, K20, K21, K22, K16, K15,  K29, K2A, K2B, K2C, K2D, K2E, K28,           \
    K27, K31, K26, K25, K24, K23,  K19, K1A, K1B, K1C, K1D, K1E, K1F, K18,      \
    K37,      K35, K34,      K33,  K0A,           K0B,      K0C, K0F, K08       \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, ___, K0A, K0B, K0C, ___, ___, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, ___ }, \
    { ___, K31, ___, K33, K34, K35, ___, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F }, \
    { ___, ___, ___, ___, ___, ___, ___, ___, K48, K49, K4A, K4B, K4C, K4D, K4E, K4F }  \
}

