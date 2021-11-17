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
    k_esc,       k_f1, k_f2, k_f3, f_f4,    k_f5, k_f6, k_f7, k_f8,    k_f9, k_f10, k_f11, k_f12,      k_prscr, k_scrl, k_pause, \
    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,          k_ins,   k_home, k_pgup,     kp_nl, kp_div, kp_mult, kp_minus, \
    k_tab,     k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backsl, k_del,   k_end,  k_pgdn,     kp_7,  kp_8,   kp_9,    kp_plus,  \
    k_caps,       k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,                                kp_4,  kp_5,   kp_6,              \
    k_lshift,        k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,       k_rshift,               k_up,               kp_1,  kp_2,   kp_3,    kp_enter, \
    k_lctrl, k_lwin, k_lalt,              k_space,             k_ralt, k_rwin, k_rmenu, k_rctrl,       k_left,  k_down, k_right,    kp_0,          kp_dot             \
) \
{ \
    { k_esc,    k_f2,   f_f4,  KC_NO, k_f6,  k_f7,    k_f8,  k_f9,  k_f10,        k_f12,         k_prscr,     k_scrl, k_pause, KC_NO, KC_NO,  KC_NO    }, \
    { k_tild,   k_f1,   k_f3,  k_f5,  KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,        k_f11,         KC_NO,       KC_NO,  KC_NO,   KC_NO, KC_NO,  kp_minus }, \
    { k_1,      k_2,    k_4,   k_5,   k_6,   k_7,     k_9,   k_0,   k_minus,      KC_NO,         k_backspace, k_home, k_pgup,  kp_nl, kp_div, kp_mult  }, \
    { k_tab,    k_w,    k_3,   k_r,   k_y,   k_u,     k_8,   k_o,   k_squarebrop, k_equals,      k_backsl,    k_ins,  k_pgdn,  kp_7,  kp_8,   kp_9     }, \
    { k_caps,   k_q,    k_e,   k_f,   k_t,   k_h,     k_i,   k_l,   k_p,          k_squarebrcl,  k_return,    k_del,  k_end,   kp_4,  kp_5,   kp_plus  }, \
    { k_lshift, k_a,    k_s,   k_d,   k_g,   k_n,     k_j,   k_k,   k_semicolon,  k_singlequote, k_rshift,    k_up,   KC_NO,   kp_1,  kp_2,   kp_6     }, \
    { k_lctrl,  k_z,    k_x,   k_c,   k_v,   k_b,     k_m,   k_cm,  k_period,     k_fwslash,     k_rctrl,     k_down, k_right, kp_0,  kp_3,   KC_NO    }, \
    { k_lwin,   k_lalt, KC_NO, KC_NO, KC_NO, k_space, KC_NO, KC_NO, k_ralt,       k_rwin,        k_rmenu,     k_left, KC_NO,   KC_NO, kp_dot, kp_enter }  \
}
