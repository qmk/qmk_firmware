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

// Note: unused columns 8..14 are not listed here. Column 15 is listed here as column 8
// Note arguments representing the layout are named based on default F77 hhkb split backspace configuration, for other layouts argument naming might not make much sense
// This was done for ease of implementation.

#define LAYOUT_all( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,     \
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_backspace,       \
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_hashtag, k_return, \
    k_lshift, k_nonusbs, k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,   \
    k_caps, k_lgui, k_lalt,         k_space,                 k_extrakey,      k_ralt, k_numlock, k_rctrl     \
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backtick,   KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        k_backslash,  KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         k_hashtag,      k_backspace,  KC_NO},\
    { k_nonusbs,k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        k_extrakey,     k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_ansi_regular_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        KC_NO,        KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_caps,   k_a,    k_e, k_t,     k_u, k_o,         KC_NO,          k_backslash,  KC_NO},\
    { KC_NO,    k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, KC_NO,        KC_NO},\
    { k_lctrl,  k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_fn},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_rshift,     KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_ansi_regular_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backtick, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_backslash,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        k_backtick,   KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_caps,   k_a,    k_e, k_t,     k_u, k_o,         KC_NO,          k_backslash,  KC_NO},\
    { KC_NO,    k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, KC_NO,        KC_NO},\
    { k_lctrl,  k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_fn},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_rshift,     KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_ansi_hhkb_split_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_backslash,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        KC_NO,        KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         KC_NO,          k_backslash,  KC_NO},\
    { KC_NO,    k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_ansi_hhkb_split_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_backspace,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backtick,   KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        k_backslash,  KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         KC_NO,          k_backspace,  KC_NO},\
    { KC_NO,    k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_ansi_nonhhkb_split_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_backslash,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        KC_NO,        KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         KC_NO,          k_backslash,  KC_NO},\
    { KC_NO,    k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_ansi_nonhhkb_split_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_backspace,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_return,\
    k_lshift,    k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backtick,   KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        k_backslash,  KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         KC_NO,          k_backspace,  KC_NO},\
    { KC_NO,    k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_iso_regular_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_return,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        KC_NO,        KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_caps,   k_a,    k_e, k_t,     k_u, k_o,         k_nuhs,         KC_NO,        KC_NO},\
    { k_nubs,   k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, KC_NO,        KC_NO},\
    { k_lctrl,  k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_fn},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_rshift,     KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_iso_regular_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backtick, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl, k_return,\
    k_caps,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift,\
    k_lctrl, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_fn\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        k_backtick,   KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_caps,   k_a,    k_e, k_t,     k_u, k_o,         k_nuhs,         KC_NO,        KC_NO},\
    { k_nubs,   k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, KC_NO,        KC_NO},\
    { k_lctrl,  k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_fn},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_rshift,     KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_iso_hhkb_split_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_return,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        KC_NO,        KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         k_nuhs,         KC_NO,        KC_NO},\
    { k_nubs,   k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_iso_hhkb_split_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_return,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backtick,   KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        k_backslash,  KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         k_nuhs,         KC_NO,        KC_NO},\
    { k_nubs,   k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_iso_nonhhkb_split_shift_regular_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backspace,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_return,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backspace,  KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        KC_NO,        KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         k_nuhs,         KC_NO,        KC_NO},\
    { k_nubs,   k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}

#define LAYOUT_iso_nonhhkb_split_shift_split_backspace( \
    k_esc, k_1, k_2, k_3, k_4, k_5, k_6, k_7, k_8, k_9, k_0, k_minus, k_equals, k_backslash, k_backtick,\
    k_tab,   k_q, k_w, k_e, k_r, k_t, k_y, k_u, k_i, k_o, k_p, k_squarebrop, k_squarebrcl,k_return,\
    k_lctrl,   k_a, k_s, k_d, k_f, k_g, k_h, k_j, k_k, k_l, k_semicolon, k_singlequote, k_nuhs,\
    k_lshift,k_nubs,k_z, k_x, k_c, k_v, k_b, k_n, k_m, k_cm,k_period, k_forwardslash, k_rshift, k_fn,\
    k_caps, k_lgui, k_lalt,         k_space,                 k_ralt                , k_numlock, k_rctrl\
) \
{ \
    { k_1,      k_2,    k_4, k_6,     k_8, k_0,         k_equals,       k_backtick,   KC_NO},\
    { k_esc,    k_q,    k_3, k_5,     k_7, k_9,         k_minus,        k_backslash,  KC_NO},\
    { k_tab,    k_w,    k_r, k_y,     k_i, k_p,         k_squarebrop,   k_squarebrcl, KC_NO},\
    { k_lctrl,  k_a,    k_e, k_t,     k_u, k_o,         k_nuhs,         KC_NO,        KC_NO},\
    { k_nubs,   k_x,    k_d, k_g,     k_k, k_l,         k_forwardslash, k_rshift,     KC_NO},\
    { k_caps,   k_lalt, k_v, k_space, k_m, k_cm,        KC_NO,          k_numlock,    k_rctrl},\
    { k_lgui,   k_z,    k_c, k_b,     k_n, k_period,    k_ralt,         k_fn,         KC_NO},\
    { k_lshift, k_s,    k_f, k_h,     k_j, k_semicolon, k_singlequote,  k_return,     KC_NO}\
}
