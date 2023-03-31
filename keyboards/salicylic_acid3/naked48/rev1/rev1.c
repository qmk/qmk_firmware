/*
Copyright 2021 Salicylic_Acid

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

#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = { {
    // Key Matrix to LED Index
        { 0,47,42,41,36,35,30,29,24,23,18,17 },
        { 1,46,43,40,37,34,31,28,25,22,19,16 },
        { 2,45,44,39,38,33,32,27,26,21,20,15 },
        { 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14 }
    }, {
    // LED Index to Physical Position
        {   0,   0 }, {   0,  21 }, {   0,  43 }, {  17,  64 }, {  34,  64 },{  52,  64 }, {  69,  64 }, {  86,  64 }, { 103,  64 }, { 121,  64 },
        { 138,  64 }, { 155,  64 }, { 172,  64 }, { 190,  64 }, { 207,  64 },{ 224,  43 }, { 224,  21 }, { 224,   0 }, { 207,   0 }, { 207,  21 },
        { 207,  43 }, { 190,  43 }, { 190,  21 }, { 190,   0 }, { 172,   0 },{ 172,  21 }, { 172,  43 }, { 155,  43 }, { 155,  21 }, { 155,   0 },
        { 138,   0 }, { 138,  21 }, { 138,  43 }, {  86,  43 }, {  86,  21 },{  86,   0 }, {  69,   0 }, {  69,  21 }, {  69,  43 }, {  52,  43 },
        {  52,  21 }, {  52,   0 }, {  34,   0 }, {  34,  21 }, {  34,  43 },{  17,  43 }, {  17,  21 }, {  17,   0 }
    }, {
    // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
