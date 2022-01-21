/* Copyright 2021 peepeetee
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

#include "bm68hsrgb.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     14 },
    { 15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29 },
    { 30,     NO_LED, 31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43 },
    { NO_LED, 44,     45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     57 },
    { 58,     59,     60,     NO_LED, NO_LED, NO_LED, 61,     NO_LED, NO_LED, 62,     63,     64,     65,     66,     67 }
}, {
    // LED Index to Physical Position
    {  0,  0}, { 15,  0}, { 30,  0}, { 45,  0}, { 60,  0}, { 75,  0}, { 90,  0}, {105,  0}, {120,  0}, {135,  0}, {150,  0}, {165,  0}, {180,  0}, {202,  0}, {225,  0}, // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace, Delete
    {  4, 16}, { 22, 16}, { 37, 16}, { 52, 16}, { 67, 16}, { 82, 16}, { 97, 16}, {112, 16}, {127, 16}, {142, 16}, {157, 16}, {172, 16}, {187, 16}, {206, 16}, {225, 16}, // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], backslash , Home
    {  6, 32},            { 26, 32}, { 41, 32}, { 56, 32}, { 71, 32}, { 86, 32}, {101, 32}, {116, 32}, {131, 32}, {146, 32}, {161, 32}, {176, 32}, {201, 32}, {225, 32}, // Capslock, A, S, D, F, G, H, J, K, L, ;, ', Enter, Page up
               {  9, 48}, { 34, 48}, { 49, 48}, { 64, 48}, { 79, 48}, { 94, 48}, {109, 48}, {124, 48}, {139, 48}, {154, 48}, {169, 48}, {189, 48}, {208, 48}, {225, 48}, // LShift, Z, X, C, V, B, N, M, ,, ., /, Shift, Up, Page Down
    {  2, 64}, { 21, 64}, { 39, 64},                                  { 94, 64},                       {148, 64}, {163, 64}, {178, 64}, {193, 64}, {208, 64}, {225, 64}, // Ctrl, GUI, Alt, Space, RAlt, FN, Ctrl, Left, Down, Right
    {185, 45}, {160, 45}, {125, 45}, { 95, 45}, { 60, 45}, { 25, 45} // UNDERGLOW
}, {
    // LED Index to Flag
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,  // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace, Delete
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,  // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], backslash , Home
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,  // Capslock, A, S, D, F, G, H, J, K, L, ;, ', Enter, Page up
       1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,  // LShift, Z, X, C, V, B, N, M, ,, ., /, Shift, Up, Page Down
    1, 1, 1,          4,       1, 1, 1, 1, 1, 1,  // Ctrl, GUI, Alt, Space, RAlt, FN, Ctrl, Left, Down, Right
    2, 2, 2, 2, 2, 2  // UNDERGLOW
} };

//CAPS backlight
__attribute__ ((weak))
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
}
#endif
