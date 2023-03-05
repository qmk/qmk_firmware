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
#include "keybee65.h"

led_config_t g_led_config  = {
    {
        // Key Matrix to LED Index
        {  0,      1,  2,      3,      4,      5,      6,  7,      8,      9, 10, 11, 12, NO_LED, 13, 14 },
        { 29, NO_LED, 28,     27,     26,     25,     24, 23,     22,     21, 20, 19, 18,     17, 16, 15 },
        { 30, NO_LED, 31,     32,     33,     34,     35, 36,     37,     38, 39, 40, 41, NO_LED, 42, 43 },
        { 57, NO_LED, 56,     55,     54,     53,     52, 51,     50,     49, 48, 47, 46, NO_LED, 45, 44 },
        { 58,     59, 60, NO_LED, NO_LED, NO_LED, NO_LED, 61, NO_LED, NO_LED, 62, 63, 64,     65, 66, 67 }
    }, {
        // LED Index to Physical Position
        {  6,  2 }, { 20,  2 }, { 35, 11 }, { 49, 11 }, { 64, 11 }, { 78, 11 }, {  92, 11 }, { 107, 11 }, { 120, 11 }, { 135, 11 }, { 148, 11 }, { 164, 11 }, { 177, 11 }, { 198, 11 }, { 220, 11 },
        {  9, 24 }, { 26, 24 }, { 42, 24 }, { 56, 24 }, { 70, 24 }, { 85, 24 }, { 100, 24 }, { 113, 24 }, { 128, 24 }, { 143, 24 }, { 156, 24 }, { 170, 24 }, { 184, 24 }, { 202, 24 }, { 220, 24 },
        { 11, 38 }, { 29, 38 }, { 46, 38 }, { 60, 38 }, { 74, 38 }, { 88, 38 }, { 103, 38 }, { 118, 38 }, { 132, 38 }, { 146, 38 }, { 160, 38 }, { 174, 38 },              { 198, 38 }, { 220, 38 },
        { 16, 53 },             { 37, 53 }, { 52, 53 }, { 66, 53 }, { 80, 53 }, {  96, 53 }, { 110, 53 }, { 125, 53 }, { 140, 53 }, { 153, 53 }, { 168, 53 }, { 187, 53 }, { 207, 53 }, { 220, 53 },
        {  6, 68 }, { 25, 68 }, { 44, 68 },                                     {  96, 68 },                           { 148, 68 }, { 164, 68 }, { 180, 68 }, { 192, 68 }, { 207, 68 }, { 220, 68 }
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4,
        4,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4,          4,       4, 4, 4, 4, 4, 4
    }
};
