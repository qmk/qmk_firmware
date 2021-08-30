 /* 
 Copyright 2020 Garret Gartner
  
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

#define XXXX KC_NO

#define LAYOUT_staggered( \
    k001,    k002,                                                 k011, k012, k013, \
    k101,    k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, \
    k201,    k202, k203, k204, k205, k206, k207, k208, k209, k210, k211,       k213, \
    k301,    k302, k303, k304, k305, k306, k307, k308, k309, k310,       k312, k313, \
    k401,    k402, k403, k404,       k406,       k408,             k411, k412, k413 \
) \
{ \
    { k001, k002, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, k011, k012, k013 }, \
    { k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113 }, \
    { k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, XXXX, k213 }, \
    { k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, XXXX, k312, k313 }, \
    { k401, k402, k403, k404, XXXX, k406, XXXX, k408, XXXX, XXXX, k411, k412, k413 } \
}

#define LAYOUT_staggered_big_boy( \
    k001,    k002,                                                 k011, k012, k013, \
    k101,    k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, \
    k201,    k202, k203, k204, k205, k206, k207, k208, k209, k210, k211,       k213, \
    k301,    k302, k303, k304, k305, k306, k307, k308, k309, k310,       k312, k313, \
    k401,    k402, k403,                k406,                      k411, k412, k413 \
) \
{ \
    { k001, k002, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, k011, k012, k013 }, \
    { k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113 }, \
    { k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, XXXX, k213 }, \
    { k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, XXXX, k312, k313 }, \
    { k401, k402, k403, XXXX, XXXX, k406, XXXX, XXXX, XXXX, XXXX, k411, k412, k413 } \
}
