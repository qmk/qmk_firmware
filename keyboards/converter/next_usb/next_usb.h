
/*
Copyright 2021 Charlotte Brolan <charlotte@kuritakey.zone>


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include "quantum.h"


/* 
 * NeXT Matrix(Scan code)
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * | 49| 4A| 4B| 4C| 4D| 50| 4F| 4E| 1E| 1F| 20| 1D| 1C|   1B  | | 1A| 58| 19| | 26| 27| 28| 25|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * | 41  | 42| 43| 44| 45| 48| 47| 46| 06| 07| 08| 05| 04| 03  | | 02|   | 01| | 21| 22| 23| 24|
 * |-----------------------------------------------------------| `---'   `---' |-----------|---|
 * | 57   | 39| 3A| 3B| 3C| 3D| 40| 3F| 3E| 2D| 2C| 2B|   2A   |               | 12| 18| 13| 15|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * | 56     | 31| 32| 33| 34| 35| 37| 36| 2E| 2F| 30|  55      |     | 16|     | 11| 17| 14|   |
 * |-----------------------------------------------------------| ,-----------. |-----------|   |
 * | 52  | 54  |                38                 | 53  | 51  | | 09| 0F| 10| |0B     | 0C| 0D|
 * `-----------------------------------------------------------' `-----------' `---------------'
 */


#define LAYOUT_next( \
    K49, K4A, K4B, K4C, K4D, K50, K4F, K4E, K1E, K1F, K20, K1D, K1C, K1B,   K1A, K58, K19,    K26, K27, K28, K25, \
    K41, K42, K43, K44, K45, K48, K47, K46, K06, K07, K08, K05, K04, K03,   K02,      K01,    K21, K22, K23, K24, \
    K57, K39, K3A, K3B, K3C, K3D, K40, K3F, K3E, K2D, K2C, K2B,   K2A,                        K12, K18, K13, K15, \
    K56, K31, K32, K33, K34, K35, K37, K36, K2E, K2F, K30,     K55,              K16,         K11, K17, K14,      \
    K52, K54,                    K38,                           K53, K51,   K09, K0F, K10,    K0B,      K0C, K0D  \
    ) { \
    { KC_NO, K01, K02, K03, K04, K05, K06, K07 }, \
    { K08, K09, KC_NO, K0B, K0C, K0D, KC_NO, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K28, KC_NO, K2A, K2B, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K38, K39, K3A, K3B, K3C, K3D, K3E, K3F }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K48, K49, K4A, K4B, K4C, K4D, K4E, K4F }, \
    { K50, K51, K52, K53, K54, K55, K56, K57 }, \
    { K58, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}

#endif
