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
    k_lctrl,         k_lalt, k_code,                      k_space,                    k_ralt,      k_rctrl,  k_left,  k_down, k_right,    kp_0_hidden, kp_0,   kp_dot,  kp_enter_hidden  \
) \
{ \
    /*        0       1      2      3                4         5              6             7         8            9         A         B               C                D        E      F     */ \
    /* 0 */ { k_esc,  k_g,   k_h,   k_f6,            KC_NO,    k_singlequote, k_f5,         KC_NO,    kp_0_hidden, kp_0,     kp_dot,   k_up,           k_lalt,          KC_NO,   k_f4,  k_nubs  }, \
    /* 1 */ { k_tab,  k_t,   k_y,   k_squarebrcl,    k_f7,     k_squarebrop,  k_backspace,  k_lshift, kp_4,        kp_5,     kp_6,     kp_plus_hidden, KC_NO,           KC_NO,   k_f3,  k_caps  }, \
    /* 2 */ { k_tild, k_5,   k_6,   k_equals,        k_f8,     k_minus,       k_f9,         KC_NO,    k_del,       k_ins,    k_pgup,   k_home,         KC_NO,           k_lctrl, k_f2,  k_f1    }, \
    /* 3 */ { k_1,    k_4,   k_7,   k_8,             k_9,      k_0,           k_f10,        KC_NO,    k_f11,       k_f12,    k_pgdn,   k_end,          k_prscr,         KC_NO,   k_3,   k_2     }, \
    /* 4 */ { k_q,    k_r,   k_u,   k_i,             k_o,      k_p,           k_bsp_hidden, KC_NO,    kp_7,        kp_8,     kp_9,     kp_plus,        k_scrl,          KC_NO,   k_e,   k_w     }, \
    /* 5 */ { k_a,    k_f,   k_j,   k_k,             k_l,      k_semicolon,   k_backsl,     KC_NO,    kp_1,        kp_2,     kp_3,     kp_enter,       kp_enter_hidden, KC_NO,   k_d,   k_s     }, \
    /* 6 */ { k_z,    k_v,   k_m,   k_cm,            k_period, k_nuhs,        k_return,     k_rshift, kp_nl,       kp_div,   kp_mult,  k_pause,        KC_NO,           k_rctrl, k_c,   k_x     }, \
    /* 7 */ { KC_NO,  k_b,   k_n,   k_rshift_hidden, KC_NO,    k_fwslash,     k_space,      KC_NO,    k_down,      k_right,  kp_minus, k_left,         k_ralt,          KC_NO,   KC_NO, k_code  }  \
}

// the following three key mappings are informed guesses, based on similarity of the gen4 membrane to previous-gen membranes: kp_plus, k_ins, kp_0_hidden

#define LAYOUT_ansi( \
    k_esc,       k_f1, k_f2, k_f3, k_f4,    k_f5, k_f6, k_f7, k_f8,    k_f9, k_f10, k_f11, k_f12,            k_prscr, k_scrl, k_pause, \
    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals,               k_backspace,  k_ins,   k_home, k_pgup,     kp_nl,       kp_div, kp_mult, kp_minus,        \
    k_tab,     k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backsl,       k_del,   k_end,  k_pgdn,     kp_7,        kp_8,   kp_9,    kp_plus,         \
    k_caps,       k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote,        k_return,                               kp_4,        kp_5,   kp_6,                     \
    k_lshift,       k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,                  k_rshift,           k_up,               kp_1,        kp_2,   kp_3,    kp_enter,        \
    k_lctrl,         k_lalt,                              k_space,                    k_ralt,      k_rctrl,  k_left,  k_down, k_right,          kp_0,          kp_dot                    \
) \
{ \
    /*        0       1      2      3                4         5              6             7         8            9         A         B               C                D        E      F     */ \
    /* 0 */ { k_esc,  k_g,   k_h,   k_f6,            KC_NO,    k_singlequote, k_f5,         KC_NO,    KC_NO,       kp_0,     kp_dot,   k_up,           k_lalt,          KC_NO,   k_f4,  KC_NO   }, \
    /* 1 */ { k_tab,  k_t,   k_y,   k_squarebrcl,    k_f7,     k_squarebrop,  k_backspace,  k_lshift, kp_4,        kp_5,     kp_6,     KC_NO,          KC_NO,           KC_NO,   k_f3,  k_caps  }, \
    /* 2 */ { k_tild, k_5,   k_6,   k_equals,        k_f8,     k_minus,       k_f9,         KC_NO,    k_del,       k_ins,    k_pgup,   k_home,         KC_NO,           k_lctrl, k_f2,  k_f1    }, \
    /* 3 */ { k_1,    k_4,   k_7,   k_8,             k_9,      k_0,           k_f10,        KC_NO,    k_f11,       k_f12,    k_pgdn,   k_end,          k_prscr,         KC_NO,   k_3,   k_2     }, \
    /* 4 */ { k_q,    k_r,   k_u,   k_i,             k_o,      k_p,           KC_NO,        KC_NO,    kp_7,        kp_8,     kp_9,     kp_plus,        k_scrl,          KC_NO,   k_e,   k_w     }, \
    /* 5 */ { k_a,    k_f,   k_j,   k_k,             k_l,      k_semicolon,   k_backsl,     KC_NO,    kp_1,        kp_2,     kp_3,     kp_enter,       KC_NO,           KC_NO,   k_d,   k_s     }, \
    /* 6 */ { k_z,    k_v,   k_m,   k_cm,            k_period, KC_NO,         k_return,     k_rshift, kp_nl,       kp_div,   kp_mult,  k_pause,        KC_NO,           k_rctrl, k_c,   k_x     }, \
    /* 7 */ { KC_NO,  k_b,   k_n,   KC_NO,           KC_NO,    k_fwslash,     k_space,      KC_NO,    k_down,      k_right,  kp_minus, k_left,         k_ralt,          KC_NO,   KC_NO, KC_NO   }  \
}

