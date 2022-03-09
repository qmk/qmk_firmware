/* Copyright 2021 DZTECH <moyi4681@Live.cn>
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

#include "kbd75rgb.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3,      4,      5,  6,      7,       8, 9,  10, 11, 12, 13,    15},
    {  30, 29, 28, 27,     26,     25, 24,     23,     22, 21, 20, 19, 18, 17,    16},
    {  31, 32, 33, 34,     35,     36, 37,     38,     39, 40, 41, 42, 43, 44,    45},
    {  59, 58, 57, 56,     55,     54, 53,     52,     51, 50, 49, 48, 14, 47,    46},
    {  60, 61, 62, 63,     64,     65, 66,     67,     68, 69, 70, 71, NO_LED,72, 73},
    {  83, 82, 81, NO_LED, NO_LED, 80, NO_LED, NO_LED, 79, 78, 77, 76, NO_LED,75 ,74}
}, {
    {0, 0},   {14.9, 0},  {14.9*2, 0},{14.9*3, 0}, {14.9*4, 0}, {14.9*5, 0}, {14.9*6, 0}, {14.9*7, 0}, {14.9*8, 0}, {14.9*9, 0}, {14.9*10, 0}, {14.9*11, 0}, {14.9*12, 0},  {14.9*13, 0}, {14.9*14, 0}, {224, 0},
    {224, 12.8}, {218, 12.8},{192, 12.8},{176, 12.8},{160, 12.8},{144, 12.8},{128, 12.8},{112, 12.8},{96, 12.8},{80, 12.8},{64, 12.8},{48, 12.8},{32, 12.8},{16, 12.8},{0, 12.8},         
    {0, 25.6},{16, 25.6}, {32, 25.6}, {48, 25.6},  {64, 25.6},  {80, 25.6},  {96, 25.6},  {112, 25.6}, {128, 25.6}, {144, 25.6}, {160, 25.6},{176, 25.6}, {192, 25.6},   {218, 25.6}, {224, 25.6},
{224, 38.4},{200, 38.4},{176, 38.4},{160, 38.4},{144, 38.4},{128, 38.4},{112, 38.4},{96, 38.4},{80, 38.4},{64, 38.4},{48, 38.4},{32, 38.4},{16, 38.4},{0, 38.4},                       
    {0, 51.2},{16, 51.2}, {32, 51.2}, {48, 51.2},  {64, 51.2},  {80, 51.2},  {96, 51.2},  {112, 51.2}, {128, 51.2}, {144, 51.2}, {160, 51.2},   {189, 51.2}, {218, 51.2},   {224, 51.2}, 
{224, 64},{218, 64},{192, 64},{176, 64},{160, 64},{144, 64}, {80, 64}, {32, 64},{16, 64},{0, 64}                                                                              
}, {
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,1,4,1,1,1,4,4,4,
4,4,4,4
} };


__attribute__ ((weak))
void rgb_matrix_indicators_user(void)
{
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK))
    {
        rgb_matrix_set_color(59, 0xFF, 0xFF, 0xFF);
    }
}
#endif
