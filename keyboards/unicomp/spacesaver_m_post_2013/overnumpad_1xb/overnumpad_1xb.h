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
    k_esc,       k_f1, k_f2, k_f3, k_f4,    k_f5, k_f6, k_f7, k_f8,    k_f9, k_f10, k_f11, k_f12,            k_prscr, k_scrl, k_pause, \
    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_bsp_hidden, k_backspace,  k_ins,   k_home, k_pgup,     kp_nl,       kp_div, kp_mult, kp_minus,        \
    k_tab,     k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backsl,       k_del,   k_end,  k_pgdn,     kp_7,        kp_8,   kp_9,    kp_plus,         \
    k_caps,       k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,k_return,                               kp_4,        kp_5,   kp_6,    kp_plus_hidden,  \
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash, k_rshift_hidden, k_rshift,           k_up,               kp_1,        kp_2,   kp_3,    kp_enter,        \
    k_lctrl, k_lwin, k_lalt, k_code,      k_space,             k_1_d,  k_6_4,  k_rmenu, k_rctrl,             k_left,  k_down, k_right,    kp_0_hidden, kp_0,   kp_dot,  kp_enter_hidden  \
) \
{ \
    /*        0       1             2         3       4       5      6      7      8             9             A              B        C        D                E                F   */ \
    /* 0 */ { k_esc,  k_pause,      k_f3,     k_f1,   k_ins,  k_3,   k_4,   k_6,   k_f5,         k_f7,         k_f9,          k_f11,   k_prscr, k_right,         k_scrl,          KC_NO   }, \
    /* 1 */ { k_tab,  KC_NO,        k_del,    k_pgdn, KC_NO,  k_e,   k_t,   k_u,   k_backspace,  k_minus,      k_down,        k_end,   k_home,  k_1_d,           KC_NO,           k_caps  }, \
    /* 2 */ { k_1,    k_bsp_hidden, kp_nl,    k_pgup, k_code, k_i,   k_r,   k_y,   k_equals,     k_9,          k_0,           kp_mult, kp_div,  k_up,            k_lwin,          KC_NO   }, \
    /* 3 */ { k_q,    k_lshift,     kp_9,     k_2,    KC_NO,  k_k,   k_f,   k_h,   k_squarebrcl, k_o,          k_semicolon,   kp_8,    kp_7,    KC_NO,           KC_NO,           k_lctrl }, \
    /* 4 */ { k_a,    KC_NO,        kp_6,     k_w,    k_lalt, k_d,   k_g,   k_j,   k_backsl,     k_squarebrop, k_singlequote, kp_5,    kp_4,    k_rshift_hidden, kp_plus_hidden,  KC_NO   }, \
    /* 5 */ { k_z,    k_rshift,     kp_dot,   k_x,    KC_NO,  k_cm,  k_b,   k_m,   k_return,     k_period,     k_p,           kp_0,    kp_1,    KC_NO,           kp_0_hidden,     k_rctrl }, \
    /* 6 */ { k_nubs, KC_NO,        kp_3,     k_s,    k_6_4,  k_c,   k_v,   k_n,   k_left,       k_l,          k_fwslash,     kp_2,    kp_plus, k_nuhs,          kp_enter_hidden, KC_NO   }, \
    /* 7 */ { k_tild, KC_NO,        kp_minus, k_f2,   k_f4,   k_8,   k_5,   k_7,   k_f6,         k_f8,         k_f10,         k_f12,   k_rmenu, k_space,         kp_enter,        KC_NO   }  \
}

