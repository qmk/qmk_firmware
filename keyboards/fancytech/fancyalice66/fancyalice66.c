/* Copyright 2022 chent7 <https://github.com/chent7>
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

#include "fancyalice66.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13, NO_LED,     14},
    { 15,     16,     17,     18,     19,     20, NO_LED,     21,     22,     23,     24,     25,     26,     27,     28,     29},
    { 30,     31,     32,     33,     34,     35, NO_LED,     36,     37,     38,     39,     40,     41,     42, NO_LED,     43},
    { 44,     45,     46,     47,     48,     49, NO_LED,     50,     51,     52,     53,     54,     55, NO_LED,     56, NO_LED},
    { 57, NO_LED,     58,     59, NO_LED, NO_LED,     60,     61, NO_LED, NO_LED,     62, NO_LED, NO_LED,     63,     64,     65}
}, {
    //Underglow (0 -> 15)
    {207, 41},{207, 28},{207, 14},{175, 11},{140, 4},{105, 9},{72, 4},{42, 6},{3, 7},{3, 33},{3, 44},{38, 50},{78, 52},{105, 57},{136, 56},{177, 50},

    //Key matrix (16 -> 83)
    {195,  10}, {185,  10}, {171,   9}, {161,  12}, {149,  14}, {138,  16}, {126,  18}, {108,  18}, { 97,  16}, { 86,  14}, { 73,  12}, { 63,   9}, { 51,  10}, { 32,  10},             { 12,   7},
    {195,  20}, {180,  20}, {169,  20}, {157,  22}, {146,  26}, {134,  28},             {112,  30}, {100,  28}, { 90,  26}, { 77,  22}, { 66,  20}, { 54,  20}, { 42,  20}, { 28,  20}, {  8,  18},
    {197,  31}, {180,  31}, {168,  32}, {157,  34}, {146,  36}, {135,  37},             {106,  38}, { 95,  37}, { 84,  35}, { 72,  32}, { 58,  30}, { 45,  30}, { 28,  30},             {  6,  28},
    {197,  41}, {177,  41}, {163,  43}, {154,  45}, {143,  47}, {130,  49},             {101,  49}, { 90,  46}, { 78,  44}, { 67,  42}, { 52,  41}, { 36,  41},             { 17,  44},
    {201,  50},             {168,  52}, {146,  56},                         {128,  60}, { 91,  57},                         { 67,  52},                         { 29,  54}, { 17,  54}, {  6,  54}
}, {
    //Underglow (0 -> 15)
    0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,

    //Key matrix (16 -> 82)
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,
	0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,      0xFF,      0xFF,      0xFF,      0xFF,      0xFF,                 0xFF,
	0xFF,                 0xFF,      0xFF,                            0xFF,      0xFF,                            0xFF,                            0xFF,      0xFF,      0xFF
}};
#endif
