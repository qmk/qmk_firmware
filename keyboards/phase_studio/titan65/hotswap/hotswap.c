/* Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "hotswap.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {     52,     53, 54,     55,     56,     57, 58,     59,     60,     61, 62, 63,     64,    NO_LED,      65, 66 },
        {     51, NO_LED, 50,     49,     48,     47, 46,     45,     44,     43, 42, 41,     40,         39,    .38, 37 },
        {     23, NO_LED, 24,     25,     26,     27, 28,     29,     30,     31, 32, 33,     34,         35, NO_LED, 36 },
        { NO_LED,     22, 21,     20,     19,     18, 17,     16,     15,     14, 13, 12, NO_LED,         11,     10,  9 },
        {      0,      1, NO_LED, 2, NO_LED, NO_LED,  3, NO_LED, NO_LED, NO_LED,  4,  5, NO_LED,          6,      7,  8 }
    }, {
        {   2,  64 }, {  21,  64 }, {  39,  64 },                                           {  96,  64 },                             { 150,  64 }, { 165,  64 },               { 195,  64 }, { 210,  64 }, { 224,  64 },
        { 224,  48 }, { 210,  48 },  { 189,  48 },  { 154,  48 },   { 139,  48 },  { 124,  48 },  { 109,  48 },   {  94,  48 },  {  79,  48 },  {  64,  48 },   {  49,  48 }, {  34,  48 }, {   22,  48 }, { 5, 48 },
        {   6,  32 },               {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 }, { 181, 32 },     { 201,  32 },          { 224,  32 },
        { 224,  16 }, { 206,  16 },{ 188,  16 },  { 173,  16 }, { 158,  16 },  { 143,  16 },  { 128,  16 },   { 113,  16 }, {  98,  16 },  {  83,  16 }, {  68,  16 }, {  53,  16 },   {  38,  16 }, { 22, 16 },   {   4,  16 },
        {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180, 0 },                { 203,   0 }, { 224,   0 }
    }, {
        1, 1, 1,          4,       1, 1,    1, 1, 1,
        1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4,   4,  1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 1,   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   1, 1
    }
};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
