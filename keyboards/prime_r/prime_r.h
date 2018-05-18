/* Copyright 2018 Andrew Heaston
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
#ifndef PRIMER_H
#define PRIMER_H

#include "quantum.h"

#define KEYMAP( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210,       K212, K213, K214, K215, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, \
	K400,       K402, K403, K404, K405,       K407,       K409, K410, K411, K412, K413, K414, K415  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  KC_NO, K212,  K213,  K214,  K215 }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  K315 }, \
	{ K400,  KC_NO, K402,  K403,  K404,  K405,  KC_NO, K407,  KC_NO, K409,  K410,  K411,  K412,  K413,  K414,  K415 }  \
}

#endif