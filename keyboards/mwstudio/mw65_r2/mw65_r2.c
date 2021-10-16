/* Copyright 2021 TW59420 <https://github.com/TW59420>
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

#include "mw65_r2.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  { 0,      1,      2,      3,      4,      5,      6,      7 },
  { 8,      9,      10,     11,     12,     13,     14,    15 }
}, {
    { 175, 45 }, { 130, 45 }, { 85, 45 }, { 50, 45 }, {  15, 45 }, { 15, 35 }, { 15, 25 }, { 15, 10 }, { 50, 10 }, { 85, 10 }, { 130, 10 }, { 175, 10 }, { 210, 10 }, { 210, 25 }, { 210, 35 }, { 210, 45 },
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
#endif
