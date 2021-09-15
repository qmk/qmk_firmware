/* Copyright 2020 Boardsource
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

#include "technik_s.h"
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
    {22, NO_LED, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
    {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44},
    {45, 46, 47, 48, NO_LED, 49, 50, NO_LED, 51, 52, 53, 54}
}, {
    {220, 17}, {172, 17}, {112, 17}, { 50, 17}, {  4, 17}, {  4, 56}, { 50, 56}, {112, 56}, {172, 56}, {220, 56},
    {  0,  0}, { 20,  0}, { 40,  0}, { 61,  0}, { 81,  0}, {101,  0}, {122,  0}, {142,  0}, {162,  0}, {183,  0}, {203,  0}, {224,  0},
         { 10, 21}, { 30, 21}, { 51, 21}, { 71, 21}, { 91, 21}, {112, 21}, {132, 21}, {152, 21}, {173, 21}, {193, 21}, {214, 21},
    {  0, 42}, { 20, 42}, { 40, 42}, { 61, 42}, { 81, 42}, {101, 42}, {122, 42}, {142, 42}, {162, 42}, {183, 42}, {203, 42}, {224, 42},
    {  0, 64}, { 20, 64}, { 40, 64},      { 68, 64}, { 97, 64},            {126, 64}, {154, 64},       {183, 64}, {203, 64}, {224, 64}
}, {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 4, 4, 1, 1, 1, 1
} };
#endif

