/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 harshit goel
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

#include "quantum.h"
#include "quantum_keycodes.h"
#include "keycode.h"
#include "action.h"

void matrix_init_user(void);  // TODO port this to other PS2AVRGB boards

#define LAYOUT_default( \
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

#define LAYOUT_custom( \
	K500, K502, K503, K504, K505, K600, K610, K710, K700, K511, K512, K513, K514, K113, K214, K013, K706, K709, K708, \
	K400, K401, K402, K403, K404, K405, K601, K611, K711, K701, K410, K411, K412,       K414, K406, K407, K408, K409, \
    K300,   K301, K302, K303, K304, K305, K602, K612, K712, K702, K310, K311, K312,     K313, K306, K307, K308, K309, \
	K200,    K201, K202, K203, K204, K205, K603, K613, K713, K703, K210, K211,          K213, K206, K207, K208, K209, \
	K100,      K101, K102, K103, K104, K105, K604, K614, K714, K704, K110,              K111, K608,K106, K107, K108, K009, \
	K000,   K001,   K002,                    K605,                    K705, K010, K011, K606, K607,  K006, K008  \
) { \
	{      K000,       K001,       K002,       KC_NO,      KC_NO,      KC_NO,      K006,       KC_NO,      K008,       K009,       K010,       K011,       KC_NO,      K013,      KC_NO, }, \
	{      K100,       K101,       K102,       K103,       K104,       K105,       K106,       K107,       K108,       KC_NO,      K110,       K111,       KC_NO,      K113,      KC_NO, }, \
	{      K200,       K201,       K202,       K203,       K204,       K205,       K206,       K207,       K208,       K209,       K210,       K211,       KC_NO,      K213,      K214, }, \
	{      K300,       K301,       K302,       K303,       K304,       K305,       K306,       K307,       K308,       K309,       K310,       K311,       K312,       K313,      KC_NO, }, \
	{      K400,       K401,       K402,       K403,       K404,       K405,       K406,       K407,       K408,       K409,       K410,       K411,       K412,       KC_NO,     K414, }, \
	{      K500,       KC_NO,      K502,       K503,       K504,       K505,       KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      K511,       K512,       K513,      K514, }, \
	{      K600,       K601,       K602,       K603,       K604,       K605,       K606,       K607, K608,      KC_NO,       K610,       K611,       K612,       K613,      K614, }, \
	{      K700,       K701,       K702,       K703,       K704,       K705,       K706,       KC_NO,      K708,       K709,       K710,       K711,       K712,       K713,      K714  } \
}

#define LAYOUT_jj50( \
K011, K010, K009, K008, K004, K005, K006, K007, K003, K002, K201, K000, \
K111, K110, K109, K108, K104, K105, K106, K107, K103, K102, K001, K100, \
K211, K210, K209, K208, K204, K205, K206, K207, K203, K202, K101, K200, \
K311, K310, K309, K308, K304, K305, K306, K307, K303, K302, K301, K300, \
K411, K410, K409, K408, K404, K405, K406, K407, K403, K402, K401, K400  \
) { \
{      K100,       K001,       K102,       K103,       K104,       K105,       K106,       K107,       K108,       K109,       K110,       K111, }, \
{      K200,       K101,       K202,       K203,       K204,       K205,       K206,       K207,       K208,       K209,       K210,       K211, }, \
{      K000,       K201,       K002,       K003,       K004,       K005,       K006,       K007,       K008,       K009,       K010,       K011, }, \
{      K300,       K301,       K302,       K303,       K304,       K305,       K306,       K307,       K308,       K309,       K310,       K311, }, \
{      K400,       K401,       K402,       K403,       K404,       K405,       K406,       K407,       K408,       K409,       K410,       K411 },  \
}

#define LAYOUT_iso( \
	K0500, K0502, K0503, K0504, K0505, K0600, K0610, K0710, K0700, K0511, K0512, K0513, K0514, K0113, K0214, K0013, K0706, K0709, K0708, \
	K0400, K0401, K0402, K0403, K0404, K0405, K0601, K0611, K0711, K0701, K0410, K0411, K0412,     K0414,    K0406, K0407, K0408, K0409, \
	  K0300,  K0301, K0302, K0303, K0304, K0305, K0602, K0612, K0712, K0702, K0310, K0311, K0312,   K0213,   K0306, K0307, K0308, K0309, \
	    K0200,   K0201, K0202, K0203, K0204, K0205, K0603, K0613, K0713, K0703, K0210, K0211, K0212,         K0206, K0207, K0208, K0209, \
	  K0100,  K0003, K0101, K0102, K0103, K0104, K0105, K0604, K0614, K0714, K0704, K0110,   K0111,   K0608, K0106, K0107, K0108, K0009, \
	  K0000,  K0001,  K0002,                 K0605,                          K0705,   K0011,   K0606, K0607, K0609, K0006, K0008         \
) { \
	{ K0000, K0001, K0002, K0003, KC_NO, KC_NO, K0006, KC_NO, K0008, K0009, KC_NO, K0011, KC_NO, K0013, KC_NO, }, \
	{ K0100, K0101, K0102, K0103, K0104, K0105, K0106, K0107, K0108, KC_NO, K0110, K0111, KC_NO, K0113, KC_NO, }, \
	{ K0200, K0201, K0202, K0203, K0204, K0205, K0206, K0207, K0208, K0209, K0210, K0211, K0212, K0213, K0214, }, \
	{ K0300, K0301, K0302, K0303, K0304, K0305, K0306, K0307, K0308, K0309, K0310, K0311, K0312, KC_NO, KC_NO, }, \
	{ K0400, K0401, K0402, K0403, K0404, K0405, K0406, K0407, K0408, K0409, K0410, K0411, K0412, KC_NO, K0414, }, \
	{ K0500, KC_NO, K0502, K0503, K0504, K0505, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0511, K0512, K0513, K0514, }, \
	{ K0600, K0601, K0602, K0603, K0604, K0605, K0606, K0607, K0608, K0609, K0610, K0611, K0612, K0613, K0614, }, \
	{ K0700, K0701, K0702, K0703, K0704, K0705, K0706, KC_NO, K0708, K0709, K0710, K0711, K0712, K0713, K0714  }  \
}

#endif
