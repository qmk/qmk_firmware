/*
Copyright 2021 CannonKeys LLC

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

#define LAYOUT_all( \
	K0100,        K0101, K0001, K0102, K0002, K0103, K0003, K0104, K0004, K0105, K0005, K0106, K0006, K0107, K0007, K0108, \
    K0300, K0200, K0301, K0201, K0302, K0202, K0303, K0203, K0304, K0204, K0305, K0205, K0306, K0206, K0307, K0207, K0308, \
    K0500, K0400, K0501, K0401, K0502, K0402, K0503, K0403, K0504, K0404, K0505, K0405, K0506, K0406, K0507, K0407, K0508, \
    K0700, K0600, K0701, K0601, K0702, K0602, K0703, K0603, K0704, K0604, K0705, K0605, K0706, K0606,                      \
    K0900, K0800, K0901, K0801, K0902, K0802, K0903, K0803, K0904, K0804, K0905, K0805,        K0806,        K0807,        \
    K1100, K1000, K1101,                      K1103,                      K1105,        K1106, K1006, K1107, K1007, K1108  \
) { \
	{ KC_NO, K0001, K0002, K0003, K0004, K0005, K0006, K0007, KC_NO }, \
	{ K0100, K0101, K0102, K0103, K0104, K0105, K0106, K0107, K0108 }, \
    { K0200, K0201, K0202, K0203, K0204, K0205, K0206, K0207, KC_NO }, \
	{ K0300, K0301, K0302, K0303, K0304, K0305, K0306, K0307, K0308 }, \
    { K0400, K0401, K0402, K0403, K0404, K0405, K0406, K0407, KC_NO }, \
	{ K0500, K0501, K0502, K0503, K0504, K0505, K0506, K0507, K0508 }, \
	{ K0600, K0601, K0602, K0603, K0604, K0605, K0606, KC_NO, KC_NO }, \
	{ K0700, K0701, K0702, K0703, K0704, K0705, K0706, KC_NO, KC_NO }, \
	{ K0800, K0801, K0802, K0803, K0804, K0805, K0806, K0807, KC_NO }, \
	{ K0900, K0901, K0902, K0903, K0904, K0905, KC_NO, KC_NO, KC_NO }, \
	{ K1000, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K1006, K1007, KC_NO }, \
	{ K1100, K1101, KC_NO, K1103, KC_NO, K1105, K1106, K1107, K1108 } \
}
