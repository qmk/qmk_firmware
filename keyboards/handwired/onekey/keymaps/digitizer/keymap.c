/* Copyright 2021 QMK
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

#include <math.h>

enum custom_keycodes {
    DG_TIP = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(DG_TIP)
};

uint32_t timer = 0;

void keyboard_post_init_user(void) {
    digitizer_in_range_on();
}

void matrix_scan_user() {
    if (timer_elapsed32(timer) < 200) {
        return;
    }

    timer = timer_read32();

    float x = 0.5 - 0.2 * cos(timer / 250. / 6.28);
    float y = 0.5 - 0.2 * sin(timer / 250. / 6.28);
    digitizer_set_position(x, y);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DG_TIP:
            if (record->event.pressed) {
                digitizer_tip_switch_on();
            } else {
                digitizer_tip_switch_off();
            }
            return false;
    }
    return true;
}
