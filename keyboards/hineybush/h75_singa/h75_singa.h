/* Copyright 2019 hineybush
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
#define LAYOUT_all( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, k014, k015, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, k114, k115, \
    k200,       k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214, k215, \
    k300,       k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, k314, k315, \
    k400, k401, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412,       k414, k415, \
    k500, k501, k502,       k504,       k506,       k508,       k510, k511,       k513, k514, k515  \
) \
{ \
    {k000,  k001,  k002,  k003,  k004,  k005,  k006,  k007,  k008,  k009,   k010,   k011,   k012,   k013,   k014, k015}, \
    {k100,  k101,  k102,  k103,  k104,  k105,  k106,  k107,  k108,  k109,   k110,   k111,   k112,   k113,   k114, k115}, \
    {k200,  KC_NO, k202,  k203,  k204,  k205,  k206,  k207,  k208,  k209,   k210,   k211,   k212,   k213,   k214, k215}, \
    {k300,  KC_NO, k302,  k303,  k304,  k305,  k306,  k307,  k308,  k309,   k310,   k311,   k312,   k313,   k314, k315}, \
    {k400,  k401,  k402,  k403,  k404,  k405,  k406,  k407,  k408,  k409,   k410,   k411,   k412,   KC_NO,  k414, k415}, \
    {k500,  k501,  k502,  KC_NO, k504,  KC_NO, k506,  KC_NO, k508,  KC_NO,  k510,   k511,   KC_NO,  k513,   k514, k515}  \
}

#define LAYOUT_wkl_std( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, k014, k015, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112,       k114, k115, \
    k200,       k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214, k215, \
    k300,       k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312,       k314, k315, \
    k400,       k402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412,       k414, k415, \
    k500, k501,                         k506,                   k510, k511,       k513, k514, k515  \
) \
{ \
    {k000,  k001,  k002,  k003,  k004,  k005,  k006,  k007,  k008,  k009,   k010,   k011,   k012,   k013,   k014, k015}, \
    {k100,  k101,  k102,  k103,  k104,  k105,  k106,  k107,  k108,  k109,   k110,   k111,   k112,   KC_NO,  k114, k115}, \
    {k200,  KC_NO, k202,  k203,  k204,  k205,  k206,  k207,  k208,  k209,   k210,   k211,   k212,   k213,   k214, k215}, \
    {k300,  KC_NO, k302,  k303,  k304,  k305,  k306,  k307,  k308,  k309,   k310,   k311,   k312,   KC_NO,  k314, k315}, \
    {k400,  KC_NO, k402,  k403,  k404,  k405,  k406,  k407,  k408,  k409,   k410,   k411,   k412,   KC_NO,  k414, k415}, \
    {k500,  k501,  KC_NO, KC_NO, KC_NO, KC_NO, k506,  KC_NO, KC_NO, KC_NO,  k510,   k511,   KC_NO,  k513,   k514, k515}  \
}
