/**
 * cain_re.h
 *
    Copyright 2020 astro <yuleiz@gmail.com>

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
    k000,       k001, k002, k003, k004,   k005, k006, k007, k008,     k009, k010, k011, k012,                             k013, k014, k015, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112,       k113,   k114, k115, k116, k117,   k118, k119, k120, \
    k200,    k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212,    k213,   k214, k215, k216, k217,   k218, k219, k220, \
    k300,       k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311,       k312,   k313, k314, k315, k316, \
    k400,         k401, k402, k403, k404, k405, k406, k407, k408, k409, k410,           k411,   k412, k413, k414, k415,         k416, \
    k500,     k501,   k502,                   k503,                   k504,   k505,     k506,   k507, k508, k509, k510,   k511, k512, k513 \
) { \
  { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011}, \
  { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111}, \
  { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211}, \
  { k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311}, \
  { k400, k401, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411}, \
  { k012, k113, k112, k212, k213, k312, k412, k413, k414, k415, k316, k315}, \
  { k114, k115, k116, k117, k217, k216, k215, k214, k313, k314, k416, KC_NO}, \
  { k013, k014, k015, k120, k119, k118, k218, k219, k220, k511, k512, k513}, \
  { k500, k501, k502, k503, k504, k505, k506, k507, k508, k509, k510, KC_NO} \
}
