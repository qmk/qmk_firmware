/* Copyright 2021 Dztech
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
#include "rgb.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
{
    { 0,  NO_LED, 1,   2,      3,      4,      NO_LED,  5,      6,      7,      8,  9,  10,     11, 12,     13,     14, 15, 16, 17 },
    { 36, 35,     34,  33,     32,     31,     30,      29,     28,     27,     26, 25, 24,     23, NO_LED, 22,     21, 20, 19, 18 },
    { 37, 38,     39,  40,     41,     42,     43,      44,     45,     46,     47, 48, 49,     50, NO_LED, 51,     52, 53, 54, 55 },
    { 75, 74,     73,  72,     71,     70,     69,      68,     67,     66,     65,  64, NO_LED, 63, NO_LED, NO_LED, 58, 57, 56, NO_LED },
    { 76, NO_LED, 77,  78,     79,     80,     81,      82,     83,     84,     85,  86, NO_LED, 87, NO_LED, 88,     89, 90, 91, 92 },
    { 105,104,    103, NO_LED, NO_LED, NO_LED, 102,     NO_LED, NO_LED, NO_LED, NO_LED, 100, NO_LED,     98, 97,     96,     95, 94, 93, NO_LED }
}, 
{
    {   12*0,  0 }, {  12*2,  0 }, {  12*3,  0 }, {  12*4,  0 }, {  12*5,  0 }, { 12*7,  0 }, { 12*8,  0 }, { 12*9,  0 }, { 12*10,  0 }, { 12*11,  0 },    { 12*12,  0 }, { 12*13,  0 }, { 12*14,  0 }, { 12*15,  0 }, { 12*16,  0 }, { 12*17,  0 }, { 12*18,  0 }, { 224,  0 },
    
    { 224,  14 }, { 12*18,  14 },  { 12*17,  14 }, { 12*16,  14 },{ 12*15,  14 },{ 12*13,  14 },  { 12*12,  14 },  { 12*11,  14 },  { 12*10,  14 }, { 12*9,  14 },{ 12*8, 14},{ 12*7,  14},  {  12*6, 14 },  {  12*5,  14 }, {  12*4,  14 },{  12*3,  14 },{  12*2,  14 }, {12,  14},  {   12*0,  14 }, 
      
    {   12*0,  26.8 }, {12,  26.8}, {  12*2,  26.8 }, {  12*3,  26.8 }, {  12*4,  26.8 }, {  12*5,  26.8 }, {  12*6, 26.8 }, { 12*7,  26.8}, { 12*8, 26.8}, { 12*9,  26.8 }, { 12*10,  26.8 }, { 12*11,  26.8 },    { 12*12,  26.8 }, { 12*13,  26.8 },  { 12*15,  26.8 }, { 12*16,  26.8 }, { 12*17,  26.8 }, { 12*18,  26.8 }, { 224,  33.2 },

 { 12*18,  39.6 }, { 12*17,  39.6 },{ 12*16,  39.6 }, {224,0},{0,0},{0,64},{224,64 },   { 12*13,  39.6 }, { 12*11,  39.6 }, { 12*10,  39.6 }, { 12*9,  39.6 },{ 12*8, 39.6},  { 12*7,  39.6},  {  12*6, 39.6 },  {  12*5,  39.6 },{  12*4,  39.6 },{  12*3,  39.6 },  {  12*2,  39.6 }, {12,  39.6},  {   12*0,  39.6 }, 
    
    {   12*0,  52 },{  12*2,  52 }, {  12*3,  52 }, {  12*4,  52 }, {  12*5,  52 }, {  12*6, 52 }, { 12*7,  52}, { 12*8, 52}, { 12*9,  52 }, { 12*10,  52 }, { 12*11,  52 },   { 12*13,  52 },  { 12*15,  52 }, { 12*16,  52 }, { 12*17,  52 }, { 12*18,  52 }, { 224,  58 },
    
 { 12*18,  64 },  { 12*17,  64 },  { 12*16,  64 },  { 12*15,  64 },{ 12*14,  64 }, { 12*13,  64 },  { 12*11,  64 },   {  12*6, 64 }, {  12*2,  64 }, {12,  64},    {   12*0,  64 }
},
{           
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4
}};

__attribute__ ((weak))
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(75, 0xFF, 0xFF, 0xFF);
    }
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(21, 0xFF, 0xFF, 0xFF);
    }    
}
#endif
