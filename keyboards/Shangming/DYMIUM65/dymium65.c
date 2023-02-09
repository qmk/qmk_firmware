 /* 
 Copyright 2020 Alec Penland
 Copyright 2020 Garret Gartner
  
 This program is free software: you can redistribute it and/or modify 
 it under the terms of the GNU General Public License as published by 
 the Free Software Foundation, either version 2 of the License, or 
 (at your option) any later version. 
  
 This program is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 GNU General Public License for more details. 
  
 You should have received a copy of the GNU General Public License 
 along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */ 

#include "dymium65.h"

/*
        k00,                                                                                             
               k11,  k12,  k13,   k14,   k15,   k16,  k17,   k18,   k19,  k1A,  k1B,  k1C,  k1D,  k1E, k1F,        
        k20,   k21,  k22,  k23,   k24,   k25,   k26,  k27,   k28,   k29,  k2A,  k2B,  k2C,  k2D,          
        k30,   k31,  k32,  k33,   k34,   k35,   k36,  k37,   k38,   k39,  k3A,  k3B,        k3D,  k3E, k3F
        k40,         k42,  k43,   k44,   k45,   k46,  k47,   k48,   k49,  k4A,  k4B,        k4D,  k4E, k4F
        k50,   k51,  k52,                       k56,                k59,  k5A,        k5C,  k5D,  k5E, k5F
*/

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {0,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, 1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     NO_LED, NO_LED},
        {28,     27,     26,     25,     24,     23,     22,     21,     20,     19,     18,     17,     16,     15,     NO_LED, NO_LED},
        {29,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     NO_LED, 41,     14,         42},
        {55,     NO_LED, 54,     53,     52,     51,     50,     49,     48,     47,     46,     45,     NO_LED, 44,     43,     NO_LED},
        {56,     57,     58,     NO_LED, NO_LED, NO_LED, 59,     NO_LED, NO_LED, 60,     61,     NO_LED, 62,     63,     64,         65}
    }, {
        {14,  0}, {28,  0}, {42,  0}, {56,  0}, {70,  0}, {84,  0}, {98,  0}, {112,  0}, {126,  0}, {140,  0}, {154,  0}, {168,  0}, {182,  0},{196,  0},
        {224, 16},{196, 16},{182, 16},{168, 16},{154, 16},{140, 16},{126, 16},{112, 16}, {98, 16},  {84, 16},  {70, 16},  {56, 16},  {42, 16} ,{28, 16},  {14, 32},
        {14, 32}, {28, 32}, {42, 32}, {56, 32}, {70, 32}, {84, 32}, {98, 32}, {112, 32}, {126, 32}, {140, 32}, {154, 32}, {168, 32},           {196, 32}, {224, 32},
        {224, 48},          {196, 48},{168, 48},{154, 48},{140, 48},{126, 48},{112, 48}, {98, 48},  {84, 48},  {70, 48},  {56, 48},            {42, 48},  {14, 48},
        {14, 64}, {28, 64}, {42, 64},                               {98, 64},                       {140, 64}, {154, 64}, {168, 64}, {182, 64},{196, 64}, {224, 64}
    }, {
        4,
                       4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4,             4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
        LED_FLAG_ALL,  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4, 
        4,                4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 
        4,             4, 4,          4,       4, 4,    4, 4, 4, 4
    }
};

#endif
