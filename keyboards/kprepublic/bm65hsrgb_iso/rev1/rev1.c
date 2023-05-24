/* Copyright 2020 ipetepete, 2021 deadolus, 2022 p4yne
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
#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     14},
  { 15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29},
  { 30,     NO_LED, 31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43},
  { 44,     45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     57,     58},
  { 59,     60,     NO_LED, NO_LED, NO_LED, 61,     NO_LED, NO_LED, 62,     63, NO_LED,     64,     65,     66,     67}

}, {
  // LED Index to Physical Position
  // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace, Delete
  {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180,   0 }, { 202,   0 }, { 224,   0 },
  // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], Enter, Pos1
  {   7,  16 }, {  22,  16 }, {  37,  16 }, {  52,  16 }, {  67,  16 }, {  82,  16 }, {  97,  16 }, { 112,  16 }, { 127,  16 }, { 142,  16 }, { 157,  16 }, { 172,  16 }, { 187,  16 }, { 206,  16 }, { 224,  16 },
  // Capslock, A, S, D, F, G, H, J, K, L, ;, ',  , PageUp
  {  11,  32 }, {  26,  32 }, {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 }, { 198,  32 }, { 224,  32 },
  // LShift, <,  Z, X, C, V, B, N, M, ,, ., /, Shift, Up, PageDown
  {   3,  48 }, {  18,  48 }, {  33,  48 }, {  48,  48 }, {  63,  48 }, {  78,  48 }, {  93,  48 }, { 108,  48 }, { 123,  48 }, { 138,  48 }, { 153,  48 }, { 168,  48 }, { 190,  48 }, { 209,  48 }, { 224,  48 },
  // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
  {   3,  64 }, {  22,  64 }, {  33,  64 }, { 101,  64 }, { 135,  64 }, { 153,  64 }, { 194,  64 }, { 209,  64 },{ 224,  64 },
  // UNDERGLOW
  {   216, 32 }, {  180,  32 }, {  144, 32 }, { 108,  32 }, { 72,  32 }, { 36,  32 }
}, {
  // LED Index to Flag
  // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace, Delete
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
  // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], Enter, Pos1
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
  // Capslock, A, S, D, F, G, H, J, K, L, ;, ',  , PageUp
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
  // LShift, <, Z, X, C, V, B, N, M, ,, ., /, RShift, Up, PageDown
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
  // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
  1, 1, 1, 4, 1, 1, 1, 1, 1,
  // UNDERGLOW
  2, 2, 2, 2, 2, 2
} };

__attribute__ ((weak))
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
}
#endif
