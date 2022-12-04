/*
Copyright 2021 CapsUnlocked

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

#include "v2_iso.h"
#ifdef CU80_RGB

void matrix_init_kb(void) {
    setPinOutput(E6);
    matrix_init_user();
}

/* Set LED 62 (Caps Lock) and LED 14 (Scroll Lock) when key active */
void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(62, 255, 255, 255);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(14, 255, 255, 255);
    }
}

/* Leds on the CU80 go ltr > rtl > ltr > rlt > Ltr > rtl */
led_config_t g_led_config = {{{0, NO_LED, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, {32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16}, {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49}, {62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50}, {63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, NO_LED, NO_LED, 76}, {87, 86, 85, NO_LED, NO_LED, 84, NO_LED, NO_LED, NO_LED, 83, 82, 81, 80, 79, NO_LED, 78, 77}},
                             /*board layout accounting for led directions */
                             {{0, 0}, {28, 0}, {42, 0}, {56, 0}, {71, 0}, {85, 0}, {99, 0}, {113, 0}, {127, 0}, {141, 0}, {155, 0}, {169, 0}, {184, 0}, {198, 0}, {212, 0}, {226, 0}, {226, 26}, {212, 26}, {198, 26}, {184, 26}, {169, 26}, {155, 26}, {141, 26}, {127, 26}, {113, 26}, {99, 26}, {85, 26}, {71, 26}, {56, 26}, {42, 26}, {28, 26}, {14, 26}, {0, 26}, {0, 26}, {14, 26}, {28, 26}, {42, 26}, {56, 26}, {71, 26}, {85, 26}, {99, 26}, {113, 26}, {127, 26}, {141, 26}, {155, 26}, {169, 26}, {184, 26}, {198, 26}, {212, 26}, {226, 26}, {169, 38}, {155, 38}, {141, 38}, {127, 38}, {113, 38}, {99, 38}, {85, 38}, {71, 38}, {56, 38}, {42, 38}, {28, 38}, {14, 38}, {0, 38}, {0, 51}, {14, 51}, {28, 51}, {42, 51}, {56, 51}, {71, 51}, {85, 51}, {99, 51}, {113, 51}, {127, 51}, {141, 51}, {155, 51}, {169, 51}, {212, 51}, {226, 64}, {212, 64}, {184, 64}, {169, 64}, {155, 64}, {141, 64}, {127, 64}, {71, 64}, {28, 64}, {14, 64}, {0, 64}},
                             /* marks scroll and caps as function modifiers for led effects */
                             {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 1, 1, 1, 4, 1, 1, 1}};
#endif
