/* Copyright 2020-2022 Lorenzo Leonini
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

led_config_t g_led_config = {
    {
        {12, 11, 8, 7, 4, 3, 36, 37, 38, 39, 40, 41},
        {13, 10, 9, 6, 5, 2, 35, 34, 33, 32, 31, 30},
        {14, 15, 16, 17, 18, 1, 24, 25, 26, 27, 28, 29},
        {NO_LED, NO_LED, NO_LED, 19, 20, 21, 0, 22, 23, NO_LED, NO_LED, NO_LED}
    }, {
        {112, 32}, {92,  36}, {94,  25}, {97,  14}, {80,  13}, {77,  24},
        {62,  18}, {64,  8},  {49,  6},  {46,  17}, {28,  23}, {30,  13},
        {14,  11}, {11,  22}, {8,   32}, {26,  34}, {43,  28}, {61,  29},
        {76,  34}, {78,  46}, {97,  49}, {112, 56}, {127, 49}, {146, 46},
        {132, 36}, {148, 34}, {164, 29}, {180, 28}, {198, 34}, {215, 32},
        {212, 22}, {196, 23}, {178, 17}, {161, 18}, {146, 24}, {130, 25},
        {126, 14}, {143, 13}, {159, 8},  {175, 6},  {194, 13}, {210, 11}
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4
    }
};
