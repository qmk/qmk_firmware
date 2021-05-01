/* Copyright 2018 Elliot Powell
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
#ifndef EP96_H
#define EP96_H

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
    K000, K001, K002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, k014, k015, k016, k017, k018, \
    K100, K101, K102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112,       k114, k115, k116, k117, k118, \
    K200,       K202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213,       k215, k216, k217,       \
    K300,       K302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, k314, k315, k316, k317, k318, \
    K400, K401, K402, k403, k404, k405, k406, k407, k408, k409, k410, k411,       k413, k414, k415, k416, k417,       \
    K500, K501, K502,                   k506,                         k511, k512, k513, k514, k515, k516, k517, k518) \
{ \
    {K000, K001, K002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, k014, k015, k016, k017, k018}, \
    {K100, K101, K102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, xxxx, k114, k115, k116, k117, k118}, \
    {K200, xxxx, K202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, xxxx, k215, k216, k217, xxxx}, \
    {K300, xxxx, K302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, k314, k315, k316, k317, k318}, \
    {K400, K401, K402, k403, k404, k405, k406, k407, k408, k409, k410, k411, xxxx, k413, k414, k415, k416, k417, xxxx}, \
    {K500, K501, K502, xxxx, xxxx, xxxx, k506, xxxx, xxxx, xxxx, xxxx, k511, k512, k513, k514, k515, k516, k517, k518}  \
}

#endif
