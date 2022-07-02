/* Copyright 2022 Envious Design
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
 *
 *
 *
 *
 */
#define XXX KC_NO

#define LAYOUT( \
    K00, K02, K03, K04, K05, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E, K2F, K2G, K2H, \
    K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, \
    K40, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, \
    K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5D, K5G, \
    K60, K61, K63, K66, K6A, K6B, K6D, K6E, K6F, K6G, K6H  \
) { \
    { K00, XXX, K02, K03, K04, K05, XXX, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F, K2G, K2H }, \
    { K30, XXX, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H }, \
    { K40, XXX, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, XXX, XXX, XXX, XXX }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, XXX, K5D, XXX, XXX, K5G, XXX }, \
    { K60, K61, XXX, K63, XXX, XXX, K66, XXX, XXX, XXX, K6A, K6B, XXX, K6D, K6E, K6F, K6G, K6H }, \
}

