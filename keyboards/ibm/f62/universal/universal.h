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

#define LAYOUT_default( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_braces, k_return,\
    k_lshift,k_nonusbs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, KC_NO, k_backspace,         \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash,     \
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_braces, k_return,  \
    k_lshift, k_nonusbs, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, KC_NO, k_rshift, \
    k_lctrl, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_fn      \
)

#define LAYOUT_all( \
    k_2_1_esc, k_1_1_1, k_1_2_2, k_2_3_3, k_1_3_4, k_2_4_5, k_1_4_6, k_2_5_7, k_1_5_8, k_2_6_9, k_1_6_0, k_2_7_minus, k_1_7_equals, k_2_8_backslash, k_1_8_backtick,     \
    k_3_1_tab,   k_2_2_q, k_3_2_w, k_4_3_e, k_3_3_r, k_4_4_t, k_3_4_y, k_4_5_u, k_3_5_i, k_4_6_o, k_3_6_p, k_3_7_squarebrop, k_3_8_squarebrcl,k_4_8_backspace,       \
    k_4_1_lctrl,   k_4_2_a, k_5_2_s, k_6_3_d, k_5_3_f, k_6_4_g, k_5_4_h, k_5_5_j, k_6_5_k, k_6_6_l, k_5_6_semicolon, k_5_7_singlequote, k_4_7_hashtag, k_5_8_return, \
    k_5_1_lshift, k_6_1_nonusbs, k_7_2_z, k_6_2_x, k_7_3_c, k_8_3_v, k_7_4_b, k_7_5_n, k_8_5_m, k_8_6_cm,k_7_6_period, k_6_7_forwardslash, k_6_8_rshift, k_7_8_fn,   \
    k_8_1_caps, k_7_1_lgui, k_8_2_lalt,         k_8_4_space,                                  k_8_7_ralt, k_7_7_numlock, k_8_8_rctrl     \
) \
{ \
    { k_1_1_1,      k_1_2_2,    k_1_3_4, k_1_4_6,     k_1_5_8, k_1_6_0,         k_1_7_equals,       k_1_8_backtick   },\
    { k_2_1_esc,    k_2_2_q,    k_2_3_3, k_2_4_5,     k_2_5_7, k_2_6_9,         k_2_7_minus,        k_2_8_backslash  },\
    { k_3_1_tab,    k_3_2_w,    k_3_3_r, k_3_4_y,     k_3_5_i, k_3_6_p,         k_3_7_squarebrop,   k_3_8_squarebrcl },\
    { k_4_1_lctrl,  k_4_2_a,    k_4_3_e, k_4_4_t,     k_4_5_u, k_4_6_o,         k_4_7_hashtag,      k_4_8_backspace  },\
    { k_5_1_lshift, k_5_2_s,    k_5_3_f, k_5_4_h,     k_5_5_j, k_5_6_semicolon, k_5_7_singlequote,  k_5_8_return     },\
    { k_6_1_nonusbs,k_6_2_x,    k_6_3_d, k_6_4_g,     k_6_5_k, k_6_6_l,         k_6_7_forwardslash, k_6_8_rshift     },\
    { k_7_1_lgui,   k_7_2_z,    k_7_3_c, k_7_4_b,     k_7_5_n, k_7_6_period,    k_7_7_numlock,      k_7_8_fn         },\
    { k_8_1_caps,   k_8_2_lalt, k_8_3_v, k_8_4_space, k_8_5_m, k_8_6_cm,        k_8_7_ralt,         k_8_8_rctrl      }\
}

#define LAYOUT_ansi_regular_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, KC_NO, k_backspace,     \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash, \
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, KC_NO, k_return, \
    k_lshift, KC_NO, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, KC_NO, k_rshift, \
    k_lctrl, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_fn  \
)

#define LAYOUT_ansi_regular_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backtick, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backtick, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash, \
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, KC_NO, k_return, \
    k_lshift, KC_NO, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, KC_NO, k_rshift, \
    k_lctrl, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_fn  \
)

#define LAYOUT_ansi_nonhhkb_split_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_backslash,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, KC_NO, k_backspace,      \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash,  \
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, KC_NO, k_return, \
    k_lshift, KC_NO, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,   \
    k_caps, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_rctrl \
)

#define LAYOUT_ansi_nonhhkb_split_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_backspace,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick, \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backspace,  \
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, KC_NO, k_return, \
    k_lshift, KC_NO, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,   \
    k_caps, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_rctrl \
)

#define LAYOUT_iso_regular_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_return,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, KC_NO, k_backspace,      \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, KC_NO,        \
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs, k_return, \
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, KC_NO, k_rshift,   \
    k_lctrl, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_fn   \
)

#define LAYOUT_iso_regular_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backtick, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_return,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backtick, k_backspace, \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, KC_NO,        \
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs, k_return, \
    k_lshift, k_nubs, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, KC_NO, k_rshift, \
    k_lctrl, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_fn   \
)

#define LAYOUT_iso_nonhhkb_split_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_return,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, KC_NO, k_backspace,       \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, KC_NO,         \
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs, k_return, \
    k_lshift, k_nubs, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,   \
    k_caps, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_rctrl  \
)

#define LAYOUT_iso_nonhhkb_split_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_return,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,  \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, KC_NO,         \
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs, k_return, \
    k_lshift,k_nubs, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,    \
    k_caps, k_lgui, k_lalt,         k_space,                                  k_ralt, k_numlock, k_rctrl  \
)
