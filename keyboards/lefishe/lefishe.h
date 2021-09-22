/* Copyright 2020 Lyso1
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

#define LAYOUT_default( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015,       K017, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,       K116, K117, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,             K216, K217, \
	K300, K301, K302,       K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, \
	K400, K401, K402, K403, K404,                   K408,                         K413,       K415, K416, K417  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  KC_NO, K017 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  KC_NO, K116,  K117 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO, KC_NO, K216,  K217 }, \
	{ K300,  K301,  K302,  KC_NO, K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317 }, \
	{ K400,  K401,  K402,  K403,  K404,  KC_NO, KC_NO, KC_NO, K408,  KC_NO, KC_NO, KC_NO, KC_NO, K413,  KC_NO, K415,  K416,  K417 }  \
}

#define LAYOUT_wk_sbs( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, K016, K017, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,       K116, K117, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,             K216, K217, \
	K300, K301, K302,       K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, \
	K400, K401, K402, K403, K404,                   K408,                         K413,       K415, K416, K417  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  KC_NO, K116,  K117 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO, KC_NO, K216,  K217 }, \
	{ K300,  K301,  K302,  KC_NO, K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317 }, \
	{ K400,  K401,  K402,  K403,  K404,  KC_NO, KC_NO, KC_NO, K408,  KC_NO, KC_NO, KC_NO, KC_NO, K413,  KC_NO, K415,  K416,  K417 }  \
}

#define LAYOUT_wkl_sbs( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, K016, K017, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,       K116, K117, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,             K216, K217, \
	K300, K301, K302,       K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, \
	K400, K401, K402,       K404,                   K408,                         K413,       K415, K416, K417  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  KC_NO, K116,  K117 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO, KC_NO, K216,  K217 }, \
	{ K300,  K301,  K302,  KC_NO, K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317 }, \
	{ K400,  K401,  K402,  KC_NO, K404,  KC_NO, KC_NO, KC_NO, K408,  KC_NO, KC_NO, KC_NO, KC_NO, K413,  KC_NO, K415,  K416,  K417 }  \
}

#define LAYOUT_wkl( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015,       K017, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,       K116, K117, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,             K216, K217, \
	K300, K301, K302,       K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, K316, K317, \
	K400, K401, K402,       K404,                   K408,                         K413,       K415, K416, K417  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  KC_NO, K017 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  KC_NO, K116,  K117 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO, KC_NO, K216,  K217 }, \
	{ K300,  K301,  K302,  KC_NO, K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315,  K316,  K317 }, \
	{ K400,  K401,  K402,  KC_NO, K404,  KC_NO, KC_NO, KC_NO, K408,  KC_NO, KC_NO, KC_NO, KC_NO, K413,  KC_NO, K415,  K416,  K417 }  \
}
