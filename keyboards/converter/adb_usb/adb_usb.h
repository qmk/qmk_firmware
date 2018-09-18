/*
Copyright 2011,2012,2013 Jun Wako <wakojun@gmail.com>

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

Ported to QMK by Peter Roe <pete@13bit.me>
*/

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include "quantum.h"

/* M0115/M3501 Apple Extended Keyboard ANSI
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.             ,---.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|             |Pwr|
 * `---'   `---------------' `---------------' `---------------' `-----------'             `---'
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  =|  /|  *|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|  -|
 * |-----------------------------------------------------------| `-----------' |---------------|
 * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|  +|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
 * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
 * |Ctrl |Opt |Cmd |         Space           |     |Opt |Ctrl  | |Lef|Dow|Rig| |      0|  .|   |
 * `-----------------------------------------------------------' `-----------' `---------------'
 */
#define LAYOUT_ext_ansi( \
    K35,    K7A,K78,K63,K76,K60,K61,K62,K64,K65,K6D,K67,K6F, K69,K6B,K71,              K7F, \
    K32,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33, K72,K73,K74,  K47,K51,K4B,K43, \
    K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,K2A, K75,K77,K79,  K59,K5B,K5C,K4E, \
    K39,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,    K24,               K56,K57,K58,K45, \
    K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,        K7B,     K3E,      K53,K54,K55,     \
    K36,K3A,K37,        K31,                        K7C,K7D, K3B,K3D,K3C,  K52,    K41,K4C  \
) { \
    { K00,   K01,   K02,   K03, K04,   K05,   K06,   K07    }, \
    { K08,   K09,   KC_NO, K0B, K0C,   K0D,   K0E,   K0F    }, \
    { K10,   K11,   K12,   K13, K14,   K15,   K16,   K17    }, \
    { K18,   K19,   K1A,   K1B, K1C,   K1D,   K1E,   K1F    }, \
    { K20,   K21,   K22,   K23, K24,   K25,   K26,   K27    }, \
    { K28,   K29,   K2A,   K2B, K2C,   K2D,   K2E,   K2F    }, \
    { K30,   K31,   K32,   K33, KC_NO, K35,   K36,   K37    }, \
    { K38,   K39,   K3A,   K3B, K3C,   K3D,   K3E,   KC_NO, }, \
    { KC_NO, K41,   KC_NO, K43, KC_NO, K45,   KC_NO, K47    }, \
    { KC_NO, KC_NO, KC_NO, K4B, K4C,   KC_NO, K4E,   KC_NO, }, \
    { KC_NO, KC_NO, K52,   K53, K54,   K55,   K56,   K57    }, \
    { K58,   K59,   KC_NO, K5B, K5C,   KC_NO, KC_NO, KC_NO, }, \
    { K60,   K61,   K62,   K63, K64,   K65, KC_NO,   K67    }, \
    { KC_NO, K69,   KC_NO, K6B, KC_NO, K6D, KC_NO,   K6F    }, \
    { KC_NO, K71,   K72,   K73, K74,   K75, K76,     K77    }, \
    { K78,   K79,   K7A,   K7B, K7C,   K7D, KC_NO,   K7F    }  \
}

/* M0116 Apple Standard Keyboard ANSI
 *                     +-------+
 *                     | power |
 *                     +-------+
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+-----+ +---+---+---+---+
 * |esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | bks | |clr| = | / | * |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | tab | q | w | e | r | t | y | u | i | o | p | [ | ] |   | | 7 | 8 | 9 | + |
 * +-----------------------------------------------------+   | +---+---+---+---+
 * | ctrl | a | s | d | f | g | h | j | k | l | ; | ' |return| | 4 | 5 | 6 | - |
 * +---------------------------------------------------------+ +---+---+---+---+
 * | shift  | z | x | c | v | b | n | m | , | . | / |  shift | | 1 | 2 | 3 |   |
 * +---------------------------------------------------------+ +-------+---|ent|
 * |cap|opt|comnd| ` |                   | \ |lef|rig|dwn|up | |   0   | . |   |
 * +---------------------------------------------------------+ +-------+---+---+
 */
#define LAYOUT_m0116_ansi( \
                           K7F,                                              \
   K35,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33, K47,K51,K4B,K43, \
   K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,     K59,K5B,K5C,K45, \
   K36,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,    K24, K56,K57,K58,K4E, \
   K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,        K7B, K53,K54,K55,     \
   K39,K3A,K37,K32,        K31,        K2A,K3B,K3C,K3D,K3E, K52,    K41,K4C  \
) { \
  { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07   }, \
  { K08,   K09,   KC_NO, K0B,   K0C,   K0D,   K0E,   K0F   }, \
  { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17   }, \
  { K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
  { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27   }, \
  { K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F   }, \
  { K30,   K31,   K32,   K33,   KC_NO, K35,   K36,   K37   }, \
  { K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   KC_NO }, \
  { KC_NO, K41,   KC_NO, K43,   KC_NO, K45,   KC_NO, K47   }, \
  { KC_NO, KC_NO, KC_NO, K4B,   K4C,   KC_NO, K4E,   KC_NO }, \
  { KC_NO, K51,   K52,   K53,   K54,   K55,   K56,   K57   }, \
  { K58,   K59,   KC_NO, K5B,   K5C,   KC_NO, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, K7B,   KC_NO, KC_NO, KC_NO, K7F   }  \
}

#endif
