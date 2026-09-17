/*

QMK Firmware for dekuNukem/duckyPad

Copyright (C) 2020 Anthony Som

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(A0);
    gpio_write_pin_high(A0);
    gpio_write_pin_low(A0);
    wait_ms(10);
    gpio_write_pin_high(A0);

    keyboard_pre_init_user();
}

#ifdef OLED_ENABLE
#    define LOGO_SIZE 384
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    static const char PROGMEM ducky_logo[LOGO_SIZE] = {
      // clang-format off
      0, 0, 0, 0,128,128,128,128,128, 0, 0,252,252,252, 0, 0, 0,128,128,128, 0, 0, 0, 0, 0,128,128,128, 0, 0, 0, 0, 0,128,128,128,128,128, 0, 0, 0, 0, 0,252,252,252, 0, 0, 0, 0, 0,128,128,128,128,128,128, 0, 0, 0, 0, 0, 0,128,128,128,128, 0,248,248,248, 56, 56, 56, 56, 56, 56,120,240,224,192, 0, 0,128,128,128,128,128,128, 0, 0, 0, 0, 0, 0, 0, 0,128,128,128,128,128, 0, 0,252,252,252, 0, 0, 0, 0, 0,232, 24, 24,232, 0, 24, 48, 48, 24, 0,232, 24, 24,232, 0, 0,
      0,248,254,255,143, 7, 3, 3, 3, 7,142,255,255,255, 0, 0, 0,255,255,255, 0, 0, 0, 0, 0,255,255,255, 0,248,254,255,143, 7, 3, 3, 3, 3,143, 7, 2, 0, 0,255,255,255,240,120,252,254,231,131, 1, 0, 1, 7, 63,254,240,192, 0,224,252,127, 31, 3, 0, 0,255,255,255,112,112,112,112,112,112, 56, 63, 31, 15,193,231,243,115, 51, 51, 51, 55,255,255,252, 0, 0,248,254,255,143, 7, 3, 3, 3, 7,142,255,255,255, 0, 0, 0, 0, 0, 21,127,127,252,252,252,253,253,252,252,252,255,255,255, 0, 0,
      0, 0, 3, 7, 15, 15, 14, 14, 14, 7, 3, 15, 15, 15, 0, 0, 0, 3, 7, 15, 15, 14, 14, 6, 3, 15, 15, 15, 0, 0, 3, 7, 7, 15, 14, 14, 14, 14, 7, 7, 2, 0, 0, 15, 15, 15, 0, 0, 0, 1, 3, 15, 15, 12,136,224,224,224,247,127,127, 31, 3, 0, 0, 0, 0, 0, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 15, 14, 14, 14, 6, 3, 15, 15, 15, 0, 0, 0, 3, 7, 15, 15, 14, 14, 14, 7, 3, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 11, 3, 11, 7, 11, 7, 7, 31, 0, 0
      //clang-format on
    };
    oled_write_raw_P(ducky_logo, LOGO_SIZE);
    return false;
}
#endif
