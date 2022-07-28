/* Copyright 2022 Studio Kestra
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
    k000, k100, k001, k101, k002, k102, k003, k103, k004, k104, k005, k105, k006, k106, k007, k107, \
    k200, k300, k201, k301, k202, k302, k203, k303, k204, k304, k205, k305, k206,       k207, k307, \
    k400, k500, k401, k501, k402, k502, k403, k503, k404, k504, k405, k505,             k407, k507, \
    k600,       k601, k701, k602, k702, k603, k703, k604, k704, k605, k705, k606,       k607, k707,  \
    k800, k900, k801,       k802,       k803,       k804,       k805,       k806,       k807, k907  \
) { \
    { k000,  k001,  k002,  k003,  k004,  k005,  k006,  k007 }, \
    { k100,  k101,  k102,  k103,  k104,  k105,  k106,  k107 }, \
    { k200,  k201,  k202,  k203,  k204,  k205,  k206,  k207 }, \
    { k300,  k301,  k302,  k303,  k304,  k305,  KC_NO, k307 }, \
    { k400,  k401,  k402,  k403,  k404,  k405,  KC_NO, k407 }, \
    { k500,  k501,  k502,  k503,  k504,  k505,  KC_NO, k507 }, \
    { k600,  k601,  k602,  k603,  k604,  k605,  k606,  k607 }, \
    { KC_NO, k701,  k702,  k703,  k704,  k705,  KC_NO, k707 }, \
    { k800,  k801,  k802,  k803,  k804,  k805,  k806,  k807 }, \
    { k900,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k907 } \
}
