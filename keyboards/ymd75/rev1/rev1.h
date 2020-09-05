/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Wayne Jones (WarmCatUK) <waynekjones@gmail.com>
 
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

#define LAYOUT( \
    K05, K25, K35, K45, K55, K06, KA6, KA7, K07, KB5, KC5, KD5, KE5, KD1, KE1, KE2, \
    K04, K14, K24, K34, K44, K54, K16, KB6, KB7, K17, KA4, KB4, KC4, KE4,      KD0, \
    K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, KC3, KD3,      K67, \
    K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, KB2, KD2,           KE0, \
    K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, KB1,           K86, K77, \
    K00, K10, K20,           K56,                     K57, KB0, KC0, K96, K76, K66  \
){ \
    { K00, K10,   K20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB0, KC0,   KD0,   KC_NO }, \
    { K01, K11,   K21, K31,   K41,   K51,   KC_NO, KC_NO, KC_NO, KC_NO, KA1,   KB1, KC_NO, KD1,   KE1   }, \
    { K02, K12,   K22, K32,   K42,   K52,   KC_NO, KC_NO, KC_NO, KC_NO, KA2,   KB2, KC_NO, KD2,   KE2   }, \
    { K03, K13,   K23, K33,   K43,   K53,   KC_NO, KC_NO, KC_NO, KC_NO, KA3,   KB3, KC3,   KD3,   KC_NO }, \
    { K04, K14,   K24, K34,   K44,   K54,   KC_NO, KC_NO, KC_NO, KC_NO, KA4,   KB4, KC4,   KC_NO, KE4   }, \
    { K05, KC_NO, K25, K35,   K45,   K55,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB5, KC5,   KD5,   KE5   }, \
    { K06, K16,   K26, K36,   K46,   K56,   K66,   K76,   K86,   K96,   KA6,   KB6, KC6,   KD6,   KE6   }, \
    { K07, K17,   K27, K37,   K47,   K57,   K67,   K77,   KE0,   KC_NO, KA7,   KB7, KC7,   KD7,   KE7   } \
}

#define LAYOUT_iso( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K514, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, K513, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,             K214, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K314, \
	K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,       K413, K414, \
	K500, K501, K502,                   K505,                         K506, K508, K509, K510, K511  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  KC_NO, K114 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314 }, \
	{ K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414 }, \
	{ K500,  K501,  K502,  KC_NO, KC_NO, K505,  K506,  KC_NO,  K508,  K509,  K510,  K511,  KC_NO, K513, K514 }  \
}
