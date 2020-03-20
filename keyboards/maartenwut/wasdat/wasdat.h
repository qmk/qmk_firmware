/* Copyright 2019 Maarten Dekkers <maartenwut@gmail.com>
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_fullsize_ansi( \
    K05,      K44, K42, K32, K02, K21, K0A, K3E, K4E, K4D, K2D, K0D, K7D,      K23, K53, K51, \
    K45, K25, K24, K22, K20, K40, K48, K28, K2A, K2E, K2F, K4F, K4A, K3D,      K47, K4C, K46,      K69, K67, K66, K76, \
    K35, K55, K54, K52, K50, K30, K38, K58, K5A, K5E, K5F, K3F, K3A, K1D,      K49, K2C, K26,      K59, K57, K56, K5C, \
    K34, K15, K14, K12, K10, K00, K08, K18, K1A, K1E, K1F, K0F,      K6D,                          K39, K37, K36, \
    K3B,      K65, K64, K62, K60, K70, K78, K68, K6A, K6E, K7F,      K1B,           K0C,           K19, K17, K16, K1C, \
    K41, K31, K03,                K09,                K73, K11, K33, K61,      K7C, K79, K77,      K07,      K06 \
) \
{ \
    { K00, XXX, K02, K03, XXX, K05, K06, K07, K08, K09, K0A, XXX, K0C, K0D, XXX, K0F }, \
    { K10, K11, K12, XXX, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX, K28, XXX, K2A, XXX, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, K42, XXX, K44, K45, K46, K47, K48, K49, K4A, XXX, K4C, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, XXX, K5C, XXX, K5E, K5F }, \
    { K60, K61, K62, XXX, K64, K65, K66, K67, K68, K69, K6A, XXX, XXX, K6D, K6E, XXX }, \
    { K70, XXX, XXX, K73, XXX, XXX, K76, K77, K78, K79, XXX, XXX, K7C, K7D, XXX, K7F } \
}

#define LAYOUT_fullsize_iso( \
    K05,      K44, K42, K32, K02, K21, K0A, K3E, K4E, K4D, K2D, K0D, K7D,      K23, K53, K51, \
    K45, K25, K24, K22, K20, K40, K48, K28, K2A, K2E, K2F, K4F, K4A, K3D,      K47, K4C, K46,      K69, K67, K66, K76, \
    K35, K55, K54, K52, K50, K30, K38, K58, K5A, K5E, K5F, K3F, K3A,           K49, K2C, K26,      K59, K57, K56, K5C, \
    K34, K15, K14, K12, K10, K00, K08, K18, K1A, K1E, K1F, K0F, K1D, K6D,                          K39, K37, K36, \
    K3B, K04, K65, K64, K62, K60, K70, K78, K68, K6A, K6E, K7F,      K1B,           K0C,           K19, K17, K16, K1C, \
    K41, K31, K03,                K09,                K73, K11, K33, K61,      K7C, K79, K77,      K07,      K06 \
) \
{ \
    { K00, XXX, K02, K03, K04, K05, K06, K07, K08, K09, K0A, XXX, K0C, K0D, XXX, K0F }, \
    { K10, K11, K12, XXX, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX, K28, XXX, K2A, XXX, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, K42, XXX, K44, K45, K46, K47, K48, K49, K4A, XXX, K4C, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, XXX, K5C, XXX, K5E, K5F }, \
    { K60, K61, K62, XXX, K64, K65, K66, K67, K68, K69, K6A, XXX, XXX, K6D, K6E, XXX }, \
    { K70, XXX, XXX, K73, XXX, XXX, K76, K77, K78, K79, XXX, XXX, K7C, K7D, XXX, K7F } \
}

#define LAYOUT_tkl_ansi( \
    K05,      K44, K42, K32, K02, K21, K0A, K3E, K4E, K4D, K2D, K0D, K7D,      K23, K53, K51, \
    K45, K25, K24, K22, K20, K40, K48, K28, K2A, K2E, K2F, K4F, K4A, K3D,      K47, K4C, K46, \
    K35, K55, K54, K52, K50, K30, K38, K58, K5A, K5E, K5F, K3F, K3A, K1D,      K49, K2C, K26, \
    K34, K15, K14, K12, K10, K00, K08, K18, K1A, K1E, K1F, K0F,      K6D, \
    K3B,      K65, K64, K62, K60, K70, K78, K68, K6A, K6E, K7F,      K1B,           K0C, \
    K41, K31, K03,                K09,                K73, K11, K33, K61,      K7C, K79, K77 \
) \
{ \
    { K00, XXX, K02, K03, XXX, K05, XXX, XXX, K08, K09, K0A, XXX, K0C, K0D, XXX, K0F }, \
    { K10, K11, K12, XXX, K14, K15, XXX, XXX, K18, XXX, K1A, K1B, XXX, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX, K28, XXX, K2A, XXX, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, XXX, XXX, K38, XXX, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, K42, XXX, K44, K45, K46, K47, K48, K49, K4A, XXX, K4C, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX, K58, XXX, K5A, XXX, XXX, XXX, K5E, K5F }, \
    { K60, K61, K62, XXX, K64, K65, XXX, XXX, K68, XXX, K6A, XXX, XXX, K6D, K6E, XXX }, \
    { K70, XXX, XXX, K73, XXX, XXX, XXX, K77, K78, K79, XXX, XXX, K7C, K7D, XXX, K7F } \
}

#define LAYOUT_tkl_iso( \
    K05,      K44, K42, K32, K02, K21, K0A, K3E, K4E, K4D, K2D, K0D, K7D,      K23, K53, K51, \
    K45, K25, K24, K22, K20, K40, K48, K28, K2A, K2E, K2F, K4F, K4A, K3D,      K47, K4C, K46, \
    K35, K55, K54, K52, K50, K30, K38, K58, K5A, K5E, K5F, K3F, K3A,           K49, K2C, K26, \
    K34, K15, K14, K12, K10, K00, K08, K18, K1A, K1E, K1F, K0F, K1D, K6D, \
    K3B, K04, K65, K64, K62, K60, K70, K78, K68, K6A, K6E, K7F,      K1B,           K0C, \
    K41, K31, K03,                K09,                K73, K11, K33, K61,      K7C, K79, K77 \
) \
{ \
    { K00, XXX, K02, K03, K04, K05, XXX, XXX, K08, K09, K0A, XXX, K0C, K0D, XXX, K0F }, \
    { K10, K11, K12, XXX, K14, K15, XXX, XXX, K18, XXX, K1A, K1B, XXX, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX, K28, XXX, K2A, XXX, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, XXX, XXX, K38, XXX, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, K42, XXX, K44, K45, K46, K47, K48, K49, K4A, XXX, K4C, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX, K58, XXX, K5A, XXX, XXX, XXX, K5E, K5F }, \
    { K60, K61, K62, XXX, K64, K65, XXX, XXX, K68, XXX, K6A, XXX, XXX, K6D, K6E, XXX }, \
    { K70, XXX, XXX, K73, XXX, XXX, XXX, K77, K78, K79, XXX, XXX, K7C, K7D, XXX, K7F } \
}
