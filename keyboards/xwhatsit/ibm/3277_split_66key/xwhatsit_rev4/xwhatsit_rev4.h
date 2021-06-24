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

#define LAYOUT_all( \
    k31,    k_1  , k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,                 k_dup,  k_fieldmark, \
    k32, k_tab, k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,                   k_ins,  k_del, \
    k33, k_caps,  k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,            k_up,   k_down, \
    k34, k_lshift,  k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,       k_rshift,                k_left, k_right, \
            k_lreset,                            k_space,           k_space2, k_space3, k_space4, k_rctrl \
) \
{ \
    { k32,      k31,      k_1,     k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0,      k_minus,      k_equals,      k_backspace, KC_NO,      k_dup,  k_fieldmark },\
    { k33,      k_tab,    k_q,     k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p,      k_squarebrop, k_squarebrcl,  k_return,    KC_NO,      k_ins,  k_del },\
    { k34,      k_lshift, k_caps,  k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l,      k_semicolon,  k_singlequote, k_rshift,    KC_NO,      k_up,   k_down },\
    { k_space2, k_lreset, k_space, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,    k_space4,      k_rctrl,     k_space3 ,  k_left, k_right }\
}


#define LAYOUT( \
    k31,    k_1  , k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,                 k_dup,  k_fieldmark, \
    k32, k_tab, k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,                   k_ins,  k_del, \
    k33, k_caps,  k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,            k_up,   k_down, \
    k34, k_lshift,  k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,       k_rshift,                k_left, k_right, \
            k_lreset,                            k_space,           k_space2, k_rctrl \
) \
    LAYOUT_all( \
    k31,    k_1  , k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,                 k_dup,  k_fieldmark, \
    k32, k_tab, k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,                   k_ins,  k_del, \
    k33, k_caps,  k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,            k_up,   k_down, \
    k34, k_lshift,  k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,       k_rshift,                k_left, k_right, \
            k_lreset,                            k_space,           KC_NO, k_space2, KC_NO, k_rctrl)

// Note:
// * real columns 1..4, 14 are not in use. (and also in position 15 there is a skipped pin, like for all beam springs)
// * position which is encoded as column 15, row 1 in qmk is a calibration pad
// * position which is encoded as column 15, row 2 in qmk is a calibration pad
