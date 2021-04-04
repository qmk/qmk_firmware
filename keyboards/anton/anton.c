/* Copyright 2021 Leonez <Leonez@nuaa.edu.cn>
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

#include "anton.h"


#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        // Key Matrix to LED index
        {  0,       1,          2,          3,      4,      5,      6,      7,          8,          9,      10,     11,     12,     13,     14,     15 },
        { 30,       29,         28,         27,     26,     25,     24,     23,         22,         21,     20,     19,     18,     NO_LED, 17,     16 },
        { 31,       NO_LED,     32,         33,     34,     35,     36,     37,         38,         39,     40,     41,     42,     43,     44,     45 },
        { 59,       NO_LED,     58,         57,     56,     55,     54,     53,         52,         51,     50,     49,     48,     47,     NO_LED, 46 },
        { 60,       NO_LED,     61,         62,     63,     64,     65,     66,         67,         68,     69,     70,     NO_LED, 71,     72,     73 },
        { 83,       82,         NO_LED,     81,     NO_LED, NO_LED, 80,     NO_LED,     NO_LED,     NO_LED, 79,     78,     77,     76,     75,     74 }
    },
    {
        // LED index to phcsical position
        { 0,   0}, { 16,  0}, { 32,  0}, { 48,  0}, { 64,  0}, { 80,  0}, { 96,  0}, {112,  0}, {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {208,  0}, {224,  0}, {240,  0},
        { 240,16}, {216, 16},            {192, 16}, {176, 16}, {160, 16}, {144, 16}, {128, 16}, {112, 16}, { 96, 16}, { 80, 16}, { 64, 16}, { 48, 16}, { 32, 16}, { 16, 16}, {  0, 16},//reverse
        {  4, 32},            { 24, 32}, { 40, 32}, { 56, 32}, { 72, 32}, { 88, 32}, {104, 32}, {120, 32}, {136, 32}, {152, 32}, {168, 32}, {184, 32}, {200, 32}, {220, 32}, {240, 32},
        {240, 48},            {214, 48}, {188, 48}, {172, 48}, {156, 48}, {140, 48}, {124, 48}, {108, 48}, { 92, 48}, { 76, 48}, { 60, 48}, { 44, 48}, { 28, 48},            {  6, 48},//reverse
        { 10, 64},            { 36, 64}, { 52, 64}, { 68, 64}, { 84, 64}, {100, 64}, {116, 64}, {132, 64}, {148, 64}, {164, 64}, {180, 64},            {202, 64}, {224, 64}, {240, 64},
        {240, 80}, {224, 80}, {208, 80}, {192, 80}, {176, 80}, {160, 80},                       {102, 80},                                             { 42, 80}, { 22, 80}, {  2, 80} //reverse
    },
    {
        // LED index to flag
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,       0x04, 0x04,
        0x04,       0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
        0x08,       0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,       0x04,
        0x04,       0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,       0x04, 0x04, 0x04, 0x04,
        0x04, 0x04,       0x04,             0x04,                   0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    }
};

#endif

