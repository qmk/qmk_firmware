/* Copyright 2020 null-ll
 * Copyright 2021 Jels, Josh Johnson
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

#define ____ KC_NO

#include "quantum.h"

#define LAYOUT_default( \
	  K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,        \
	  K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114, 		 \
	  K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,               \
	         K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K214,        \
	         K401,  K402,         K404,         K406,         K408,         K410,  K411,         K412,  K413,  K314  \
) { \
	{ K000,  K002,  K004,  K006,  K008,  K010,  K012 }, \
	{ K001,  K003,  K005,  K007,  K009,  K011,  K013 }, \
	{ K100,  K102,  K104,  K106,  K108,  K110,  K112 }, \
	{ K101,  K103,  K105,  K107,  K109,  K111,  K113 }, \
	{ K200,  K202,  K204,  K206,  K208,  K210,  K014 }, \
	{ K201,  K203,  K205,  K207,  K209,  K211,  K114 }, \
	{ K301,  K303,  K305,  K307,  K309,  K311,  K212 }, \
	{ K302,  K304,  K306,  K308,  K310,  K312,  K213 }, \
	{ K401,  ____,  K404,  K408,  K411,  K413,  K313 }, \
	{ ____,  K402,  K406,  K410,  K412,  K314,  K214 }  \
}

#define LAYOUT_split_bs( \
	  K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K403, \
	  K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114, 		 \
	  K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,               \
	         K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K214,        \
	         K401,  K402,         K404,         K406,         K408,         K410,  K411,         K412,  K413,  K314  \
) { \
	{ K000,  K002,  K004,  K006,  K008,  K010,  K012 }, \
	{ K001,  K003,  K005,  K007,  K009,  K011,  K013 }, \
	{ K100,  K102,  K104,  K106,  K108,  K110,  K112 }, \
	{ K101,  K103,  K105,  K107,  K109,  K111,  K113 }, \
	{ K200,  K202,  K204,  K206,  K208,  K210,  K014 }, \
	{ K201,  K203,  K205,  K207,  K209,  K211,  K114 }, \
	{ K301,  K303,  K305,  K307,  K309,  K311,  K212 }, \
	{ K302,  K304,  K306,  K308,  K310,  K312,  K213 }, \
	{ K401,  K403,  K404,  K408,  K411,  K413,  K313 }, \
	{ ____,  K402,  K406,  K410,  K412,  K314,  K214 }  \
}
