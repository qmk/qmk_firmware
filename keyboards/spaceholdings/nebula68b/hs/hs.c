/* Copyright 2021 Yiancar
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {  0,      1,  2,      4,      5,      6,  7,      9,     10, 11, 13, 14, 15,     17, 18 },
    { 35,     34, 33,     32,     31,     30, 29,     28,     27, 26, 25, 24, 23, NO_LED, 21 },
    { 37,     38, 39,     40,     41,     42, 43,     44,     45, 46, 47, 48, 22,     49, 19 },
    { 63, NO_LED, 62,     61,     60,     59, 58,     57,     56, 55, 54, 53, 52,     51, 20 },
    { 64,     65, 67, NO_LED, NO_LED, NO_LED, 69, NO_LED, NO_LED, 71, 72, 73, 75,     76, 77 }
}, {
    {  6, 10}, { 19, 10}, { 32, 10}, { 39, 11}, { 45, 10}, { 58, 10}, { 71, 10}, { 84, 10}, { 90, 11}, { 97, 10}, {110, 10}, {123, 10}, {130, 11}, {136, 10}, {149, 10}, {162, 10},
    {178, 13}, {182, 10}, {205, 10}, {218, 10}, {218, 23}, {205, 23}, {185, 23}, {169, 23}, {156, 23}, {143, 23}, {130, 23}, {117, 23}, {104, 23}, { 91, 23}, { 78, 23},
    { 65, 23}, { 52, 23}, { 39, 23}, { 26, 23}, { 10, 23}, {  4, 26}, { 17, 29}, { 29, 35}, { 42, 35}, { 55, 35}, { 68, 35}, { 81, 35}, { 94, 35}, {107, 35}, {120, 35}, {133, 35},
    {146, 35}, {159, 35}, {180, 35}, {220, 32}, {205, 48}, {177, 48}, {153, 48}, {140, 48}, {127, 48}, {114, 48}, {101, 48}, { 88, 48}, { 75, 48}, { 62, 48}, { 49, 48}, { 36, 48},
    { 15, 48}, {  8, 61}, { 24, 61}, { 32, 52}, { 41, 61}, { 81, 56}, { 89, 61}, {132, 53}, {138, 61}, {154, 61}, {170, 61}, {179, 53}, {192, 61}, {205, 61}, {218, 61}
}, {
    1, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 2, 1, 1, 1,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 2, 1, 2, 4, 2, 1, 1, 1, 2, 1, 1, 1
} };
// clang-format on
#endif
