/*
Copyright 2020 <contact@vwolf.be>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 66, 65, 64, 63,     62,     61,     60, 59,     58, 57,     56, 55,     54,     53, 52 },
        { 1,  2,  3,  4,      5,      6,      7,  8,      9,  10,     11, 12,     13,     14, 15 },
        { 0,  28, 27, 26,     25,     24,     23, 22,     21, 20,     19, 18,     NO_LED, 17, 16 },
        { 51, 29, 30, 31,     32,     33,     34, 35,     36, 37,     38, NO_LED, 39,     40, 41 },
        { 50, 49, 48, NO_LED, NO_LED, NO_LED, 47, NO_LED, 46, NO_LED, 45, NO_LED, 44,     43, 42 }
    }, {
        // LED Index to Physical Position
        {3, 32}, {8, 16}, {28, 16}, {44, 16}, {60, 16}, {76, 16}, {92, 16}, {108, 16}, {124, 16}, {140, 16}, 
        {156, 16}, {172, 16}, {188, 16}, {204, 16}, {224, 16}, {244, 16}, {244, 32}, {218, 32}, {192, 32}, {176, 32}, 
        {160, 32}, {144, 32}, {128, 32}, {112, 32}, {96, 32}, {80, 32}, {64, 32}, {48, 32}, {32, 32}, {40, 48}, 
        {56, 48}, {72, 48}, {88, 48}, {104, 48}, {120, 48}, {136, 48}, {152, 48}, {168, 48}, {184, 48}, {206, 48}, 
        {228, 48}, {244, 48}, {244, 64}, {228, 64}, {212, 64}, {186, 64}, {166, 64}, {96, 64}, {46, 64}, {22, 64}, 
        {0, 64}, {14, 48}, {244, 0}, {220, 3}, {196, 0}, {180, 0}, {164, 0}, {148, 0}, {132, 0}, {116, 0}, 
        {100, 0}, {84, 0}, {68, 0}, {52, 0}, {36, 0}, {20, 0}, {4, 0}
    }, {
        // LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 1, 1,
        1, 1, 1,          4,    1,    1,    1, 1, 1 
    }
};
#endif
