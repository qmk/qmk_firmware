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

#pragma once

#include "quantum.h"

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

#define LAYOUT_iso( \
    K50, K52, K53, K54, K55, K60, K6A, K7A, K70, K5B, K5C, K5D, K5E, K1D, K2E,   K0D, K76, K79, K78, \
    K40, K41, K42, K43, K44, K45, K61, K6B, K7B, K71, K4A, K4B, K4C,      K4E,   K46, K47, K48, K49, \
    K30,   K31, K32, K33, K34, K35, K62, K6C, K7C, K72, K3A, K3B, K3C,    K2D,   K36, K37, K38, K39, \
    K20,    K21, K22, K23, K24, K25, K63, K6D, K7D, K73, K2A, K2B, K2C,          K26, K27, K28, K29, \
    K10, K03, K11, K12, K13, K14, K15, K64, K6E, K7E, K74, K1A,      K1B, K68,   K16, K17, K18, K09, \
    K00,  K01,  K02,               K65,                K75,   K0B,   K66, K67, K69,   K06, K08       \
) { \
    {  K00,  K01,    K02,  K03,  KC_NO,  KC_NO,  K06,    KC_NO,  K08,    K09,    KC_NO,  K0B,  KC_NO,  K0D,    KC_NO  }, \
    {  K10,  K11,    K12,  K13,  K14,    K15,    K16,    K17,    K18,    KC_NO,  K1A,    K1B,  KC_NO,  K1D,    KC_NO  }, \
    {  K20,  K21,    K22,  K23,  K24,    K25,    K26,    K27,    K28,    K29,    K2A,    K2B,  K2C,    K2D,    K2E    }, \
    {  K30,  K31,    K32,  K33,  K34,    K35,    K36,    K37,    K38,    K39,    K3A,    K3B,  K3C,    KC_NO,  KC_NO  }, \
    {  K40,  K41,    K42,  K43,  K44,    K45,    K46,    K47,    K48,    K49,    K4A,    K4B,  K4C,    KC_NO,  K4E    }, \
    {  K50,  KC_NO,  K52,  K53,  K54,    K55,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  K5B,  K5C,    K5D,    K5E    }, \
    {  K60,  K61,    K62,  K63,  K64,    K65,    K66,    K67,    K68,    K69,    K6A,    K6B,  K6C,    K6D,    K6E    }, \
    {  K70,  K71,    K72,  K73,  K74,    K75,    K76,    KC_NO,  K78,    K79,    K7A,    K7B,  K7C,    K7D,    K7E    }  \
}
