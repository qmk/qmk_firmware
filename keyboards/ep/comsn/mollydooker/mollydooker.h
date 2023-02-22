/* Copyright 2019 Elliot Powell
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
#define xxxx KC_NO

#define LAYOUT( \
    K100, K101, K102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, k114, k115, k116, k117, k118, \
    K200, k201, K202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214, k215, k216, k217, k218, \
    K300, k301, K302,       k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, k314, k315,       k317, k318, \
    K400, K401, K402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412, k413, k414,       k416, k417, k418, \
    K500,       K502,       k504, k505, k506,             k509,                   k513, k514,       k516, k517, k518) \
{ \
    {K100, K101, K102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, k114, k115, k116, k117, k118}, \
    {K200, k201, K202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214, k215, k216, k217, k218}, \
    {K300, k301, K302, xxxx, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, k314, k315, xxxx, k317, k318}, \
    {K400, K401, K402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412, k413, k414, xxxx, k416, k417, k418}, \
    {K500, xxxx, K502, xxxx, k504, k505, k506, xxxx, xxxx, k509, xxxx, xxxx, xxxx, k513, k514, xxxx, k516, k517, k518}  \
}
