/*
Copyright 2020 Andy Holland

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT_all( \
    K000,       K001, K002, K003, K004,    K005, K006, K007, K008,    K010, K011, K012, K013,    K014, K015, K016, \
                                                                                                                   \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K113,    K114, K115, K116, \
    K200,    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,             K214, K215, K216, \
    K300,     K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,   K313,                      \
    K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411,             K413,          K415,       \
    K500, K501, K502,                      K506,                      K509, K510, K511, K513,    K514, K515, K516  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  KC_NO, K010,  K011,  K012,  K013,  K014,  K015,  K016  }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115,  K116  }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215,  K216  }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, KC_NO, KC_NO }, \
    { K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  KC_NO, K413,  KC_NO, K415,  KC_NO }, \
    { K500,  K501,  K502,  KC_NO, KC_NO, KC_NO, K506,  KC_NO, KC_NO, K509,  K510,  K511,  KC_NO, K513,  K514,  K515,  K516  }, \
}

#define LAYOUT_tkl_iso LAYOUT_all

#define LAYOUT_ansi( \
	K000, K001, K002, K003, K004, K005,       K007, K008, K009,       K011, K012, K013, K014, K015, K016, K017, \
	                                                                                                            \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, \
	K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414,                   \
	K500,       K502, K503, K504, K505, K506, K507, K508, K509, K510, K511,       K513,             K516,       \
	K600, K601,       K603,             K606,                   K610, K611, K612,       K614, K615, K616, K617  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K007,  K008,  K009,  KC_NO, K011,  K012,  K013,  K014,  K015,  K016,  K017 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K214,  K215,  K216,  K217 }, \
	{ K300,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317 }, \
	{ K400,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  KC_NO, KC_NO, KC_NO }, \
	{ K500,  KC_NO, K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  KC_NO, K513,  KC_NO, K516,  KC_NO }, \
	{ K600,  K601,  K603,  KC_NO, KC_NO, KC_NO, K606,  KC_NO, KC_NO, K610,  K611,  K612,  KC_NO, K614,  K615,  K616,  K617 }  \
}
