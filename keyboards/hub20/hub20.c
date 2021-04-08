/* Copyright 2020 joshajohnson
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

#include "hub20.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {NO_LED,NO_LED,NO_LED,NO_LED},
    { 7,      8,      9,      10},
    { 11,     12,     13,    14},
    {15,     16,     17,     18},
    { 19,    20,     21,     22},
    { 23,    24,     25,     26}
    //todo: assign leds to keys differently for the different layouts
}, {
    // LED Index to Physical Position
    { 190, 50}, { 111, 50}, { 35, 50}, {38, 0}, {38, 35}, {186, 35}, {186, 0}, // UNDERGLOW
    //todo: underglow location needs to be recalculated. The top row is above row 4, and for now they have the same y value 0
    {  0,  0}, {75,  0}, {150,  0}, {225,  0}, // row 4
    {  0, 16}, {75, 16}, {150, 16}, {225, 16}, // row 3
    {  0, 32}, {75, 32}, {150, 32}, {225, 32}, // row 2
    {  0, 48}, {75, 48}, {150, 48}, {225, 48}, // row 1
    {  0, 64}, {75, 64}, {150, 64}, {225, 64}  // row 0

}, {
    // LED Index to Flag
    2, 2, 2, 2, 2, 2, 2,  // UNDERGLOW
    4, 4, 4, 4,           // row 4
    4, 4, 4, 4,           // row 3
    4, 4, 4, 4,           // row 2
    4, 4, 4, 4,           // row 1
    4, 4, 4, 4            // row 0

} };
#endif
