/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
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
#include "mike1808.h"
#include "print.h"

static bool wpm_rgb_enabled = false;
static uint8_t rgb_mode;

bool rgb_matrix_indicators_keymap(void) {
    if (wpm_rgb_enabled && rgb_matrix_is_enabled()) {
        uint8_t wpm = get_current_wpm();
        dprintf("WPM = %d\n", wpm);
        HSV hsv = rgb_matrix_get_hsv();
        hsv.h = wpm;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
    return false;
}

bool process_record_fun(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == KC_WPM_RGB) {
        if (wpm_rgb_enabled) {
            wpm_rgb_enabled = false;
            rgb_matrix_mode(rgb_mode);
        } else {
            wpm_rgb_enabled = true;
            rgb_mode = rgb_matrix_get_mode();
            rgb_matrix_enable();
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        }

        return false;
    }

    return true;
}
