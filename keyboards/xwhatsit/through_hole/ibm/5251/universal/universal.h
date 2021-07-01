/* Copyright 2020 Purdea Andrei
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
 */

#define LAYOUT( \
    k21, k31, k_tild,     k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,          k_backtab,           k_dup, \
    k22, k32, k_tab,        k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_enter,   k_kp7, k_kp8, k_kp9, k_campo_m, \
    k23, k33, k_caps,         k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nonusbs,    k_kp4, k_kp5, k_kp6, k_campo_p, \
    k24, k34, k_lshift, k_gtlt, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash, k_rshift, k_altenter,   k_kp1, k_kp2, k_kp3, \
    k42, k44, k_lctrl,                               k_space,                                    k_rightalt,       k_kp0,          k_kpdot \
) \
{ \
    { KC_NO, k21, k31, KC_NO, KC_NO,    k_tild,  k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8,  k_9,      k_0,         k_minus,       k_equals,     k_backspace, k_kp7, k_backtab, k_kp9, k_dup     }, \
    { KC_NO, k22, k32, k42,   k_caps,   k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i,  k_o,      k_p,         k_squarebrop,  k_squarebrcl, k_enter,     k_kp4, k_kp8,     k_kp6, k_campo_m }, \
    { KC_NO, k23, k33, KC_NO, k_lshift, k_gtlt,  k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k,  k_l,      k_semicolon, k_singlequote, k_nonusbs,    k_altenter,  k_kp1, k_kp5,     k_kp3, k_campo_p }, \
    { KC_NO, k24, k34, k44,   KC_NO,    k_lctrl, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm, k_period, k_fwslash,   k_space,       k_rshift,     k_rightalt,  KC_NO, k_kp2,     k_kp0, k_kpdot   }  \
}

// Note:
// * all of column "1" (1-based index) are calibration pads
// * column 4, row 3 (1-based indexes) is a calibration pad
// * column 5, row 1 (1-based indexes) is a calibration pad
// * column 5, row 4 (1-based indexes) is a calibration pad
// * column 20, row 4 (1-based indexes) is a calibration pad

