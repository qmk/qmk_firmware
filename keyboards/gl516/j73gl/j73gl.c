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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = { {
    // Key Matrix to LED Index
        { 67,66,60,59,50,49,40,39 },
        {  68,65,61,58,51,46,48,41 },
        {   69,64,62,57,52,45,47,42 },
        {     70,63,56,53,46,43,36,33 },
        {  71, 72, 55, 54, 45,44,35,34 },
        { 30,29,20,19,10, 9, 8, 0 },
        {  38,31,28,21,18,11,   1 },
        {   37,32,27,22,17,12,7,2 },
        {     26,23,16,  13,  6,3 },
        {      25, 24, 15, 14,5,4 }
    }, {
    // LED Index to Physical Position
        { 224,   0 }, { 224,  16 }, { 224,  32 }, { 224,  48 }, { 224,  64 },{ 209,  64 }, { 209,  48 }, { 206,  24 }, { 209,   0 }, { 194,   0 },
        { 179,   0 }, { 188,  16 }, { 191,  32 }, { 189,  48 }, { 194,  64 },{ 171,  64 }, { 169,  48 }, { 176,  32 }, { 173,  16 }, { 165,   0 },
        { 150,   0 }, { 156,  16 }, { 161,  32 }, { 154,  48 }, { 152,  64 },{ 135,  64 }, { 139,  48 }, { 146,  32 }, { 143,  16 }, { 135,   0 },
        { 120,   0 }, { 128,  16 }, { 131,  32 }, { 124,  48 }, { 118,  64 },{ 101,  64 }, { 109,  48 }, { 116,  32 }, { 113,  16 }, { 105,   0 },
        {  90,   0 }, {  98,  16 }, { 101,  32 }, {  94,  48 }, {  86,  64 },{  69,  64 }, {  79,  48 }, {  86,  32 }, {  83,  16 }, {  75,   0 },
        {  60,   0 }, {  68,  16 }, {  71,  32 }, {  64,  48 }, {  53,  64 },{  36,  64 }, {  49,  48 }, {  56,  32 }, {  53,  16 }, {  45,   0 },
        {  30,   0 }, {  38,  16 }, {  41,  32 }, {  34,  48 }, {  26,  32 },{  23,  16 }, {  15,   0 }, {   0,   0 }, {  11,  16 }, {  13,  32 },
        {  17,  48 }, {  2,   64 }, {  19,  64 }
    }, {
    // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4
} };
#endif

