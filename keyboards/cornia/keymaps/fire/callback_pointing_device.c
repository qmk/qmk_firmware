/* Copyright 2024 Vaarai
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

#include "./keymap.h"

/* Trackpad srolling speed adjustment */
#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

bool set_scrolling = false;

/* Variables to store accumulated scroll values */
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    /* Check if drag scrolling is active */
    if (set_scrolling) {
        /* Calculate and accumulate scroll values based on mouse movement and divisors */
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        /* Assign integer parts of accumulated scroll values to the mouse report */
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        /* Update accumulated scroll values by subtracting the integer parts */
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        /* Clear the X and Y values of the mouse report */
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}
