/* Copyright 2022 Yiancar
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

#include "nk87b.h"
#include <lib/lib8tion/lib8tion.h>

void led_init_ports(void) {
    // Set our LED pins as open drain outputs
    palSetLineMode(LED_CAPS_LOCK_PIN, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A3, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A4, PAL_MODE_OUTPUT_OPENDRAIN);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    writePin(A3, !layer_state_cmp(state, 1));
    writePin(A4, !layer_state_cmp(state, 2));
    return layer_state_set_user(state);
}

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {   
    {   0,      1,  2,      3,      4,      5,  6,      7,      8,      9,     10,  11,  12,     13,     14,    15,      16 }, 
    {  33,     32, 31,     30,     29,     28, 27,     26,     25,     24,     23,  22,  21,     20,     19,    18,      17 }, 
    {  34,     35, 36,     37,     38,     39, 40,     41,     42,     43,     44,  45,  46, NO_LED,     48,    49,      50 }, 
    {  63,     62, 61,     60,     59,     58, 57,     56,     55,     54,     53,  52,  47,     51, NO_LED, NO_LED, NO_LED }, 
    {  64, NO_LED, 65,     66,     67,     68, 69,     70,     71,     72,     73,  74,  75, NO_LED, NO_LED,     76, NO_LED }, 
    {  86,     85, 84, NO_LED, NO_LED, NO_LED, 83, NO_LED, NO_LED, NO_LED, NO_LED,  82,  81,     80,     79,     78,     77 }, 
}, {
    {  0,0  }, { 16,0  }, { 29,0  }, { 42,0  }, { 55,0  }, { 71,0  }, { 84,0  }, { 97,0  }, {110,0  }, {127,0  }, {140,0  }, {153,0  }, {166,0  }, {182,0  }, {198,0  }, {211,0  }, {224,0  }, 
    {224,15 }, {211,15 }, {198,15 }, {175,15 }, {156,15 }, {143,15 }, {130,15 }, {117,15 }, {104,15 }, { 91,15 }, { 78,15 }, { 65,15 }, { 52,15 }, { 39,15 }, { 26,15 }, { 13,15 }, {  0,15 }, 
    {  3,27 }, { 19,27 }, { 32,27 }, { 45,27 }, { 58,27 }, { 71,27 }, { 84,27 }, { 97,27 }, {110,27 }, {123,27 }, {136,27 }, {149,27 }, {162,27 }, {179,27 }, {198,27 }, {211,27 }, {224,27 }, 
    {174,40 }, {153,40 }, {140,40 }, {127,40 }, {114,40 }, {101,40 }, { 88,40 }, { 75,40 }, { 62,40 }, { 49,40 }, { 36,40 }, { 23,40 }, {  5,40 }, {  8,52 }, { 29,52 }, { 42,52 }, { 55,52 }, 
    { 68,52 }, { 81,52 }, { 94,52 }, {107,52 }, {120,52 }, {133,52 }, {146,52 }, {170,52 }, {211,52 }, {224,64 }, {211,64 }, {198,64 }, {179,64 }, {162,64 }, {146,64 }, { 91,64 }, { 36,64 }, 
    { 19,64 }, {  3,64 }
}, {
    1, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 1, 1, 1, 1, 1, 4, 1, 1, 1
} };
// clang-format on
#endif
