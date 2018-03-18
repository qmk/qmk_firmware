/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>

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

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include "quantum_keycodes.h"
#include "keycode.h"
#include "action.h"

#define KEYMAP( \
	K500, K502, K503, K504, K505, K600, K610, K710, K700, K511, K512, K513, K514, K113, K214, K013, K706, K709, K708, \
	K400, K401, K402, K403, K404, K405, K601, K611, K711, K701, K410, K411, K412,       K414, K406, K407, K408, K409, \
    K300,   K301, K302, K303, K304, K305, K602, K612, K712, K702, K310, K311, K312,     K313, K306, K307, K308, K309, \
	K200,    K201, K202, K203, K204, K205, K603, K613, K713, K703, K210, K211,          K213, K206, K207, K208, K209, \
	K100,      K101, K102, K103, K104, K105, K604, K614, K714, K704, K110,              K111, K106, K107, K108, K009, \
	K000,   K001,   K002,                    K605,                    K705, K010, K011, K606, K607, K609, K006, K008  \
) { \
	{      K000,       K001,       K002,       KC_NO,      KC_NO,      KC_NO,      K006,       KC_NO,      K008,       K009,       K010,       K011,       KC_NO,      K013,      KC_NO, }, \
	{      K100,       K101,       K102,       K103,       K104,       K105,       K106,       K107,       K108,       KC_NO,      K110,       K111,       KC_NO,      K113,      KC_NO, }, \
	{      K200,       K201,       K202,       K203,       K204,       K205,       K206,       K207,       K208,       K209,       K210,       K211,       KC_NO,      K213,      K214, }, \
	{      K300,       K301,       K302,       K303,       K304,       K305,       K306,       K307,       K308,       K309,       K310,       K311,       K312,       K313,      KC_NO, }, \
	{      K400,       K401,       K402,       K403,       K404,       K405,       K406,       K407,       K408,       K409,       K410,       K411,       K412,       KC_NO,     K414, }, \
	{      K500,       KC_NO,      K502,       K503,       K504,       K505,       KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      K511,       K512,       K513,      K514, }, \
	{      K600,       K601,       K602,       K603,       K604,       K605,       K606,       K607,       KC_NO,      K609,       K610,       K611,       K612,       K613,      K614, }, \
	{      K700,       K701,       K702,       K703,       K704,       K705,       K706,       KC_NO,      K708,       K709,       K710,       K711,       K712,       K713,      K714  } \
}



#endif









