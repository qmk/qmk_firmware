/* Copyright 2018 John M Daly
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

// This a shortcut to help you visually see your layout.
// The following is a layout that uses all available switch positions.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_all( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
    K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
    K400, K401, K402,       K404,       K406,       K408,       K410, K411, K412, K413, K414 \
) \
{ \
    { K000, K001,   K002, K003,  K004, K005,  K006, K007,  K008, K009,  K010, K011, K012,  K013, K014 }, \
    { K100, KC_NO,  K102, K103,  K104, K105,  K106, K107,  K108, K109,  K110, K111, K112,  K113, K114 }, \
    { K200, KC_NO,  K202, K203,  K204, K205,  K206, K207,  K208, K209,  K210, K211, K212,  K213, K214 }, \
    { K300, K301,   K302, K303,  K304, K305,  K306, K307,  K308, K309,  K310, K311, KC_NO, K313, K314 }, \
    { K400, K401,   K402, KC_NO, K404, KC_NO, K406, KC_NO, K408, KC_NO, K410, K411, K412,  K413, K414 }, \
}

#define LAYOUT_60_ansi( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, \
    K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313,       \
    K400, K401, K402,                   K406,                   K410, K411,       K413, K414 \
) \
{ \
    { K000, K001,  K002, K003,  K004,  K005,  K006, K007,  K008, K009,   K010, K011, K012,  KC_NO,  K014 }, \
    { K100, KC_NO, K102, K103,  K104,  K105,  K106, K107,  K108, K109,   K110, K111, K112,  K113,   K114 }, \
    { K200, KC_NO, K202, K203,  K204,  K205,  K206, K207,  K208, K209,   K210, K211, K212,  KC_NO,  K214 }, \
    { K300, KC_NO, K302, K303,  K304,  K305,  K306, K307,  K308, K309,   K310, K311, KC_NO, K313,   KC_NO }, \
    { K400, K401,  K402, KC_NO, KC_NO, KC_NO, K406, KC_NO, KC_NO, KC_NO, K410, K411, KC_NO, K413,   K414 }, \
}

#define LAYOUT_60_ansi_split_bs_rshift( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
    K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
    K400, K401, K402,                   K406,                   K410, K411,       K413, K414 \
) \
{ \
    { K000, K001,  K002, K003,  K004,  K005,  K006, K007,  K008, K009,   K010, K011, K012,  K013,   K014 }, \
    { K100, KC_NO, K102, K103,  K104,  K105,  K106, K107,  K108, K109,   K110, K111, K112,  K113,   K114 }, \
    { K200, KC_NO, K202, K203,  K204,  K205,  K206, K207,  K208, K209,   K210, K211, K212,  KC_NO,  K214 }, \
    { K300, KC_NO, K302, K303,  K304,  K305,  K306, K307,  K308, K309,   K310, K311, KC_NO, K313,   K314 }, \
    { K400, K401,  K402, KC_NO, KC_NO, KC_NO, K406, KC_NO, KC_NO, KC_NO, K410, K411, KC_NO, K413,   K414 }, \
}

#define LAYOUT_60_iso( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, \
    K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313,       \
    K400, K401, K402,                   K406,                   K410, K411,       K413, K414 \
) \
{ \
    { K000, K001,  K002, K003,  K004,  K005,  K006, K007,  K008,  K009,  K010, K011, K012,  KC_NO, K014 }, \
    { K100, KC_NO, K102, K103,  K104,  K105,  K106, K107,  K108,  K109,  K110, K111, K112,  K113,  KC_NO }, \
    { K200, KC_NO, K202, K203,  K204,  K205,  K206, K207,  K208,  K209,  K210, K211, K212,  K213,  K214 }, \
    { K300, K301,  K302, K303,  K304,  K305,  K306, K307,  K308,  K309,  K310, K311, KC_NO, K313,  KC_NO }, \
    { K400, K401,  K402, KC_NO, KC_NO, KC_NO, K406, KC_NO, KC_NO, KC_NO, K410, K411, KC_NO, K413,  K414 }, \
}

#define LAYOUT_60_hhkb( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
    K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
          K401, K402,                   K406,                         K411,       K413      \
) \
{ \
    { K000,  K001,   K002, K003,  K004,  K005,  K006, K007,  K008,  K009,  K010, K011, K012,  K013,  K014 }, \
    { K100,  KC_NO,  K102, K103,  K104,  K105,  K106, K107,  K108,  K109,  K110, K111, K112,  K113,  K114 }, \
    { K200,  KC_NO,  K202, K203,  K204,  K205,  K206, K207,  K208,  K209,  K210, K211, K212,  KC_NO, K214 }, \
    { K300,  KC_NO,  K302, K303,  K304,  K305,  K306, K307,  K308,  K309,  K310, K311, KC_NO, K313,  K314 }, \
    { KC_NO, K401,   K402, KC_NO, KC_NO, KC_NO, K406, KC_NO, KC_NO, KC_NO, KC_NO, K411, KC_NO, K413, KC_NO }, \
}

#define LAYOUT_60_hhkb_split_space( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
    K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
          K401, K402,       K404,       K406,       K408,             K411,       K413      \
) \
{ \
    { K000,  K001,   K002, K003,  K004, K005,  K006, K007,  K008, K009,  K010, K011, K012,  K013,  K014 }, \
    { K100,  KC_NO,  K102, K103,  K104, K105,  K106, K107,  K108, K109,  K110, K111, K112,  K113,  K114 }, \
    { K200,  KC_NO,  K202, K203,  K204, K205,  K206, K207,  K208, K209,  K210, K211, K212,  KC_NO, K214 }, \
    { K300,  KC_NO,  K302, K303,  K304, K305,  K306, K307,  K308, K309,  K310, K311, KC_NO, K313,  K314 }, \
    { KC_NO, K401,   K402, KC_NO, K404, KC_NO, K406, KC_NO, K408, KC_NO, KC_NO, K411, KC_NO, K413, KC_NO }, \
}

#define LAYOUT_60_hhkb_split_625u_space( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
    K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
          K401, K402,       K404,       K406,       K408,       K410, K411,       K413      \
) \
{ \
    { K000,  K001,   K002, K003,  K004, K005,  K006, K007,  K008, K009,  K010, K011, K012,  K013,  K014 }, \
    { K100,  KC_NO,  K102, K103,  K104, K105,  K106, K107,  K108, K109,  K110, K111, K112,  K113,  K114 }, \
    { K200,  KC_NO,  K202, K203,  K204, K205,  K206, K207,  K208, K209,  K210, K211, K212,  KC_NO, K214 }, \
    { K300,  KC_NO,  K302, K303,  K304, K305,  K306, K307,  K308, K309,  K310, K311, KC_NO, K313,  K314 }, \
    { KC_NO, K401,   K402, KC_NO, K404, KC_NO, K406, KC_NO, K408, KC_NO, K410, K411, KC_NO, K413, KC_NO }, \
}
