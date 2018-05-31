/* Copyright 2017 skully <skullydazed@gmail.com>
 *           2018 Jack Humbert <jack.humb@gmail.com>
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
#ifndef QMK_HANDWIRE_H
#define QMK_HANDWIRE_H

#include "quantum.h"

/*
 * These are shortcuts to help you work with the various layout options. If your 
 * keymap works with one of the LAYOUT_...() macros you are encouraged to use that
 * and to contribute your keymap to the corresponding layout in 
 * `qmk_firmware/layouts/community`.
 */

/* The fully-featured KEYMAP() that has every single key available in the matrix.
 */
#define KEYMAP(\
    j00, j01, j02, j03, j04, j05, j06, \
    j10, j11, j12, j13, j14, j15, j16, \
    j20, j21, j22, j23, j24, j25, j26, \
    j30, j31, j32, j33, j34, j35, \
    j40, j41, j42, j43, j44, \
                        j54, j55, j56, \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, k16, \
    k20, k21, k22, k23, k24, k25, k26, \
         k31, k32, k33, k34, k35, k36, \
              k42, k43, k44, k45, k46, \
    k50, k51, k52 \
) { \
    { j00, j01, j02, j03, j04, j05, j06 }, \
    { j10, j11, j12, j13, j14, j15, j16 }, \
    { j20, j21, j22, j23, j24, j25, j26 }, \
    { j30, j31, j32, j33, j34, j35, 0   }, \
    { j40, j41, j42, j43, j44, 0,   0   }, \
    { 0,   0,   0,   0,   j54, j55, j56 }, \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { 0,   k31, k32, k33, k34, k35, k36 }, \
    { 0,   0,   k42, k43, k44, k45, k46 }, \
    { k50, k51, k52, 0,   0,   0,   0   } \
}

#endif