/* Copyright 2022 Moritz Plattner
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

#define LAYOUT_1800_all( \
	K000, K001, K002, K003, K004,       K006, K007, K008, K009, K010, K011, K012, K013,       K015, K016, K017, K018, \
	                                                                                          K115, K116, K117, K118, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217, K218, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317, K318, \
	K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, \
	K500, K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511,       K513, K514, K515, K516, K517, K518, \
    K600, K601, K602,                   K606,             K609, K610, K611, K612, K613, K614, K615, K616, K617        \
) { \
	{ K000,  K001,  K002,  K003,  K004,  KC_NO, K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO, K015,  K016,  K017,  K018  }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K115,  K116,  K117,  K118  }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215,  K216,  K217,  K218  }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  K315,  K316,  K317,  K318  }, \
	{ K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415,  K416,  K417,  K418  }, \
	{ K500,  K501,  K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  KC_NO, K513,  K514,  K515,  K516,  K517,  K518  }, \
    { K600,  K601,  K602,  KC_NO, KC_NO, KC_NO, K606,  KC_NO, KC_NO, K609,  K610,  K611,  K612,  K613,  K614,  K615,  K616,  K617,  KC_NO }  \
}

#define LAYOUT_1800_iso_6u( \
	K000, K001, K002, K003, K004,       K006, K007, K008, K009, K010, K011, K012, K013,       K015, K016, K017, K018, \
	                                                                                          K115, K116, K117, K118, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217, K218, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, K318, \
	K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, \
	K500, K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511,       K513, K514, K515, K516, K517, K518, \
    K600, K601, K602,                   K606,             K609, K610, K611, K612, K613, K614, K615, K616, K617        \
) { \
	{ K000,  K001,  K002,  K003,  K004,  KC_NO, K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO, K015,  K016,  K017,  K018  }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K115,  K116,  K117,  K118  }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215,  K216,  K217,  K218  }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317,  K318  }, \
	{ K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415,  K416,  K417,  K418  }, \
	{ K500,  K501,  K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  KC_NO, K513,  K514,  K515,  K516,  K517,  K518  }, \
    { K600,  K601,  K602,  KC_NO, KC_NO, KC_NO, K606,  KC_NO, KC_NO, K609,  K610,  K611,  K612,  K613,  K614,  K615,  K616,  K617,  KC_NO }  \
}

#define LAYOUT_1800_iso_7u( \
	K000, K001, K002, K003, K004,       K006, K007, K008, K009, K010, K011, K012, K013,       K015, K016, K017, K018, \
	                                                                                          K115, K116, K117, K118, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217, K218, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, K318, \
	K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, \
	K500, K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511,       K513, K514, K515, K516, K517, K518, \
    K600,       K602,                   K606,             K609,             K612, K613, K614, K615, K616, K617        \
) { \
	{ K000,  K001,  K002,  K003,  K004,  KC_NO, K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO, K015,  K016,  K017,  K018  }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K115,  K116,  K117,  K118  }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215,  K216,  K217,  K218  }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317,  K318  }, \
	{ K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415,  K416,  K417,  K418  }, \
	{ K500,  K501,  K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  KC_NO, K513,  K514,  K515,  K516,  K517,  K518  }, \
    { K600,  KC_NO, K602,  KC_NO, KC_NO, KC_NO, K606,  KC_NO, KC_NO, K609,  KC_NO, KC_NO, K612,  K613,  K614,  K615,  K616,  K617,  KC_NO }  \
}

#define LAYOUT_1800_ansi_6u( \
	K000, K001, K002, K003, K004,       K006, K007, K008, K009, K010, K011, K012, K013,       K015, K016, K017, K018, \
	                                                                                          K115, K116, K117, K118, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217, K218, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317, K318, \
	K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,       K414, K415, K416, K417, K418, \
	K500,       K502, K503, K504, K505, K506, K507, K508, K509, K510, K511,       K513, K514, K515, K516, K517, K518, \
    K600, K601, K602,                   K606,             K609, K610, K611, K612, K613, K614, K615, K616, K617        \
) { \
	{ K000,  K001,  K002,  K003,  K004,  KC_NO, K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO, K015,  K016,  K017,  K018  }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K314,  K115,  K116,  K117,  K118  }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215,  K216,  K217,  K218  }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317,  K318  }, \
	{ K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  KC_NO, K414,  K415,  K416,  K417,  K418  }, \
	{ K500,  KC_NO, K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  KC_NO, K513,  K514,  K515,  K516,  K517,  K518  }, \
    { K600,  K601,  K602,  KC_NO, KC_NO, KC_NO, K606,  KC_NO, KC_NO, K609,  K610,  K611,  K612,  K613,  K614,  K615,  K616,  K617,  KC_NO }  \
}

#define LAYOUT_1800_ansi_7u( \
	K000, K001, K002, K003, K004,       K006, K007, K008, K009, K010, K011, K012, K013,       K015, K016, K017, K018, \
	                                                                                    K314, K115, K116, K117, K118, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217, K218, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, K318, \
	K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,       K414, K415, K416, K417, K418, \
	K500,       K502, K503, K504, K505, K506, K507, K508, K509, K510, K511,       K513, K514, K515, K516, K517, K518, \
    K600,       K602,                   K606,             K609,             K612, K613, K614, K615, K616, K617        \
) { \
	{ K000,  K001,  K002,  K003,  K004,  KC_NO, K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO, K015,  K016,  K017,  K018  }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K314,  K115,  K116,  K117,  K118  }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215,  K216,  K217,  K218  }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317,  K318  }, \
	{ K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  KC_NO, K414,  K415,  K416,  K417,  K418  }, \
	{ K500,  KC_NO, K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  KC_NO, K513,  K514,  K515,  K516,  K517,  K518  }, \
    { K600,  KC_NO, K602,  KC_NO, KC_NO, KC_NO, K606,  KC_NO, KC_NO, K609,  KC_NO, KC_NO, K612,  K613,  K614,  K615,  K616,  K617,  KC_NO }  \
}
