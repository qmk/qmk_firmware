/* Copyright 2021 illness072
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

#if defined(RGB_MATRIX_ENABLE)
led_config_t g_led_config = {
    { // keymap to LED number
        // left
        {    19,     18, 13, 12, 7, 6}, // R3
        {    20,     17, 14, 11, 8, 5}, // R2
        {NO_LED,     16, 15, 10, 9, 4}, // R1
        {NO_LED, NO_LED,  0,  1, 2, 3}, // R0
        // right
        {    46,     45, 40, 39, 34, 33}, // R3
        {    47,     44, 41, 38, 35, 32}, // R2
        {NO_LED,     43, 42, 37, 36, 31}, // R1
        {NO_LED, NO_LED, 27, 28, 29, 30}, // R0
    },
    {// phisical LED position, {x, y} : x = 0..224, y = 0..64
        // left-bg [LED_01-21]
        {56, 65}, {77, 68}, {95, 79}, {109, 91}, 
        {87, 46}, {87, 29}, {87, 12}, { 69, 43}, { 69, 26}, { 69,  8}, 
        {52, 35}, {52, 17}, {52,  0}, { 35,  4}, { 35, 21}, { 35, 38}, 
        {17, 54}, {17, 36}, {17, 19}, {  0, 26}, {  0, 43}, 
        // left-ug [LED_22-27]
        {25, 49}, {26, 19}, {60, 14}, {106, 33}, {107, 72}, { 70, 66}, 
        // right-bg [LED_28-48]
        {199, 65}, {179, 68}, {160, 79}, {146, 91}, 
        {168, 46}, {168, 29}, {168, 12}, {186, 43}, {186, 26}, {186,  8}, 
        {203, 35}, {203, 17}, {203,  0}, {220,  4}, {220, 21}, {220, 38}, 
        {238, 54}, {238, 36}, {238, 19}, {255, 26}, {255, 43}, 
        // right-ug [LED_49-54]
        {230, 49}, {230, 19}, {195, 14}, {149, 33}, {148, 72}, {185, 66}, 
    },
    {// LED Index to Flag
        // Left-bg [LED_01-21]
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        // left-ug [LED_22-27]
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        // right-bg [LED_28-48]
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        // right-ug [LED_49-54]
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW
    }
};
#endif
