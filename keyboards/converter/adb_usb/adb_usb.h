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

#pragma once

#include "quantum.h"

#define XXX KC_NO

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
    k35,      k7A, k78, k63, k76, k60, k61, k62, k64, k65, k6D, k67, k6F,  k69, k6B, k71,                 k7F, \
    k32, k12, k13, k14, k15, k17, k16, k1A, k1C, k19, k1D, k1B, k18, k33,  k72, k73, k74,  k47, k51, k4B, k43, \
    k30, k0C, k0D, k0E, k0F, k11, k10, k20, k22, k1F, k23, k21, k1E, k2A,  k75, k77, k79,  k59, k5B, k5C, k4E, \
    k39, k00, k01, k02, k03, k05, k04, k26, k28, k25, k29, k27,      k24,                  k56, k57, k58, k45, \
    k38, k06, k07, k08, k09, k0B, k2D, k2E, k2B, k2F, k2C,           k7B,       k3E,       k53, k54, k55,\
    k36, k3A, k37,           k31,                               k7C, k7D,  k3B, k3D, k3C,  k52,      k41, k4C \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k08, k09, XXX, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, XXX, k35, k36, k37 }, \
    { k38, k39, k3A, k3B, k3C, k3D, k3E, XXX }, \
    { XXX, k41, XXX, k43, XXX, k45, XXX, k47 }, \
    { XXX, XXX, XXX, k4B, k4C, XXX, k4E, XXX }, \
    { XXX, k51, k52, k53, k54, k55, k56, k57 }, \
    { k58, k59, XXX, k5B, k5C, XXX, XXX, XXX }, \
    { k60, k61, k62, k63, k64, k65, XXX, k67 }, \
    { XXX, k69, XXX, k6B, XXX, k6D, XXX, k6F }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77 }, \
    { k78, k79, k7A, k7B, k7C, k7D, XXX, k7F } \
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
                                  k7F, \
    k35, k12, k13, k14, k15, k17, k16, k1A, k1C, k19, k1D, k1B, k18, k33,  k47, k51, k4B, k43, \
    k30, k0C, k0D, k0E, k0F, k11, k10, k20, k22, k1F, k23, k21, k1E,       k59, k5B, k5C, k45, \
    k36, k00, k01, k02, k03, k05, k04, k26, k28, k25, k29, k27,      k24,  k56, k57, k58, k4E, \
    k38, k06, k07, k08, k09, k0B, k2D, k2E, k2B, k2F, k2C,           k7B,  k53, k54, k55, \
    k39, k3A, k37, k32,           k31,           k2A, k3B, k3C, k3D, k3E,  k52,      k41, k4C \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k08, k09, XXX, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, XXX, k35, k36, k37 }, \
    { k38, k39, k3A, k3B, k3C, k3D, k3E, XXX }, \
    { XXX, k41, XXX, k43, XXX, k45, XXX, k47 }, \
    { XXX, XXX, XXX, k4B, k4C, XXX, k4E, XXX }, \
    { XXX, k51, k52, k53, k54, k55, k56, k57 }, \
    { k58, k59, XXX, k5B, k5C, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { XXX, XXX, XXX, k7B, XXX, XXX, XXX, k7F } \
}
