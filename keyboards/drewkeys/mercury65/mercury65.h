/* Copyright 2023 Drewkeys
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

#define ____ KC_NO

// Corresponding changes to the layout names and/or definitions must also be made to info.json

/* Standard arrangement / LAYOUT
 * https://i.imgur.com/sBNeRr4.png
*/

/* Standard for hotswap / LAYOUT
 * https://i.imgur.com/1n0bL0d.png
 * note: hotswap is the same as soldered without ISO support
*/
#define LAYOUT_all( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, k014,             \
    k100,       k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, k114,       k116, \
    k200,       k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214,       k216, \
    k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311,       k313, k314,       k316, \
    k400, k401, k402,                   k406,                   k410, k411,       k413, k414, k415        \
) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, k014, ____, ____ }, \
    { k100, ____, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, k114, ____, k116 }, \
    { k200, ____, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214, ____, k216 }, \
    { k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, ____, k313, k314, ____, k316 }, \
    { k400, k401, k402, ____, ____, ____, k406, ____, ____, ____, k410, k411, ____, k413, k414, k415, ____ },  \
}
