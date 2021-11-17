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
    k21, k31, k_tild,     k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,                 k_dup,  k_fieldmark,     kp_7,     kp_8, kp_9,\
    k22, k32, k_tab,        k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backtab,        k_ins,  k_del,           kp_4,     kp_5, kp_6,\
    k23, k33, k_caps,         k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_braces, k_return,  k_up,   k_down,          kp_1,     kp_2, kp_3,\
    k24, k34, k_lshift, k_gtlt, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,       k_rshift,                k_left, k_right,         kp_comma, kp_0, kp_dot,\
              k_lreset,                            k_space,                       k_rightalt, k_enter \
) \
{ \
    { k21, k31, KC_NO,    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8,  k_9,      k_0,         k_minus,       k_equals,     k_backspace, KC_NO,      k_dup,  k_fieldmark, kp_7,     kp_8, kp_9 }, \
    { k22, k32, k_caps,   k_tab,  k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i,  k_o,      k_p,         k_squarebrop,  k_squarebrcl, k_backtab,   KC_NO,      k_ins,  k_del,       kp_4,     kp_5, kp_6 }, \
    { k23, k33, k_lshift, k_gtlt, k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k,  k_l,      k_semicolon, k_singlequote, k_braces,     k_return,    k_rshift,   k_up,   k_down,      kp_1,     kp_2, kp_3 }, \
    { k24, k34, k_lreset, KC_NO,  k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm, k_period, k_fwslash,   k_space,       k_enter,      KC_NO,       k_rightalt, k_left, k_right,     kp_comma, kp_0, kp_dot }  \
}

// Note:
// * column 4, row 4 (which is encoded as column 3, row 3 in qmk) is a calibration pad
// * column 17, row 4 (which is encoded as column 16, row 3 in qmk) is a calibration pad
