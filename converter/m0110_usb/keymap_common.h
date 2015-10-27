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
*/
#include <stdint.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "keymap.h"


extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


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
 * |   30| 0C| 0D| 0E| 0F| 10| 11| 20| 22| 1F| 23| 21| 1E|   | | 59| 5B| 5C| 4E|
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
 * |   30| 0C| 0D| 0E| 0F| 10| 11| 20| 22| 1F| 23| 21| 1E| 2A| | 59| 5B| 5C| 4E|
 * |---------------------------------------------------------| |---------------|
 * |    39| 00| 01| 02| 03| 05| 04| 26| 28| 25| 29| 27|    24| | 56| 57| 58| 66|
 * |---------------------------------------------------------| |---------------|
 * |      38| 06| 07| 08| 09| 0B| 2D| 2E| 2B| 2F| 2C|      38| | 53| 54| 55|   |
 * `---------------------------------------------------------' |-----------| 4C|
 *      | 3A|  37|             31              |   34| 3A|     |     52| 41|   |
 *      `------------------------------------------------'     `---------------'
 * Two right and left keys of 38 and 3A are identical, you cannot discriminate those two.
 */
#define KEYMAP( \
    K32,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33,  K47,K68,K6D,K62, \
    K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,      K59,K5B,K5C,K4E, \
    K39,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,    K24,  K56,K57,K58,K66, \
    K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,        K4D,  K53,K54,K55,K4C, \
    K3A,K37,            K31,            K34,K2A,K46,K42,K48,  K52,    K41      \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_NO,    KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_NO,    KC_NO,    KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_##K41, KC_##K42, KC_NO,    KC_NO,    KC_NO,    KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_NO,    KC_NO,    KC_NO,    KC_##K4C, KC_##K4D, KC_##K4E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_NO,    KC_##K5B, KC_##K5C, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K62, KC_NO,    KC_NO,    KC_NO,    KC_##K66, KC_NO    }, \
    { KC_##K68, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K6D, KC_NO,    KC_NO    }, \
}

/* International keyboard layout for M0110 + M0120
 * https://en.wikipedia.org/wiki/File:Apple_Macintosh_Plus_Keyboard.jpg
 * Probably International keyboard layout of M0110A doesn't exist.
 *
 * M0110 + M0120 scan codes
 * ,---------------------------------------------------------. ,---------------.
 * | 32| 12| 13| 14| 15| 17| 16| 1A| 1C| 19| 1D| 1B| 18|   33| | 47| 68| 6D| 62|
 * |---------------------------------------------------------| |---------------|
 * |   30| 0C| 0D| 0E| 0F| 10| 11| 20| 22| 1F| 23| 21| 1E| 2A| | 59| 5B| 5C| 4E|
 * |------------------------------------------------------,  | |---------------|
 * |    39| 00| 01| 02| 03| 05| 04| 26| 28| 25| 29| 27| 24|  | | 56| 57| 58| 66|
 * |---------------------------------------------------------| |---------------|
 * |  38| 06| 07| 08| 09| 0B| 2D| 2E| 2B| 2F| 2C| 0A|      38| | 53| 54| 55|   |
 * `---------------------------------------------------------' |-----------| 4C|
 *      | 3A|  37|             34              |   31| 3A|     |     52| 41|   |
 *      `------------------------------------------------'     `---------------'
 * Two right and left keys of 38 and 3A are identical, you cannot discriminate those two.
 */
#define KEYMAP_INTL( \
    K32,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33,  K47,K68,K6D,K62, \
    K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,K2A,  K59,K5B,K5C,K4E, \
    K39,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,K24,      K56,K57,K58,K66, \
    K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,K0A,          K53,K54,K55,K4C, \
        K3A,K37,            K34,                K31,          K52,    K41      \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_NO,    KC_NO,    KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_##K41, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K47 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K4C, KC_NO,    KC_##K4E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_NO,    KC_##K5B, KC_##K5C, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K62, KC_NO,    KC_NO,    KC_NO,    KC_##K66, KC_NO    }, \
    { KC_##K68, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K6D, KC_NO,    KC_NO    }, \
}
