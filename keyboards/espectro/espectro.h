/* Copyright 2018 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
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


#ifndef ESPECTRO_H
#define ESPECTRO_H

#include "quantum.h"


//Arrow keys and 1.75u shift
#define LAYOUT_default( \
K000, K001, K002, K003, K004, K600, K601, K602, K603, K005, K006, K007, K008, K702, K009, K010, K011, K012, K712,  \
K100, K101, K102, K103, K104, K604, K605, K606, K607, K105, K106, K107, K108,    K701,    K109, K110, K111, K112,  \
  K200,   K201, K202, K203, K204, K608, K609, K610, K611, K205, K206, K207, K208,  K703,  K209, K210, K211, K212,  \
  K300,    K301, K302, K303, K304, K612, K705, K706, K707, K305, K306, K307,    K308,     K309, K310, K311,        \
   K400,    K402, K403, K404, K708, K709, K710, K711, K405, K406,  K407,  K408,     K704, K409, K410, K411, K412,  \
K500, K501, K502,                K509,                      K505, K506, K507, K508, K503, K504, K510, K511         \
) { \
	{ K000,   K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011,   K012 },  \
	{ K100,   K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,   K111,   K112 },  \
	{ K200,   K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,   K211,   K212 },  \
	{ K300,   K301,   K302,   K303,   K304,   K305,   K306,   K307,   K308,   K309,   K310,   K311,   KC_NO }, \
	{ K400,   KC_NO,  K402,   K403,   K404,   K405,   K406,   K407,   K408,   K409,   K410,   K411,   K412 },  \
	{ K500,   K501,   K502,   K503,   K504,   K505,   K506,   K507,   K508,   K509,   K510,   K511,   KC_NO }, \
	{ K600,   K601,   K602,   K603,   K604,   K605,   K606,   K607,   K608,   K609,   K610,   K611,   K612 },  \
	{ KC_NO,  K701,   K702,   K703,   K704,   K705,   K706,   K707,   K708,   K709,   K710,   K711,   K712 },  \
}

// Split numpad (enter, 0), split shifts (right, left), split backspace
// This is more of an example of every possible keycode placement
#define LAYOUT_split_shift_and_bs( \
K000, K001, K002, K003, K004, K600, K601, K602, K603, K005, K006, K007, K008, K702, K009, K010, K011, K012, K712,  \
K100, K101, K102, K103, K104, K604, K605, K606, K607, K105, K106, K107, K108, K700, K701, K109, K110, K111, K112,  \
  K200,   K201, K202, K203, K204, K608, K609, K610, K611, K205, K206, K207, K208,  K703,  K209, K210, K211, K212,  \
  K300,    K301, K302, K303, K304, K612, K705, K706, K707, K305, K306, K307,    K308,     K309, K310, K311, K312,  \
    K400, K401, K402, K403, K404, K708, K709, K710, K711, K405, K406, K407,   K408, K704, K409, K410, K411, K412,  \
K500, K501, K502,                K509,                      K505, K506, K507, K508, K503, K504, K510, K511, K512   \
) { \
	{ K000,   K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011,   K012 },  \
	{ K100,   K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,   K111,   K112 },  \
	{ K200,   K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,   K211,   K212 },  \
	{ K300,   K301,   K302,   K303,   K304,   K305,   K306,   K307,   K308,   K309,   K310,   K311,   K312 },  \
	{ K400,   K401,   K402,   K403,   K404,   K405,   K406,   K407,   K408,   K409,   K410,   K411,   K412 },  \
	{ K500,   K501,   K502,   K503,   K504,   K505,   K506,   K507,   K508,   K509,   K510,   K511,   K512 },  \
	{ K600,   K601,   K602,   K603,   K604,   K605,   K606,   K607,   K608,   K609,   K610,   K611,   K612 },  \
	{ K701,   K701,   K702,   K703,   K704,   K705,   K706,   K707,   K708,   K709,   K710,   K711,   K712 },  \
}




/*
Placement of every possible switch defined below.
x2 means the diode allows two possible positions for the switch

#define LAYOUT_all( \
K000, K001, K002, K003, K004, K600, K601, K602, K603, K005, K006, K007, K008, K702, K009, K010, K011, K012, K712, \
K100, K101, K102, K103, K104, K604, K605, K606, K607, K105, K106, K107, K108, K700, K701x2, K109, K110, K111, K112, \
K200, K201, K202, K203, K204, K608, K609, K610, K611, K205, K206, K207, K208,     K703,   K209, K210, K211, K212, \
                                                                                  K308,                     K212, \
K300, K300, K301, K302, K304, K612, K705, K706, K707, K305, K306, K307,   K703, K308,     K309, K310, K311, K312, \
K400x2, K401, K402, K403, K404, K708, K709, K710, K711, K405, K406, K407, K408, K408, K704, K409, K410, K411, K412, \
                                                                                                            K412, \
K500x2, K501x2, K502,           K509x3,                 K505x3, K506x2, K507x2, K508x2, K503x2, K504, K510x2, K511, K512  \
)  { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312 }, \
	{ K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412 }, \
	{ K500,  K501,  K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  K512 }, \
	{ K600,  K601,  K602,  K603,  K604,  K605,  K606,  K607,  K608,  K609,  K610,  K611,  K612 }, \
	{ K700,  K701,  K702,  K703,  K704,  K705,  K706,  K707,  K708,  K709,  K710,  K711,  K712 }, \
}
*/

#endif
