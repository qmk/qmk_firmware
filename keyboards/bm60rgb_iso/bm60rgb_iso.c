/* Copyright 2020 markva
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
#include "bm60rgb_iso.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    led_set_user(usb_led);
}

led_config_t g_led_config = { {
  {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13 },
  {  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27 },
  {  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  40,  41,  42 },
  {  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56 },
  {  57,  58,  59,  NO_LED, NO_LED, NO_LED,  60, NO_LED,  NO_LED,  61, 62,  63,  64,  65}
}, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
    {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180,   0 }, { 202,   0 },
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ],  ,
    {   7,  16 }, {  22,  16 }, {  37,  16 }, {  52,  16 }, {  67,  16 }, {  82,  16 }, {  97,  16 }, { 112,  16 }, { 127,  16 }, { 142,  16 }, { 157,  16 }, { 172,  16 }, { 187,  16 }, { 206,  16 }, 
    // Capslock, A, S, D, F, G, H, J, K, L, ;, ', Enter
    {  11,  32 }, {  26,  32 }, {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 }, { 198,  32 }, 
    // LShift, <, Z, X, C, V, B, N, M, ,, ., /, Shift, Up,
    {   3,  48 }, {  22,  48 }, {  33,  48 }, {  48,  48 }, {  63,  48 }, {  78,  48 }, {  93,  48 }, { 108,  48 }, { 123,  48 }, { 138,  48 }, { 153,  48 }, { 168,  48 }, { 194,  48 }, { 213,  48 }, 
    // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
    {   3,  64 }, {  22,  64 }, {  33,  64 }, { 101,  64 }, { 135,  64 }, { 153,  64 }, { 195,  64 }, { 210,  64 }, { 225,  64 }
}, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ],  , 
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 
    // Capslock, A, S, D, F, G, H, J, K, L, ;, ', Enter
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 
    // LShift,<, Z, X, C, V, B, N, M, ,, ., /, Shift, Up, 
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 
    // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
    1, 1, 1, 4, 1, 1, 1, 1, 1
} };
