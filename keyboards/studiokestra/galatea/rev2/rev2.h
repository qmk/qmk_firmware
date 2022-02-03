/* Copyright 2021 Studio Kestra
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
#define LAYOUT_all(\
    k0000, k0100,        k0001, k0002, k0102, k0003, k0103, k0004, k0104, k0005, k0105, k0006, k0106, k0007,    k0107, k0008, k0108, \
    k0200, k0300, k0201, k0301, k0202, k0302, k0203, k0303, k0204, k0304, k0205, k0305, k0206, k0306, k0207,    k0307, k0208, k0308, \
    k0400, k0500, k0401, k0501, k0402, k0502, k0403, k0503, k0404, k0504, k0405, k0505, k0406,        k0407,    k0507, k0408, k0508, \
    k0600, k0700, k0601, k0701, k0602, k0702, k0603, k0703, k0604, k0704, k0605, k0705, k0606,                                       \
    k0800, k0900, k0801, k0901, k0802, k0902, k0803, k0903, k0804, k0904, k0805, k0905, k0806,        k0807,           k0808,        \
    k1000, k1100, k1001,                      k1003,                      k1005, k1105, k1006,        k1007,    k1107, k1008, k1108  \
) { \
    { k0000,  k0001,  k0002,  k0003,  k0004,  k0005,  k0006,  k0007,  k0008 }, \
    { k0100,  KC_NO,  k0102,  k0103,  k0104,  k0105,  k0106,  k0107,  k0108 }, \
    { k0200,  k0201,  k0202,  k0203,  k0204,  k0205,  k0206,  k0207,  k0208 }, \
    { k0300,  k0301,  k0302,  k0303,  k0304,  k0305,  k0306,  k0307,  k0308 }, \
    { k0400,  k0401,  k0402,  k0403,  k0404,  k0405,  k0406,  k0407,  k0408 }, \
    { k0500,  k0501,  k0502,  k0503,  k0504,  k0505,  KC_NO,  k0507,  k0508 }, \
    { k0600,  k0601,  k0602,  k0603,  k0604,  k0605,  k0606,  KC_NO,  KC_NO }, \
    { k0700,  k0701,  k0702,  k0703,  k0704,  k0705,  KC_NO,  KC_NO,  KC_NO }, \
    { k0800,  k0801,  k0802,  k0803,  k0804,  k0805,  k0806,  k0807,  k0808 }, \
    { k0900,  k0901,  k0902,  k0903,  k0904,  k0905,  KC_NO,  KC_NO,  KC_NO }, \
    { k1000,  k1001,  KC_NO,  k1003,  KC_NO,  k1005,  k1006,  k1007,  k1008 }, \
    { k1100,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  k1105,  KC_NO,  k1107,  k1108 } \
}
