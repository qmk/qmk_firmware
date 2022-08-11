/* Copyright 2021 drhigsby
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

#define LAYOUT_3uc( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110,  \
    k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210,   \
          k301, k302, k303,       k305,       k307, k308, k309           \
) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010 }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110 },  \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210 },   \
    { KC_NO, k301, k302, k303, KC_NO, k305, KC_NO, k307, k308, k309 }        \
}

#define LAYOUT_2x2uc( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110,  \
    k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210,   \
          k301, k302, k303,       k305,       k307, k308, k309           \
) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010 }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110 },  \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210 },   \
    { KC_NO, k301, k302, k303, KC_NO, k305, KC_NO, k307, k308, k309 }        \
}

#define LAYOUT_7uc( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110,  \
    k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210,   \
          k301,                   k305,                   k309           \
) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010 }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110 },  \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210 },   \
    { KC_NO, k301, KC_NO, KC_NO, KC_NO, k305, KC_NO, KC_NO, KC_NO, k309 }    \
}

#define LAYOUT_2x3uc( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110,  \
    k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210,   \
          k301, k302, k303,                   k307, k308, k309           \
) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010 }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110 },  \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210 },   \
    { KC_NO, k301, k302, k303, KC_NO, KC_NO, KC_NO, k307, k308, k309 }        \
}

#define LAYOUT_6uc( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110,  \
    k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210,   \
          k301, k302,             k305,             k308, k309           \
) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010 }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110 },  \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210 },   \
    { KC_NO, k301, k302, KC_NO, KC_NO, k305, KC_NO, KC_NO, k308, k309 }        \
}
