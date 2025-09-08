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
#include "digitizer.h"

enum custom_keycodes {
    DG_TIP = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(DG_TIP)
};

uint32_t timer = 0;
bool tip = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DG_TIP:
            tip = record->event.pressed;
            return false;
    }
    return true;
}

void digitizer_init_kb() {
    timer = timer_read32();
}

bool digitizer_task_kb(digitizer_t *const digitizer_state) {
    // Libinput suppresses a touch that starts too soon after device enumeration,
    // so delay our drag event.
    static bool startup_wait = true;
    if (startup_wait && timer_elapsed32(timer) < 1000) {
        return false;
    }
    startup_wait = false;

    // If the time between events is too great, it is not treated
    // as a series of taps rather than a continuous movement.
    if (timer_elapsed32(timer) < 10) {
        return false;
    }

    timer = timer_read32();

    float x = 0.5 - 0.2 * cos(timer / 250. / 6.28);
    float y = 0.5 - 0.2 * sin(timer / 250. / 6.28);

    digitizer_state->contacts[0].type = STYLUS;
    digitizer_state->contacts[0].x = x * DIGITIZER_RESOLUTION_X;
    digitizer_state->contacts[0].y = y * DIGITIZER_RESOLUTION_Y;

    digitizer_state->contacts[0].tip = tip;
    digitizer_state->contacts[0].in_range = 1;
    digitizer_state->contacts[0].confidence = 1;

    return true;
}
