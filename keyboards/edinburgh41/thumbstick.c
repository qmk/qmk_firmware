/* Copyright 2022 schwarzer-geiger
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

// import thumbstick settings from config
#include QMK_KEYBOARD_H
#include "config.h"
#include "post_config.h"

bool cursor_mode = false;
bool scrolling_mode = false;
bool tapping_mode = false;

// tracks if thumbstick was released
bool returned_to_zero = true;

// tracks how many times mouse_report.x/y have been read zero in succession
uint16_t zero_reads = 0;

// manipulate mouse report based on current mode
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (cursor_mode) {
        mouse_report.x = CURSOR_SPEED * mouse_report.x;
        mouse_report.y = CURSOR_SPEED * mouse_report.y;
    }
    if (scrolling_mode) {
        mouse_report.h = SCROLL_SPEED * mouse_report.x;
        mouse_report.v = SCROLL_SPEED * mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else if (tapping_mode) {
        if ((mouse_report.x || mouse_report.y) != 0) {
            if (returned_to_zero) {
                if (mouse_report.x > 0) {
                    tap_code16(THUMBSTICK_RIGHT_TAP);
                }
                if (mouse_report.x < 0) {
                    tap_code16(THUMBSTICK_LEFT_TAP);
                }
                if (mouse_report.y > 0) {
                    tap_code16(THUMBSTICK_DOWN_TAP);
                }
                if (mouse_report.y < 0) {
                    tap_code16(THUMBSTICK_UP_TAP);
                }
                returned_to_zero = false;
            }
            zero_reads = 0;
        } else if (zero_reads < 20) {
            zero_reads++;
        }
        if (zero_reads >= 20) {
            if (returned_to_zero == false) {
                returned_to_zero = true;
            }
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}

// set mode depending on layer
layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case SCROLLING_LAYER:
            if (scrolling_mode == false) {
            scrolling_mode = true;
            }
            if (tapping_mode) {
                tapping_mode = false;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            break;
        case TAPPING_LAYER:
            if (tapping_mode == false) {
                tapping_mode = true;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            break;
        default:
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            if (tapping_mode) {
                tapping_mode = false;
            }
            if (cursor_mode == false) {
                cursor_mode = true;
            }
            break;
    }
    return state;
}
