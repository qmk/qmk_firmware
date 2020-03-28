/* Copyright 2020 Ryota Goto
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
	K000, K001, K002,         K004,       K006, K007, K008, K009,    K010, K011, K012, K013,    K014, K015, K016, K017,   K019, K020, K021, \
	K100, K101, K102, K103,   K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118,   K119, K120, K121, \
	K200, K201, K202, K203,   K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216,       K217,   K219, K220, K221, \
	K300, K301, K302, K303,   K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315,       K316, K317,                     \
	K400, K401, K402, K403,   K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415,       K416, K418,         K420,       \
	K500, K501, K502, K503,   K504, K505, K506,                       K510,                     K513, K514, K515, K516,   K519, K520, K521  \
) \
{ \
	{ K000,  K001,  K002,  KC_NO, K004,  KC_NO, K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  KC_NO, K019,  K020,  K021  }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117,  K118,  K119,  K120,  K121  }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214,  K215,  K216,  K217,  KC_NO, K219,  K220,  K221  }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  K315,  K316,  K317,  KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415,  K416,  KC_NO, K418,  KC_NO, K420,  KC_NO }, \
	{ K500,  K501,  K502,  K503,  K504,  K505,  K506,  KC_NO, KC_NO, KC_NO, K510,  KC_NO, KC_NO, K513,  K514,  K515,  K516,  KC_NO, KC_NO, K519,  K520,  K521  }  \
}

#define LAYOUT_ansi_wkl( \
	K000, K001, K002,         K004,       K006, K007, K008, K009,    K010, K011, K012, K013,    K014, K015, K016, K017,   K019, K020, K021, \
	K100, K101, K102, K103,   K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118,   K119, K120, K121, \
	K200, K201, K202, K203,   K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216,       K217,   K219, K220, K221, \
	K300, K301, K302, K303,   K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315,             K317,                     \
	K400, K401, K402, K403,   K404,       K406, K407, K408, K409, K410, K411, K412, K413, K414, K415,       K416, K418,         K420,       \
	K500, K501, K502, K503,   K504, K505, K506,                       K510,                           K514, K515, K516,   K519, K520, K521  \
) \
{ \
	{ K000,  K001,  K002,  KC_NO, K004,  KC_NO, K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  KC_NO, K019,  K020,  K021  }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117,  K118,  K119,  K120,  K121  }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214,  K215,  K216,  K217,  KC_NO, K219,  K220,  K221  }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  K315,  KC_NO, K317,  KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K400,  K401,  K402,  K403,  K404,  KC_NO, K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415,  K416,  KC_NO, K418,  KC_NO, K420,  KC_NO }, \
	{ K500,  K501,  K502,  K503,  K504,  K505,  K506,  KC_NO, KC_NO, KC_NO, K510,  KC_NO, KC_NO, KC_NO, K514,  K515,  K516,  KC_NO, KC_NO, K519,  K520,  K521  }  \
}








