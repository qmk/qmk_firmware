/* Copyright 2021 minibois
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

// readability
#define ___ KC_NO

/* Default
 * ,-------------------.
 * |00 |01 |02 |03 |04 |
 * |-------------------|
 * |10 |11 |12 |13 |14 |
 * |-------------------|
 * |20 |21 |22 |23 |24 |
 * |-------------------|
 * |30 |31 |32 |33 |34 |
 * |-------------------|
 * |40 |41 |42 |43 |44 |
 * `-------------------'
*/
#define LAYOUT_all( \
        k00, k01, k02, k03, k04 , \
        k10, k11, k12, k13, k14 , \
        k20, k21, k22, k23, k24 , \
        k30, k31, k32, k33, k34 , \
        k40, k41, k42, k43, k44   \
) \
{ \
    {   k00, k01, k02, k03, k04,   },  \
    {   k10, k11, k12, k13, k14,   },  \
    {   k20, k21, k22, k23, k24,   },  \
    {   k30, k31, k32, k33, k34,   },  \
    {   k40, k41, k42, k43, k44,   }   \
}

/* Standard Numpad
 * ,-------------------.
 * |00 |01 |02 |03 |04 |
 * |-------------------|
 * |10 |11 |12 |13 |   |
 * |---------------|14 |
 * |20 |21 |22 |23 |   |
 * |-------------------|
 * |30 |31 |32 |33 |   |
 * |---------------|34 |
 * |40 |  41   |43 |   |
 * `-------------------'
*/
#define LAYOUT_standard_numpad( \
        k00, k01, k02, k03, k04 , \
        k10, k11, k12, k13,       \
        k20, k21, k22, k23, k24 , \
        k30, k31, k32, k33,       \
        k40,      k42, k43, k44   \
) \
{ \
    {   k00, k01, k02, k03, k04,   },  \
    {   k10, k11, k12, k13, ___,   },  \
    {   k20, k21, k22, k23, k24,   },  \
    {   k30, k31, k32, k33, ___,   },  \
    {   k40, ___, k42, k43, k44,   }   \
}
