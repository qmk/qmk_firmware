/* Copyright 2021 DTIsaac
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
// default keymap: all 117 keys with ANSI Enter
#define LAYOUT( \
	K000,       K001, K002, K003, K300, K301, K302, K303, K306, K307, K308, K309, K310,         K004, K005, K006,    K007, K008, K009, K010, \
	K100, K101, K102, K103, K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410,   K104, K105, K106,    K107, K108, K109, K110, \
	K200, K201, K202, K203, K500, K501, K502, K503, K505, K506, K507, K508, K509, K510,         K204, K205, K206,    K207, K208, K209, K210, \
	K800, K801, K802, K803, K600, K601, K602, K603, K606, K607, K608, K609, K610,                                    K807, K808, K809, K810, \
	K900, K901, K902, K903, K700, K701, K702, K703, K705, K706, K707, K708, K709, K710,               K906,          K907, K908, K909, K910, \
	KA00, KA01, KA02, KA03,       K804, K805, K806,             K604, K605, K904, K905,         KA04, KA05, KA06,    KA07, KA08, KA09, KA10  \
) { \
	{ K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010 }, \
	{ K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110 }, \
	{ K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210 }, \
	{ K300, K301, K302, K303, KC_NO, KC_NO, K306, K307, K308, K309, K310 }, \
	{ K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410 }, \
	{ K500, K501, K502, K503, KC_NO, K505, K506, K507, K508, K509, K510 }, \
	{ K600, K601, K602, K603, K604, K605, K606, K607, K608, K609, K610 }, \
	{ K700, K701, K702, K703, KC_NO, K705, K706, K707, K708, K709, K710 }, \
	{ K800, K801, K802, K803, K804, K805, K806, K807, K808, K809, K810 }, \
	{ K900, K901, K902, K903, K904, K905, K906, K907, K908, K909, K910 }, \
	{ KA00, KA01, KA02, KA03, KA04, KA05, KA06, KA07, KA08, KA09, KA10 }  \
}
