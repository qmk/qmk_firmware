/* Copyright 2023 Gopolar
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

// OLED animation
#include "lib/logo.h"

#ifdef RGB_MATRIX_ENABLE

#include <string.h>
#include <math.h>
#include <lib/lib8tion/lib8tion.h>

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    hsv_t   hsv = rgb_matrix_config.hsv;
    uint8_t time = scale16by8(g_rgb_timer, qadd8(32, 1));
    hsv.h        = time;
    rgb_t   rgb = hsv_to_rgb(hsv);

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(25, rgb.r, rgb.g, rgb.b);
    } else if (!(rgb_matrix_get_flags() & LED_FLAG_INDICATOR)) {
        rgb_matrix_set_color(25, 0, 0, 0);
    }

    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(73, rgb.r, rgb.g, rgb.b);
    } else if (!(rgb_matrix_get_flags() & LED_FLAG_INDICATOR)) {
        rgb_matrix_set_color(73, 0, 0, 0);
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
    uint16_t startup_timer;

    oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
        startup_timer = timer_read();

        return rotation;
    }

    bool oled_task_kb(void) {
        static bool finished_logo = false;

        if ((timer_elapsed(startup_timer) < 5000) && !finished_logo) {
            render_logo();
        } else {
            finished_logo = true;

            if (!oled_task_user()) {
                return false;
            }
        }

        return true;
    }
#endif
