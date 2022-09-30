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
                         k_f13, k_f14, k_f15, k_f16, k_f17, k_f18, k_f19, k_f20, k_f21, k_f22, k_f23, k_f24, \
                         k_f1,  k_f2,  k_f3,  k_f4,  k_f5,  k_f6,  k_f7,  k_f8,  k_f9,  k_f10, k_f11, k_f12, \
k_lb1, k_lb2,    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals,               k_backspace,   k_ins,   k_home,   k_pgup,   kp_nl,       kp_div, kp_mult, kp_minus,        \
k_lb3, k_lb4,    k_tab,     k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,      k_backsl,   k_del,   k_end,    k_pgdn,   kp_7,        kp_8,   kp_9,    kp_plus,         \
k_lb5, k_lb6,    k_caps,       k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,k_return,            k_up,               kp_4,        kp_5,   kp_6,    kp_plus_hidden,  \
k_lb7, k_lb8,    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,                  k_rshift,   k_left,  k_navmid, k_right,  kp_1,        kp_2,   kp_3,    kp_enter,        \
k_lb9, k_lb10,   k_lctrl,       k_lalt,                     k_space,                              k_ralt,       k_rctrl,            k_down,             kp_0,                kp_dot                    \
) \
{ \
    /*        0       1             2         3       4        5      6      7      8             9             A              B        C        D                E                F   */ \
    /* 0 */ { k_lb1,  k_lb4,        k_f3,     k_f1,   k_ins,   k_3,   k_4,   k_6,   k_f5,         k_f7,         k_f9,          k_f11,   k_lb3,   k_right,         k_lb2,           k_lb6   }, \
    /* 1 */ { k_tab,  k_f21,        k_del,    k_pgdn, k_f22,   k_e,   k_t,   k_u,   k_backspace,  k_minus,      k_down,        k_end,   k_home,  k_f23,           k_f14,           k_caps  }, \
    /* 2 */ { k_1,    k_f19,        kp_nl,    k_pgup, k_f17,   k_i,   k_r,   k_y,   k_equals,     k_9,          k_0,           kp_mult, kp_div,  k_up,            k_lb9,           k_f16   }, \
    /* 3 */ { k_q,    k_rshift,     kp_9,     k_2,    KC_NO,   k_k,   k_f,   k_h,   k_squarebrcl, k_o,          k_semicolon,   kp_8,    kp_7,    k_f24,           k_f13,           k_lctrl }, \
    /* 4 */ { k_a,    KC_NO,        kp_6,     k_w,    k_lalt,  k_d,   k_g,   k_j,   k_backsl,     k_squarebrop, k_singlequote, kp_5,    kp_4,    k_f20,           k_f15,           k_lb10  }, \
    /* 5 */ { k_z,    k_lshift,     kp_dot,   k_x,    KC_NO,   k_cm,  k_b,   k_m,   k_return,     k_period,     k_p,           kp_0,    kp_1,    k_navmid,        kp_plus_hidden,  k_rctrl }, \
    /* 6 */ { k_nubs, KC_NO,        kp_3,     k_s,    k_ralt,  k_c,   k_v,   k_n,   k_left,       k_l,          k_fwslash,     kp_2,    kp_plus, k_nuhs,          k_lb7,           KC_NO   }, \
    /* 7 */ { k_tild, k_f18,        kp_minus, k_f2,   k_f4,    k_8,   k_5,   k_7,   k_f6,         k_f8,         k_f10,         k_f12,   k_lb8,   k_space,         kp_enter,        k_lb5   }  \
}
