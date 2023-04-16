/* Copyright 2021 Moritz Plattner
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

#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index, LED 61 omitted on ANSI
    { 0,      2,      4,      6,      8,      10,     12,     14     }, \
    { 1,      3,      5,      7,      9,      11,     13,     15     }, \
    { 16,     18,     20,     22,     24,     26,     28,     NO_LED }, \
    { 17,     19,     21,     23,     25,     27,     29,     30     }, \
    { 31,     32,     34,     36,     38,     40,     42,     44     }, \
    { NO_LED, 33,     35,     37,     39,     41,     43,     45     }, \
    { 46,     48,     50,     52,     54,     56,     NO_LED, 58     }, \
    { 47,     49,     51,     53,     55,     57,     NO_LED, 59     }, \
    { 60,     62,     64,     66,     68,     70,     NO_LED, 73     }, \
    { NO_LED, 63,     65,     67,     69,     71,     72,     74     }, \
    { 75,     78,     NO_LED, NO_LED, NO_LED, 79,     81,     83     }, \
    { 76,     77,     NO_LED, NO_LED, NO_LED, 80,     82,     84     }  \
}, {
    // LED Index to Physical Position, the LED at { 0,0 } in row 5 is there to catch a non-existing LED on ANSI
    {  0,0  }, { 15,0  }, { 30,0  }, { 45,0  }, { 60,0  }, { 75,0  }, { 90,0  }, {105,0  }, {119,0  }, {134,0  }, {149,0  }, {164,0  }, {179,0  }, {194,0  }, {209,0  }, {224,0  }, 
    {  0,13 }, { 15,13 }, { 30,13 }, { 45,13 }, { 60,13 }, { 75,13 }, { 90,13 }, {105,13 }, {119,13 }, {134,13 }, {149,13 }, {164,13 }, {179,13 },            {202,13 }, {224,13 }, 
    {  4,26 },            { 22,26 }, { 37,26 }, { 52,26 }, { 67,26 }, { 82,26 }, { 97,26 }, {112,26 }, {127,26 }, {142,26 }, {157,26 }, {172,26 }, {187,26 }, {205,26 }, {224,26 }, 
    {  6,38 },            { 26,38 }, { 41,38 }, { 56,38 }, { 71,38 }, { 86,38 }, {101,38 }, {116,38 }, {131,38 }, {146,38 }, {161,38 }, {175,38 }, {200,38 },            {224,38 }, 
    {  9,51 }, {  0,0  }, { 34,51 }, { 49,51 }, { 63,51 }, { 78,51 }, { 93,51 }, {108,51 }, {123,51 }, {138,51 }, {153,51 }, {168,51 },            {189,51 }, {209,51 }, {224,51 }, 
    {  2,64 }, { 21,64 }, { 39,64 },                                  { 95,64 },                                  {149,64 }, {164,64 }, {179,64 }, {194,64 }, {209,64 }, {224,64 }
}, {
    // LED Index to Flag, the 0 flag in row 5 is there to catch a non-existing LED on ANSI
    1, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
    1,    4,12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    9,   12,12,12, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
    1, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 4, 1,
    1, 9, 1,          4,          1, 1, 1, 4, 4, 4,
} };
#endif
