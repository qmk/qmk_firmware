/* Copyright 2023 wuque
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

#include "creek70.h"

led_config_t g_led_config = {{
                                 {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                 {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                 {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                 {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                 {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                             },
                             {},
                             {8, 8, 8, 2, 2, 2, 2}};

// default white
HSV hsv = {0, 0, 255};

void set_color_right_rgb(uint8_t index) {
    RGB temp_color = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, temp_color.r, temp_color.g, temp_color.b);
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < 3; i++) {
            rgb_matrix_set_color(i, RGB_RED);
        }
    } else {
        for (uint8_t i = 0; i < 3; i++) {
            set_color_right_rgb(i);
        }
    }
    return true;
}

enum my_keycodes {
    RIGHT_COLOR_CHANGE = QK_KB,
    RIGHT_BRIGHTNESS_ADD,
    RIGHT_BRIGHTNESS_MINUS,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RIGHT_COLOR_CHANGE:
            if (record->event.pressed) {
                // WHITE
                if (hsv.h == 0) {
                    hsv.h = 43;
                    hsv.s = 255;
                }
                // YELLOW
                else if (hsv.h == 43) {
                    hsv.h = 85;
                }
                // GREEN
                else if (hsv.h == 85) {
                    hsv.h = 170;
                }
                // BLUE
                else if (hsv.h == 170) {
                    hsv.h = 0;
                    hsv.s = 0;
                }
                for (uint8_t i = 0; i < 3; i++) {
                    set_color_right_rgb(i);
                }
            }
            return false;
        case RIGHT_BRIGHTNESS_ADD:
            if (record->event.pressed) {
                if (hsv.v < 255) {
                    hsv.v = hsv.v + 15;
                }
            }
            return false;
        case RIGHT_BRIGHTNESS_MINUS:
            if (record->event.pressed) {
                if (hsv.v > 0) {
                    hsv.v = hsv.v - 15;
                }
            }
            return false;
        default:
            return true;
    }
}
