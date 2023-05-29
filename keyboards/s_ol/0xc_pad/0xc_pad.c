/* Copyright 2021 s-ol
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
#include "0xc_pad.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // indices
    {     0,    6, KC_NO, KC_NO },
    {     1,    5,     7, KC_NO },
    {     2,    4,     8,    11 },
    { KC_NO,    3,     9,    10 }
}, {
    // phys position
    { 96, 110}, { 80, 83}, { 64,  55}, { 80, 28},
    { 96,  55}, {112, 83}, {128, 110}, {144, 83},
    {128,  55}, {112, 28}, {144,  28}, {160, 55}
}, {
    // flags
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
