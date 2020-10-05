/*
Copyright 2020 Evy Dekkers

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

#include "canoe_gen2.h"

void keyboard_pre_init_kb(void) {
  setPinOutput(E6);
  writePinHigh(E6);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(E6, !led_state.caps_lock);
    }

    return true;
}

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // 15, 44, 46, 48,
    // 74, 75, 76
    {  0,  1,  2,  3,      4,      5,      6,  7,      8,      9, 10, 11, 12,     14, 16 },
    { 17, 18, 19, 20,     21,     22,     23, 24,     25,     26, 27, 28, 29,     13, 31 },
    { 32, 33, 34, 35,     36,     37,     38, 39,     40,     41, 42, 43, 30,     45, 47 },
    { 49, 50, 51, 52,     53,     54,     55, 56,     57,     58, 59, 60, 61,     62, 63 },
    { 64, 65, 66, NO_LED, NO_LED, NO_LED, 67, NO_LED, NO_LED, 69, 70, NO_LED, 71, 72, 73 }
}, {
    // LED Index to Physical Position
    { 7, 8 },    // Esc
    { 22,  8 },  // 1
    { 37,  8 },  // 2
    { 52,  8 },  // 3
    { 67,  8 },  // 4
    { 82,  8 },  // 5
    { 97,  8 },  // 6
    { 112,  8 }, // 7
    { 127,  8 }, // 8
    { 142,  8 }, // 9
    { 157,  8 }, // 0
    { 172,  8 }, // -
    { 187,  8 }, // =
    { 202,  8 }, // split bs
    { 209,  8 }, // bs
    { 217,  8 }, // split bs
    { 231,  8 }, // ins
    { 11, 24 },   // tab
    { 30,  24 },  // q
    { 45,  24 },  // w
    { 60,  24 },  // e
    { 75,  24 },  // r
    { 90,  24 },  // t
    { 104,  24 }, // y
    { 119,  24 }, // u
    { 134,  24 }, // i
    { 149,  24 }, // o
    { 164,  24 }, // p
    { 179,  24 }, // [
    { 194,  24 }, // ]
    { 212,  24 }, // backslash
    { 231,  24 }, // del
    { 11, 40 },   // caps
    { 34,  40 },  // a
    { 49,  40 },  // s
    { 64,  40 },  // d
    { 79,  40 },  // f
    { 94,  40 },  // g
    { 108,  40 }, // h
    { 123,  40 }, // j
    { 138,  40 }, // k
    { 153,  40 }, // l
    { 168,  40 }, // ;
    { 183,  40 }, // '
    { 198,  40 }, // iso hash
    { 200,  40 }, // ansi enter
    { 215,  32 }, // iso enter
    { 231,  40 }, // pgup
    { 9, 56 },    // iso shift
    { 17,  56 },  // ansi shift
    { 26,  56 },  // iso nubs
    { 41,  56 },  // z
    { 56,  56 },  // x
    { 71,  56 },  // c
    { 86,  56 },  // v
    { 101,  56 }, // b
    { 116,  56 }, // n
    { 131,  56 }, // m
    { 146,  56 }, // ,
    { 161,  56 }, // .
    { 175,  56 }, // ?
    { 196,  56 }, // shift
    { 217,  56 }, // up
    { 231,  56 }, // pgdn
    { 10, 72 },   // ctrl
    { 29,  72 },  // win
    { 48,  72 },  // alt
    { 103,  72 }, // space
    { 112,  72 }, // space
    { 161,  72 }, // alt
    { 176,  72 }, // fn
    { 202,  72 }, // left
    { 217,  72 }, // down
    { 231,  72 }, // right
    { 7,  40 },   // top 1
    { 119,  40 }, // top 2
    { 231,  40 }  // top 3
}, {
    // LED Index to Flag
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 1, 1, 4, 4, 1, 1, 1, 1, 1,
    2, 2, 2
} };
#endif
