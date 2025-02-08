/*
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

//x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
//y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
  { 0,       1,      2,      3,      4,      5,      6,      7,      8,      9 },
  { 10,     11,     12,     13,     14,     15,     16,     17,     18,     19 },
  { 20,     21,     22,     23,     24,     25,     26,     27,     28,     29 },
  { 30,     31,     32,     33,     34,     35,     36,     37,     38,     39 },
  { 40,     41,     42,     43,     44,     45,     46,     47,     48,     49 },
  { 50,     51,     52,     53,     54,     55,     56,     57,     58,     59 },
  { 60,     61,     62,     63,     64,     65,     66,     67,     68,     69 },
  { 70,     71,     72,     73,     74,     75,     76,     77,     78,     79 },
  { 80,     81,     82,     83,     84,     85,     86,     87,     88,     89 },
  { 90,     91, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
    // LED Index to Physical Position
    {   0,   0 }, { 13,   0 }, { 26,   0 }, { 39,   0 }, { 52,   0 }, { 65,   0 }, { 78,   0 }, { 91,   0 }, { 104,   0 }, { 117,   0 }, { 130,   0 }, { 143,   0 }, { 156,   0 },                                 {   195,   0 }, {   208,   0 }, {   224,   0 },
    {   0,  12 }, { 13,  12 }, { 26,  12 }, { 39,  12 }, { 52,  12 }, { 65,  12 }, { 78,  12 }, { 91,  12 }, { 104,  12 }, { 117,  12 }, { 130,  12 }, { 143,  12 }, { 156,  12 }, {   169,  12 }, {   182,  24 }, {   195,  12 }, {   208,  12 }, {   224,  12 },
    {   0,  24 }, { 13,  24 }, { 26,  24 }, { 39,  24 }, { 52,  24 }, { 65,  24 }, { 78,  24 }, { 91,  24 }, { 104,  24 }, { 117,  24 }, { 130,  24 }, { 143,  24 }, { 156,  24 }, {   169,  24 },                 {   195,  24 }, {   208,  24 }, {   224,  24 },
    {   0,  36 }, { 13,  36 }, { 26,  36 }, { 39,  36 }, { 52,  36 }, { 65,  36 }, { 78,  36 }, { 91,  36 }, { 104,  36 }, { 117,  36 }, { 130,  36 }, { 143,  36 }, { 156,  36 }, {   169,  36 },
    {   0,  48 }, { 13,  48 }, { 26,  48 }, { 39,  48 }, { 52,  48 }, { 65,  48 }, { 78,  48 }, { 91,  48 }, { 104,  48 }, { 117,  48 }, { 130,  48 }, { 143,  48 }, { 156,  48 }, {   169,  48 },                                 {   208,  48 },
    {   0,  64 }, { 13,  64 }, { 26,  64 },                                        { 78,  64 },                                          { 130,  64 }, { 143,  64 }, { 156,  64 }, {   169,  64 },                 {   195,  64 }, {   208,  64 }, {   224,  64 }, {   182,  0 }
}, {
    // LED Index to Flag
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,       1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,       1,
    1, 1, 1,          1,          1, 1, 1, 1, 1, 1, 1, 1

} };

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(51, 255, 255, 255);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(14, 255, 255, 255);
    }
    return true;
}
#endif
