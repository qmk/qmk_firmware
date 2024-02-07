/*
Copyright 2024 PyuPyu

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
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
            { 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16 },
            { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43 },
            { 56, 55, 54, 53, 52, 51, 50, 49, 47, 46, 45, 44 },
            { 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67 }
        },{
            //LED Index to Physical Position
                {   0,   0 }, {  16,   0 }, {  32,   0 }, {  48,   0 }, {  64,   0 },{  80,   0 }, {  96,   0 }, { 112,   0 }, { 128,   0 }, { 144,   0 },
                { 160,   0 }, { 176,   0 }, { 192,   0 }, { 208,   0 }, { 224,   0 },{ 224,  16 }, { 210,  16 }, { 197,  16 }, { 181,  16 }, { 165,  16 },
                { 149,  16 }, { 133,  16 }, { 117,  16 }, { 101,  16 }, {  85,  16 },{  69,  16 }, {  53,  16 }, {  37,  16 }, {  21,  16 }, {   4,  16 },
                {   0,  32 }, {  30,  32 }, {  46,  32 }, {  62,  32 }, {  78,  32 },{  94,  32 }, { 110,  32 }, { 126,  32 }, { 142,  32 }, { 158,  32 },
                { 174,  32 }, { 190,  32 }, { 206,  32 }, { 208,  48 }, { 197,  48 },{ 176,  48 }, { 160,  48 }, { 144,  48 }, { 128,  48 }, { 112,  48 },
                {  96,  48 }, {  80,  48 }, {  64,  48 }, {  48,  48 }, {  32,  48 },{   8,  48 }, {   0,  64 }, {  19,  64 }, {  38,  64 }, {  78,  64 },
                { 104,  64 }, { 136,  64 }, { 160,  64 }, { 176,  48 }, { 192,  64 },{ 208,  64 }, { 224,  64 }
        },{
            // LED Index to Flag
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4
        } };
#endif
