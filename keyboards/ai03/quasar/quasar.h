/* Copyright 2019 Ryota Goto
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K702,       K503, K504, K604, K704,    K706, K708, K609, K509,    K506, K406, K411, K412,    K415, K315, K114, \
	K502, K402, K403, K404, K405, K505, K507, K407, K408, K409, K410, K510, K508,       K606,    K512, K514, K513, \
	K602, K302, K303, K304, K305, K605, K607, K307, K308, K309, K310, K610, K608,       K206,    K511, K414, K413, \
	K603, K202, K203, K204, K205, K705, K707, K207, K208, K209, K210, K710,             K106,                      \
	K601,       K102, K103, K104, K105, K005, K007, K107, K108, K109, K010,             K101,          K714,       \
	K500,       K715,                         K006,                         K015,       K100,    K014, K011, K012  \
) \
{ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K005,  K006,  K007,  KC_NO, KC_NO, K010,  K011,  K012,  KC_NO, K014,  K015  }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  KC_NO, KC_NO, KC_NO, KC_NO, K114,  KC_NO }, \
	{ KC_NO, KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, KC_NO, K302,  K303,  K304,  K305,  KC_NO, K307,  K308,  K309,  K310,  KC_NO, KC_NO, KC_NO, KC_NO, K315  }, \
	{ KC_NO, KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415  }, \
	{ K500,  KC_NO, K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  K512,  K513,  K514,  KC_NO }, \
	{ KC_NO, K601,  K602,  K603,  K604,  K605,  K606,  K607,  K608,  K609,  K610,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, KC_NO, K702,  KC_NO, K704,  K705,  K706,  K707,  K708,  KC_NO, K710,  KC_NO, KC_NO, KC_NO, K714,  K715  }  \
}
