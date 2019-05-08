/* Copyright 2019 MechMerlin
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT( \
	K000,       K002, K103, K004, K105, K006, K107, K008, K109,       K111, K012, K113, K014, K115, K016, K117, \
	K200, K301, K202, K303, K204, K305, K206, K307, K208, K309, K210, K311, K212, K313, K214, K315, K216, K317, \
	K400, K501, K402, K503, K404, K505, K406, K507, K408, K509, K410, K511, K412,       K414, K515, K416, K517, \
	K600, K701, K602, K703, K604, K705, K606, K707, K608, K709, K610, K711, K612,       K614,                   \
	K800, K901, K802, K903, K804, K905, K806, K907, K808, K909, K810, K911, K812,       K814,       K816,       \
    K1000,K1101,K1002,                  K1006,                  K1010,K1111,K1012,      K1014,K1115,K1016,K1117\
) { \
	{ K000,   K002,   K004,   K006,   K008,   KC_NO,  K012,   K014,   K016  },\
    { KC_NO,  K103,   K105,   K107,   K109,   K111,   K113,   K115,   K117  },\
	{ K200,   K202,   K204,   K206,   K208,   K210,   K212,   K214,   K216  },\
    { K301,   K303,   K305,   K307,   K309,   K311,   K313,   K315,   K317  },\
	{ K400,   K402,   K404,   K406,   K408,   K410,   K412,   K414,   K416  },\
    { K501,   K503,   K505,   K507,   K509,   K511,   KC_NO,  K515,   K517  },\
	{ K600,   K602,   K604,   K606,   K608,   K610,   K612,   K614,   KC_NO },\
    { K701,   K703,   K705,   K707,   K709,   K711,   KC_NO,  KC_NO,  KC_NO },\
	{ K800,   K802,   K804,   K806,   K808,   K810,   K812,   K814,   K816  },\
    { K901,   K903,   K905,   K907,   K909,   K911,   KC_NO,  KC_NO,  KC_NO },\
    { K1000,  K1002,  KC_NO,  K1006,  KC_NO,  K1010,  K1012,  K1014,  K1016 },\
    { K1101,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  K1111,  KC_NO,  K1115,  K1117 }\
}
