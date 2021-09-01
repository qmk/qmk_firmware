/*
Copyright 2011,2012,2014,2015 Jun Wako <wakojun@gmail.com>
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

--------------

Ported to QMK by Techsock <info@techsock.com>
*/

#pragma once

#include "quantum.h"

#define XXX KC_NO

/* Common layout for M0110 and M0110A
 * This keymap works with both keyboards. As you can see, the M0110A is 
 * a superset of M0110 keyboard, only one exception is 'Enter'(34) of M0110
 * does not exist on the M0110A.
 *
 * ,---------------------------------------------------------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Clr|  =|  /|  *|
 * |---------------------------------------------------------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
 * |-----------------------------------------------------'   | |---------------|
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6|  +|
 * |---------------------------------------------------------| |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft|Up | |  1|  2|  3|   |
 * |---------------------------------------------------------| |-----------|Ent|
 * |Opt  |Mac    |         Space         |Ent|  \|Lft|Rgt|Dn | |      0|  .|   |
 * `---------------------------------------------------------' `---------------'
 *
 * M0110A scan codes
 * ,---------------------------------------------------------. ,---------------.
 * | 32| 12| 13| 14| 15| 17| 16| 1A| 1C| 19| 1D| 1B| 18|   33| | 47| 68| 6D| 62|
 * |---------------------------------------------------------| |---------------|
 * |   30| 0C| 0D| 0E| 0F| 11| 10| 20| 22| 1F| 23| 21| 1E|   | | 59| 5B| 5C| 4E|
 * |-----------------------------------------------------'   | |---------------|
 * |    39| 00| 01| 02| 03| 05| 04| 26| 28| 25| 29| 27|    24| | 56| 57| 58| 66|
 * |---------------------------------------------------------| |---------------|
 * |      38| 06| 07| 08| 09| 0B| 2D| 2E| 2B| 2F| 2C|  38| 4D| | 53| 54| 55|   |
 * `---------------------------------------------------------' |-----------| 4C|
 * |   3A|     37|             31            | 2A| 46| 42| 48| |     52| 41|   |
 * `---------------------------------------------------------' `---------------'
 *
 * M0110 + M0120 scan codes
 * ,---------------------------------------------------------. ,---------------.
 * | 32| 12| 13| 14| 15| 17| 16| 1A| 1C| 19| 1D| 1B| 18|   33| | 47| 68| 6D| 62|
 * |---------------------------------------------------------| |---------------|
 * |   30| 0C| 0D| 0E| 0F| 11| 10| 20| 22| 1F| 23| 21| 1E| 2A| | 59| 5B| 5C| 4E|
 * |---------------------------------------------------------| |---------------|
 * |    39| 00| 01| 02| 03| 05| 04| 26| 28| 25| 29| 27|    24| | 56| 57| 58| 66|
 * |---------------------------------------------------------| |---------------|
 * |      38| 06| 07| 08| 09| 0B| 2D| 2E| 2B| 2F| 2C|      38| | 53| 54| 55|   |
 * `---------------------------------------------------------' |-----------| 4C|
 *      | 3A|  37|             31              |   34| 3A|     |     52| 41|   |
 *      `------------------------------------------------'     `---------------'
 * Two right and left keys of 38 and 3A are identical, you cannot discriminate those two.
 */
#define LAYOUT_ansi( \
    K32, K12, K13, K14, K15, K17, K16, K1A, K1C, K19, K1D, K1B, K18, K33,  K47, K68, K6D, K62, \
    K30, K0C, K0D, K0E, K0F, K11, K10, K20, K22, K1F, K23, K21, K1E,       K59, K5B, K5C, K4E, \
    K39, K00, K01, K02, K03, K05, K04, K26, K28, K25, K29, K27,      K24,  K56, K57, K58, K66, \
    K38, K06, K07, K08, K09, K0B, K2D, K2E, K2B, K2F, K2C,           K4D,  K53, K54, K55, K4C, \
    K3A, K37,                K31,                K34, K2A, K46, K42, K48,  K52,      K41 \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K08, K09, XXX, K0B, K0C, K0D, K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K28, K29, K2A, K2B, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, XXX, XXX, K37 }, \
    { K38, K39, K3A, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, K41, K42, XXX, XXX, XXX, K46, K47 }, \
    { K48, XXX, XXX, XXX, K4C, K4D, K4E, XXX }, \
    { XXX, XXX, K52, K53, K54, K55, K56, K57 }, \
    { K58, K59, XXX, K5B, K5C, XXX, XXX, XXX }, \
    { XXX, XXX, K62, XXX, XXX, XXX, K66, XXX }, \
    { K68, XXX, XXX, XXX, XXX, K6D, XXX, XXX } \
}

/* International keyboard layout for M0110 + M0120
 * https://en.wikipedia.org/wiki/File:Apple_Macintosh_Plus_Keyboard.jpg
 * Probably International keyboard layout of M0110A doesn't exist.
 *
 * M0110 + M0120 scan codes
 * ,---------------------------------------------------------. ,---------------.
 * | 32| 12| 13| 14| 15| 17| 16| 1A| 1C| 19| 1D| 1B| 18|   33| | 47| 68| 6D| 62|
 * |---------------------------------------------------------| |---------------|
 * |   30| 0C| 0D| 0E| 0F| 11| 10| 20| 22| 1F| 23| 21| 1E| 2A| | 59| 5B| 5C| 4E|
 * |------------------------------------------------------,  | |---------------|
 * |    39| 00| 01| 02| 03| 05| 04| 26| 28| 25| 29| 27| 24|  | | 56| 57| 58| 66|
 * |---------------------------------------------------------| |---------------|
 * |  38| 06| 07| 08| 09| 0B| 2D| 2E| 2B| 2F| 2C| 0A|      38| | 53| 54| 55|   |
 * `---------------------------------------------------------' |-----------| 4C|
 *      | 3A|  37|             34              |   31| 3A|     |     52| 41|   |
 *      `------------------------------------------------'     `---------------'
 * Two right and left keys of 38 and 3A are identical, you cannot discriminate those two.
 */
#define LAYOUT_iso( \
    K32, K12, K13, K14, K15, K17, K16, K1A, K1C, K19, K1D, K1B, K18, K33,  K47, K68, K6D, K62, \
    K30, K0C, K0D, K0E, K0F, K11, K10, K20, K22, K1F, K23, K21, K1E, K2A,  K59, K5B, K5C, K4E, \
    K39, K00, K01, K02, K03, K05, K04, K26, K28, K25, K29, K27, K24,       K56, K57, K58, K66, \
    K38, K06, K07, K08, K09, K0B, K2D, K2E, K2B, K2F, K2C, K0A,            K53, K54, K55, K4C, \
         K3A, K37,                K34,                     K31,            K52,      K41 \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K28, K29, K2A, K2B, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, XXX, XXX, K37 }, \
    { K38, K39, K3A, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, K41, XXX, XXX, XXX, XXX, XXX, K47 }, \
    { XXX, XXX, XXX, XXX, K4C, XXX, K4E, XXX }, \
    { XXX, XXX, K52, K53, K54, K55, K56, K57 }, \
    { K58, K59, XXX, K5B, K5C, XXX, XXX, XXX }, \
    { XXX, XXX, K62, XXX, XXX, XXX, K66, XXX }, \
    { K68, XXX, XXX, XXX, XXX, K6D, XXX, XXX } \
}
