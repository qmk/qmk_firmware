/* Copyright 2021 takashicompany
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
#define LAYOUT( \
    l001, l002, l003, l004, l005, l006, l007, l008, r001, r002, r003, r004, r005, r006, r007, r008, \
    l201, l009, l010, l011, l012, l013, l901,       r201, r009, r010, r011, r012, r013, r901,       \
    l301, l014, l015, l016, l017, l018,             r301, r014, r015, r016, r017, r018,             \
    l401, l019, l020, l021, l022, l023, l024,       r401, r019, r020, r021, r022, r023, r024,       \
    l025, l101, l102, l026, l103, l104, l027,       r025, r101, r102, r026, r103, r104, r027        \
) { \
    { l001, l002, l003, l004, l005, l006, l007 },   \
    { l201, l009, l010, l011, l012, l013, l008 },   \
    { l301, l014, l015, l016, l017, l018, l901 },   \
    { l401, l019, l020, l021, l022, l023, l024 },   \
    { l025, l101, l102, l026, l103, l104, l027 },   \
    { r001, r002, r003, r004, r005, r006, r007 },   \
    { r201, r009, r010, r011, r012, r013, r008 },   \
    { r301, r014, r015, r016, r017, r018, r901 },   \
    { r401, r019, r020, r021, r022, r023, r024 },   \
    { r025, r101, r102, r026, r103, r104, r027 }    \
}
