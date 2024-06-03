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

#ifdef RGB_MATRIX_ENABLE
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
        case RGB_MOD:
            if (record->event.pressed) {
                switch (rgb_matrix_get_mode()) {
                    case RGB_MATRIX_SOLID_MULTISPLASH:
                        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                        return false;
                    default:
                        rgb_matrix_step();
                        return false;
                }
            }
            return false;
        case RGB_RMOD:
            if (record->event.pressed) {
                switch (rgb_matrix_get_mode()) {
                    case RGB_MATRIX_SOLID_COLOR:
                        rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
                        return false;
                    default:
                        rgb_matrix_step_reverse();
                        return false;
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

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 0, 75, 75);
    } else if (!(rgb_matrix_get_flags() & LED_FLAG_INDICATOR)) {
        rgb_matrix_set_color(30, RGB_OFF);
    }
    return true;
}

void keyboard_post_init_kb(void) {
    if (!(rgb_matrix_get_flags() & LED_FLAG_ALL)) {
        rgb_matrix_set_color_all(0, 0, 0);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_STARTUP_SWIRL_ANIM);
    }

    keyboard_post_init_user();
}
#endif