#define LAYOUT_ansi( \
    k_esc,       k_f1, k_f2, k_f3, k_f4,    k_f5, k_f6, k_f7, k_f8,    k_f9, k_f10, k_f11, k_f12,            k_prscr, k_scrl, k_pause, \
    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals,               k_backspace,  k_ins,   k_home, k_pgup,     kp_nl,       kp_div, kp_mult, kp_minus,        \
    k_tab,     k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backsl,       k_del,   k_end,  k_pgdn,     kp_7,        kp_8,   kp_9,    kp_plus,         \
    k_caps,       k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote,        k_return,                               kp_4,        kp_5,   kp_6,    kp_plus_hidden,  \
    k_lshift,       k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,                  k_rshift,           k_up,               kp_1,        kp_2,   kp_3,    kp_enter,        \
    k_lctrl, k_lwin, k_lalt,              k_space,             k_1_d,  k_6_4,  k_rmenu, k_rctrl,             k_left,  k_down, k_right,           kp_0,         kp_dot                    \
) \
{ \
    /*        0       1             2         3       4       5      6      7      8             9             A              B        C        D                E                F   */ \
    /* 0 */ { k_esc,  k_pause,      k_f3,     k_f1,   k_ins,  k_3,   k_4,   k_6,   k_f5,         k_f7,         k_f9,          k_f11,   k_prscr, k_right,         k_scrl,          KC_NO   }, \
    /* 1 */ { k_tab,  KC_NO,        k_del,    k_pgdn, KC_NO,  k_e,   k_t,   k_u,   k_backspace,  k_minus,      k_down,        k_end,   k_home,  k_1_d,           KC_NO,           k_caps  }, \
    /* 2 */ { k_1,    KC_NO,        kp_nl,    k_pgup, KC_NO,  k_i,   k_r,   k_y,   k_equals,     k_9,          k_0,           kp_mult, kp_div,  k_up,            k_lwin,          KC_NO   }, \
    /* 3 */ { k_q,    k_lshift,     kp_9,     k_2,    KC_NO,  k_k,   k_f,   k_h,   k_squarebrcl, k_o,          k_semicolon,   kp_8,    kp_7,    KC_NO,           KC_NO,           k_lctrl }, \
    /* 4 */ { k_a,    KC_NO,        kp_6,     k_w,    k_lalt, k_d,   k_g,   k_j,   k_backsl,     k_squarebrop, k_singlequote, kp_5,    kp_4,    KC_NO,           kp_plus_hidden,  KC_NO   }, \
    /* 5 */ { k_z,    k_rshift,     kp_dot,   k_x,    KC_NO,  k_cm,  k_b,   k_m,   k_return,     k_period,     k_p,           kp_0,    kp_1,    KC_NO,           KC_NO,           k_rctrl }, \
    /* 6 */ { KC_NO,  KC_NO,        kp_3,     k_s,    k_6_4,  k_c,   k_v,   k_n,   k_left,       k_l,          k_fwslash,     kp_2,    kp_plus, KC_NO,           KC_NO,           KC_NO   }, \
    /* 7 */ { k_tild, KC_NO,        kp_minus, k_f2,   k_f4,   k_8,   k_5,   k_7,   k_f6,         k_f8,         k_f10,         k_f12,   k_rmenu, k_space,         kp_enter,        KC_NO   }  \
}

#define LAYOUT_iso( \
    k_esc,       k_f1, k_f2, k_f3, k_f4,    k_f5, k_f6, k_f7, k_f8,    k_f9, k_f10, k_f11, k_f12,            k_prscr, k_scrl, k_pause, \
    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals,               k_backspace,  k_ins,   k_home, k_pgup,     kp_nl,       kp_div, kp_mult, kp_minus,        \
    k_tab,     k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,      k_return,  k_del,   k_end,  k_pgdn,     kp_7,        kp_8,   kp_9,    kp_plus,         \
    k_caps,       k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,                                        kp_4,        kp_5,   kp_6,    kp_plus_hidden,  \
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,                  k_rshift,           k_up,               kp_1,        kp_2,   kp_3,    kp_enter,        \
    k_lctrl, k_lwin, k_lalt,              k_space,             k_1_d,  k_6_4,  k_rmenu, k_rctrl,             k_left,  k_down, k_right,           kp_0,         kp_dot                    \
) \
{ \
    /*        0       1             2         3       4       5      6      7      8             9             A              B        C        D                E                F   */ \
    /* 0 */ { k_esc,  k_pause,      k_f3,     k_f1,   k_ins,  k_3,   k_4,   k_6,   k_f5,         k_f7,         k_f9,          k_f11,   k_prscr, k_right,         k_scrl,          KC_NO   }, \
    /* 1 */ { k_tab,  KC_NO,        k_del,    k_pgdn, KC_NO,  k_e,   k_t,   k_u,   k_backspace,  k_minus,      k_down,        k_end,   k_home,  k_1_d,           KC_NO,           k_caps  }, \
    /* 2 */ { k_1,    KC_NO,        kp_nl,    k_pgup, KC_NO,  k_i,   k_r,   k_y,   k_equals,     k_9,          k_0,           kp_mult, kp_div,  k_up,            k_lwin,          KC_NO   }, \
    /* 3 */ { k_q,    k_lshift,     kp_9,     k_2,    KC_NO,  k_k,   k_f,   k_h,   k_squarebrcl, k_o,          k_semicolon,   kp_8,    kp_7,    KC_NO,           KC_NO,           k_lctrl }, \
    /* 4 */ { k_a,    KC_NO,        kp_6,     k_w,    k_lalt, k_d,   k_g,   k_j,   KC_NO,        k_squarebrop, k_singlequote, kp_5,    kp_4,    KC_NO,           kp_plus_hidden,  KC_NO   }, \
    /* 5 */ { k_z,    k_rshift,     kp_dot,   k_x,    KC_NO,  k_cm,  k_b,   k_m,   k_return,     k_period,     k_p,           kp_0,    kp_1,    KC_NO,           KC_NO,           k_rctrl }, \
    /* 6 */ { k_nubs, KC_NO,        kp_3,     k_s,    k_6_4,  k_c,   k_v,   k_n,   k_left,       k_l,          k_fwslash,     kp_2,    kp_plus, k_nuhs,          KC_NO,           KC_NO   }, \
    /* 7 */ { k_tild, KC_NO,        kp_minus, k_f2,   k_f4,   k_8,   k_5,   k_7,   k_f6,         k_f8,         k_f10,         k_f12,   k_rmenu, k_space,         kp_enter,        KC_NO   }  \
}
