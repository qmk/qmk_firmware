/* Copyright 2021 JasonRen(biu)
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
led_config_t g_led_config = {  //
    {
        // Key Matrix to LED Index
        {87,  86,  85,  84,  83, 82, 81, 80, 79, 78, 77, 76, 75, 74, NO_LED, NO_LED},  //
        {73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, NO_LED, NO_LED},  //
        {59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44},  //
        {43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, NO_LED},  //
        {28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, NO_LED, NO_LED, NO_LED},  //
        {15, 14, 13, NO_LED, NO_LED, 12, NO_LED, NO_LED, NO_LED, 11, NO_LED, 10, 9, 8, 7, 6}  //
    },
    {
        // LED Index to Physical Position
        {45, 13}, {40, 9}, {40, 5}, {45, 1}, {50, 5}, {50, 9},                                                                                                                               // First 6 for encoder.
        {50, 128},    {50, 119}, {50, 112}, {50, 105}, {50, 98},   {50, 86}, {50, 79}, {50, 72}, {50, 65},   {50, 53}, {50, 46}, {50, 39}, {50, 32},    {50, 23},                                      // row0
        {40, 128}, {40, 120}, {40, 112}, {40, 104}, {40, 98}, {40, 90}, {40, 82}, {40, 74}, {40, 68}, {40, 60}, {40, 52}, {40, 44}, {40, 36},    {40, 25},                                       // row1
          {30, 126},  {30, 118}, {30, 110}, {30, 102}, {30, 94}, {30, 86}, {30, 78}, {30, 70}, {30, 62}, {30, 54}, {30, 46}, {30, 38}, {30, 30},  {30, 22},          {30, 13}, {30, 5},              // row2
            {20, 124}, {20, 116}, {20, 108}, {20, 100}, {20, 92}, {20, 84}, {20, 76}, {20, 68}, {20, 60}, {20, 52}, {20, 44}, {20, 36},       {20, 26},        {20, 13}, {20, 5},                          // row3
                {10, 122}, {10, 114}, {10, 106}, {59, 98}, {10, 90}, {10, 82}, {10, 74}, {10, 66}, {10, 58}, {10, 50}, {10, 42},      {10, 31},                {10, 13},                                                // row4
          {0, 126},    {0, 118},    {0, 110},                               {0, 78},                               {0, 47},    {0,38},    {0, 29},     {0, 21}, {0, 13},  {0, 5},                                  // row5
        {45, 100}, {45, 85}, {45, 70}, {45, 55}, {25, 45}, {5, 20}, {5, 40}, {5, 60}, {5, 80}, {5,100}, {5, 120}, {25, 110},                                                                 // Last 12 for backlight
    },
    {
        // LED Index to Flag
        8, 8, 8, 8, 8, 8,                                       //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,              //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,              //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,        //
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,           //
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,                 //
        1, 1, 1, 4, 1, 4, 1, 4, 4, 4,                          //
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2                    //
    }
  };


void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {  // Capslock = RED
        rgb_matrix_set_color(0, 200, 0, 0);
        rgb_matrix_set_color(1, 200, 0, 0);
        rgb_matrix_set_color(2, 200, 0, 0);
        rgb_matrix_set_color(3, 200, 0, 0);
        rgb_matrix_set_color(4, 200, 0, 0);
        rgb_matrix_set_color(5, 200, 0, 0);
    } else if (biton32(layer_state) == 1) {  // UPPER_LAYER = BLUE
        rgb_matrix_set_color(0, 0, 0, 200);
        rgb_matrix_set_color(1, 0, 0, 200);
        rgb_matrix_set_color(2, 0, 0, 200);
        rgb_matrix_set_color(3, 0, 0, 200);
        rgb_matrix_set_color(4, 0, 0, 200);
        rgb_matrix_set_color(5, 0, 0, 200);

    }
}
#endif

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
