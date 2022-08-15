/* Copyright 2022 Tim (https://github.com/Timliuzhaolu)
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

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, \
	K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, \
	K500, K501, K502,                   K506, K507, K508, K509, K510, K511, K512, K513, \
	                                    K606, K607, K608, K609, K610, K611, K612, K613, \
	                                    K706, K707, K708, K709, K710, K711, K712, K713, \
	                                    K806, K807, K808,       K810,       K812  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313 }, \
	{ K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413 }, \
	{ K500,  K501,  K502,  KC_NO, KC_NO, KC_NO, K506,  K507,  K508,  K509,  K510,  K511,  K512,  K513 }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K606,  K607,  K608,  K609,  K610,  K611,  K612,  K613 }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K706,  K707,  K708,  K709,  K710,  K711,  K712,  K713 }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K806,  K807,  K808,  KC_NO, K810,  KC_NO, K812,  KC_NO }  \
}