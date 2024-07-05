/*
Copyright 2023 @dlford

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

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// Prints out logo
static void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,   128, 224, 224, 96, 96,  96,  96,  96,  96,  128, 192, 224, 224, 240, 240, 240, 224, 224, 192, 128, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0,   0,   0,  0,  0,  0,   0,   0,  0,   0,   0,  0,  0,  0,   0,   0, 0,   0,   0,  0,  0,  0,   0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 240, 60, 30, 7, 1, 192, 224, 224, 240, 240, 240, 0,  255, 255, 255, 255, 249, 241, 241, 7, 7, 55, 247, 192, 0, 0, 0, 0, 224, 224, 224, 224, 224, 192, 192, 192, 0, 192, 224, 224, 224, 0, 0, 0, 0, 224, 224, 96, 96, 96, 96, 0, 192, 224, 96, 96, 96, 224, 192, 192, 192, 224, 96, 96, 96, 224, 192, 0, 224, 224, 96, 96, 96, 224, 192, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 15, 60, 240, 224, 134, 31,  63, 127, 255, 249, 248, 248, 127, 127, 63,  31,  0,   0,   128, 224, 248, 60,  15,  3, 1, 0, 0, 0, 127, 127, 127, 127, 113, 127, 127, 63, 31, 31, 63, 127, 127, 112, 112, 112, 112, 127, 127, 6, 6, 6, 6, 0, 127, 127, 96, 96, 96, 127, 127, 63, 127, 127, 12, 12, 60, 127, 103, 0, 127, 127, 96, 96, 96, 127, 63, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  0,  1, 7, 14,  12,  12,  12,  12,  12,  12, 12,  12,  12,  12,  12,  14,  7,   1, 0, 0,  0,   0,   0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,   0, 0,   0,   0,   0,   0, 0, 0, 0, 0,   0,   0,  0,  0,  0,  0, 0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,  0,  0,  0,   0,   0, 0,   0,   0,  0,  0,  0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

// Render logo on both displays
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_render_logo();
    return true;
}
#endif
// clang-format off

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
	// Left
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}},
	// Right
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}}
};
#endif

// clang-format on
