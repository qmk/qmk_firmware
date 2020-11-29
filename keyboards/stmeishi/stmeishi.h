/* Copyright 2017 skully <skullydazed@gmail.com>
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
#ifndef STMEISHI_H
#define STMEISHI_H

#include "quantum.h"

/*
 * These are shortcuts to help you work with the various layout options. If your
 * keymap works with one of the LAYOUT_...() macros you are encouraged to use that
 * and to contribute your keymap to the corresponding layout in
 * `qmk_firmware/layouts/community`.
 */

/* Normal COL2ROW matrix.
 */
#define LAYOUT_normal_matrix( \
    k00, k01, k02, \
    k10, k11, k12 \
) \
{ \
    { k00, k01, k02 } , \
    { k10, k11, k12 }   \
}

/* Round Robin matrix. */
#define LAYOUT_rr_matrix( \
    k10, k01, k02, \
    k20, k21, k12  \
) \
{ \
    { KC_NO, k01,   k02   } , \
    { k10,   KC_NO, k12   } , \
    { k20,   k21,   KC_NO }   \
}

#define LAYOUT_normal LAYOUT_normal_matrix
#define KEYMAP LAYOUT_normal_matrix

#define LAYOUT_rr LAYOUT_rr_matrix


#endif