#define LAYOUT_iso( \
    k_esc,       k_f1, k_f2, k_f3, k_f4,    k_f5, k_f6, k_f7, k_f8,    k_f9, k_f10, k_f11, k_f12,            k_prscr, k_scrl, k_pause, \
    k_tild, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals,               k_backspace,  k_ins,   k_home, k_pgup,     kp_nl,       kp_div, kp_mult, kp_minus,        \
    k_tab,     k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,      k_return,  k_del,   k_end,  k_pgdn,     kp_7,        kp_8,   kp_9,    kp_plus,         \
    k_caps,       k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,                                        kp_4,        kp_5,   kp_6,                     \
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_fwslash,                  k_rshift,           k_up,               kp_1,        kp_2,   kp_3,    kp_enter,        \
    k_lctrl,         k_lalt,                              k_space,                    k_ralt,      k_rctrl,  k_left,  k_down, k_right,          kp_0,          kp_dot                    \
) \
{ \
    /*        0       1      2      3                4         5              6             7         8            9         A         B               C                D        E      F     */ \
    /* 0 */ { k_esc,  k_g,   k_h,   k_f6,            KC_NO,    k_singlequote, k_f5,         KC_NO,    KC_NO,       kp_0,     kp_dot,   k_up,           k_lalt,          KC_NO,   k_f4,  k_nubs  }, \
    /* 1 */ { k_tab,  k_t,   k_y,   k_squarebrcl,    k_f7,     k_squarebrop,  k_backspace,  k_lshift, kp_4,        kp_5,     kp_6,     KC_NO,          KC_NO,           KC_NO,   k_f3,  k_caps  }, \
    /* 2 */ { k_tild, k_5,   k_6,   k_equals,        k_f8,     k_minus,       k_f9,         KC_NO,    k_del,       k_ins,    k_pgup,   k_home,         KC_NO,           k_lctrl, k_f2,  k_f1    }, \
    /* 3 */ { k_1,    k_4,   k_7,   k_8,             k_9,      k_0,           k_f10,        KC_NO,    k_f11,       k_f12,    k_pgdn,   k_end,          k_prscr,         KC_NO,   k_3,   k_2     }, \
    /* 4 */ { k_q,    k_r,   k_u,   k_i,             k_o,      k_p,           KC_NO,        KC_NO,    kp_7,        kp_8,     kp_9,     kp_plus,        k_scrl,          KC_NO,   k_e,   k_w     }, \
    /* 5 */ { k_a,    k_f,   k_j,   k_k,             k_l,      k_semicolon,   KC_NO,        KC_NO,    kp_1,        kp_2,     kp_3,     kp_enter,       KC_NO,           KC_NO,   k_d,   k_s     }, \
    /* 6 */ { k_z,    k_v,   k_m,   k_cm,            k_period, k_nuhs,        k_return,     k_rshift, kp_nl,       kp_div,   kp_mult,  k_pause,        KC_NO,           k_rctrl, k_c,   k_x     }, \
    /* 7 */ { KC_NO,  k_b,   k_n,   KC_NO,           KC_NO,    k_fwslash,     k_space,      KC_NO,    k_down,      k_right,  kp_minus, k_left,         k_ralt,          KC_NO,   KC_NO, KC_NO   }  \
}
