/* Copyright 2023 Phage Studio
 * Copyright 2023 HorrorTroll <https://github.com/HorrorTroll>
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

#include "pila87.h"

#ifdef RGB_MATRIX_ENABLE

#include <string.h>
#include <math.h>
#include <lib/lib8tion/lib8tion.h>

led_config_t g_led_config = { {
    { 75, NO_LED,     76,     77,     78,     79,     80,     81,     82,     83,     84,     85,     86,     87,     88,     89,     90 },
    { 74,     73,     72,     71,     70,     69,     68,     67,     66,     65,     64,     63,     62,     61,     60,     59,     58 },
    { 41,     42,     43,     44,     45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     57 },
    { 40,     39,     38,     37,     36,     35,     34,     33,     32,     31,     30,     29, NO_LED,     28, NO_LED, NO_LED, NO_LED },
    { 15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25, NO_LED, NO_LED,     26, NO_LED,     27, NO_LED },
    { 14,     13,     12,     11,     10,      9,      8,      7, NO_LED, NO_LED,      6,      5,      4,      3,      2,      1,      0 }
}, {
    {224, 64}, {211, 64}, {198, 64}, {180, 64}, {164, 64}, {148, 64}, {131, 64},                       {110, 61}, {104, 61}, {83 , 64}, {65 , 61}, {58 , 61}, {34 , 64}, {18 , 64}, {2  , 64},
               {8  , 52},            {29 , 52},                       {42 , 52}, {55 , 52}, {68 , 52}, {81 , 52}, {94 , 52}, {107, 52}, {120, 52}, {133, 52}, {146, 52}, {170, 52}, {211, 52},
                                     {174, 41},            {153, 41}, {140, 41}, {127, 41}, {114, 41}, {101, 41}, {88 , 41}, {75 , 41}, {62 , 41}, {49 , 41}, {36 , 41}, {23 , 41}, {5  , 41},
    {3  , 29}, {19 , 29}, {32 , 29}, {45 , 29}, {58 , 29}, {71 , 29}, {84 , 29}, {97 , 29}, {110, 29}, {123, 29}, {136, 29}, {149, 29}, {162, 29}, {179, 29}, {198, 29}, {211, 29}, {224, 29},
    {224, 17}, {211, 17}, {198, 17}, {175, 17}, {156, 17}, {143, 17}, {130, 17}, {117, 17}, {104, 17}, {91 , 17}, {78 , 17}, {65 , 17}, {52 , 17}, {39 , 17}, {26 , 17}, {13 , 17}, {0  , 17},
    {0  ,  0}, {26 ,  0}, {39 ,  0}, {52 ,  0}, {65 ,  0}, {84 ,  0}, {97 ,  0}, {110,  0}, {123,  0}, {143,  0}, {156,  0}, {169,  0}, {182,  0}, {198,  0}, {211,  0},            {224,  0},
}, {
   4, 4, 4, 1, 1, 1, 1,       4, 4, 4, 4, 4, 1, 1, 1,
      1,    4,       4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,
            1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8,
   1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8,    4,
} };

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
            }
            return false;
    }
    return process_record_user(keycode, record);
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    HSV      hsv = rgb_matrix_config.hsv;
    uint8_t time = scale16by8(g_rgb_timer, qadd8(32, 1));
    hsv.h        = time;
    RGB      rgb = hsv_to_rgb(hsv);

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(40, rgb.r, rgb.g, rgb.b);
    } else if (!(rgb_matrix_get_flags() & LED_FLAG_INDICATOR)) {
        rgb_matrix_set_color(40, 0, 0, 0);
    }
    return true;
}
#endif
