/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

// used for tracking the state
bool is_drag_scroll = false;

enum custom_keycodes {
    DRAG_SCROLL = PLOOPY_SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:
            if (record->event.pressed) {
                // this toggles the state each time you tap it
                is_drag_scroll ^= 1;
            }
            break;
    }
    return true;
}

// The real magic is here.
// This function is called to translate the processed sensor movement
// from the mouse sensor and translates it into x and y movement for
// the mouse report. Normally.  So if "drag scroll" is toggled on,
// moving the ball scrolls instead.  You could remove the  x or y here
//  to only scroll in one direction, if you wanted, as well. In fact,
// there is no reason that you need to send this to the mouse report.
// You could have it register a key, instead.
void process_mouse_user(report_mouse_t* mouse_report, int8_t x, int8_t y) {
    if (is_drag_scroll) {
        mouse_report->h = x;
        mouse_report->v = y;
    } else {
        mouse_report->x = x;
        mouse_report->y = y;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN1, KC_BTN3, KC_BTN2,
          KC_BTN4, LT(1, KC_BTN5)
    ),
    [1] = LAYOUT(
        DRAG_SCROLL, _______, _______,
          _______, _______
    )
};
