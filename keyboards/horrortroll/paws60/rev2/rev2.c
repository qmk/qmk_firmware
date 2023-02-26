/* Copyright 2023 HorrorTroll <https://github.com/HorrorTroll>
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

#include "quantum.h"
#include "lib/custom_keycode.h"

#ifdef RGB_MATRIX_ENABLE
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RED_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_RED);
            }
            return false;
        case ORG_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_ORANGE);
            }
            return false;
        case YLW_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_YELLOW);
            }
            return false;
        case GRN_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_GREEN);
            }
            return false;
        case CYN_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_CYAN);
            }
            return false;
        case BLU_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_BLUE);
            }
            return false;
        case MGT_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_MAGENTA);
            }
            return false;
        case PIK_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(242, 171, 217);
            }
            return false;
        case RGB_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
                rgb_matrix_sethsv(HSV_RED);
            }
            return false;
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

    rgb_matrix_set_color(1, 0, 0, 0);

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(1, RGB_CYAN);
    } else if (!(rgb_matrix_get_flags() & LED_FLAG_INDICATOR)) {
        rgb_matrix_set_color(1, 0, 0, 0);
    }
    return true;
}
#endif
