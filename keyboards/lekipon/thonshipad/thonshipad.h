/* Copyright 2020 Lekipon
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

#define XXX KC_NO

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_ortho_5x15 LAYOUT

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06,      K08, K09, K0A, K0B, K0C, K0D, K0E,\
    K10, K11, K12, K13, K14, K15, K16,      K18, K19, K1A, K1B, K1C, K1D, K1E,\
    K20, K21, K22, K23, K24, K25, K26,      K28, K29, K2A, K2B, K2C, K2D, K2E,\
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E,\
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E \
) \
{ \
    { K00, K10, K20, K30, K40 }, \
    { K02, K12, K22, K32, K42 }, \
    { K04, K14, K24, K34, K44 }, \
    { K06, K16, K26, K36, K46 }, \
    { K08, K18, K28, K38, K48 }, \
    { K0A, K1A, K2A, K3A, K4A }, \
    { K0C, K1C, K2C, K3C, K4C }, \
    { K0E, K1E, K2E, K3E, K4E }, \
    { K01, K11, K21, K31, K41 }, \
    { K03, K13, K23, K33, K43 }, \
    { K05, K15, K25, K35, K45 }, \
    { XXX, XXX, XXX, K37, K47 }, \
    { K09, K19, K29, K39, K49 }, \
    { K0B, K1B, K2B, K3B, K4B }, \
    { K0D, K1D, K2D, K3D, K4D }, \
    { XXX, XXX, XXX, XXX, XXX } \
}

