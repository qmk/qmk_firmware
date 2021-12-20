/* Copyright 2021
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
#include "digitizer.h"

digitizer_t digitizer_report = {
    .inrange = false,
    .buttons = 0,
    .x = 0,
    .y = 0,
    .status = DZ_INITIALIZED
};

__attribute__((weak)) void digitizer_send(void) {
    if (digitizer_report.status & DZ_UPDATED) {
        host_digitizer_send(&digitizer_report);
        digitizer_report.status &= ~DZ_UPDATED;
    }
}

__attribute__((weak)) void digitizer_task(void) {
    digitizer_send();
}

digitizer_t digitizer_get_report(void) {
    return digitizer_report;
}

void digitizer_set_report(digitizer_t digitizer) {
    digitizer_report = digitizer;
    digitizer_report.status |= DZ_UPDATED;
}


void digitizer_register_inrange() {
    // Begin InRange "touch" event
    digitizer_report.inrange = true;
    host_digitizer_send(&digitizer_report);
    digitizer_report.status &= ~DZ_UPDATED;
}

void digitizer_unregister_inrange() {
    // End InRange "touch" event
    digitizer_report.inrange = false;
    host_digitizer_send(&digitizer_report);
    digitizer_report.status &= ~DZ_UPDATED;
}

/** \brief Register InRange touch near current x/y
 *
 * A report is immediately sent touching a coordinate near x/y, and then a
 * second report is immediately sent for a touch event precisely at x/y.
 *
 * If DIGITIZER_FUZZ_INRANGE is not defined, this function only sends one
 * report precisely at x/y.
 */
void digitizer_fuzz_inrange(uint16_t x, uint16_t y) {
#ifdef DIGITIZER_FUZZ_INRANGE
    // Linux ignores events when x/y coordinate hasn't changed; touch nearby
    digitizer_report.x = DIG_FUZZ_X(x);
    digitizer_report.y = DIG_FUZZ_Y(y);
    digitizer_register_inrange();
#endif
    // Touch precisely at x/y
    digitizer_report.x = x;
    digitizer_report.y = y;
    digitizer_register_inrange();
}

/** \brief Register several small pointer movements around the current x/y
 *
 * Immediately "jitters" the mouse back and forth, causing some OSes to
 * re-render the cursor at the last touched position.
 */
void digitizer_fuzz_mouse() {
#ifdef DIGITIZER_FUZZ_MOUSE
    // OSX can skip rendering the cursor after a touch, until the mouse moves
    report_mouse_t mouse_report;
    mouse_report = pointing_device_get_report();
    int kx = (digitizer_report.x >= DIGITIZER_MAX_X ? -1 : 1);
    int ky = (digitizer_report.y >= DIGITIZER_MAX_Y ? -1 : 1);
    for (uint8_t i = 0; i < DIGITIZER_FUZZ_MOUSE_TIMES; i++) {
        // Nudge the mouse out...
        mouse_report.x = kx * DIGITIZER_FUZZ_X;
        mouse_report.y = ky * DIGITIZER_FUZZ_Y;
        pointing_device_set_report(mouse_report);
        pointing_device_send();
        // ...and back in
        mouse_report.x = -kx * DIGITIZER_FUZZ_X;
        mouse_report.y = -ky * DIGITIZER_FUZZ_Y;
        pointing_device_set_report(mouse_report);
        pointing_device_send();
    }
#endif
}

digitizer_t digitizer_fuzz_xy(uint16_t x, uint16_t y) {
    // Touch nearby x/y, then exactly x/y
    digitizer_fuzz_inrange(x, y);
    // Touch the correct x/y only briefly
    digitizer_unregister_inrange();
#ifdef DIGITIZER_FUZZ_MOUSE
    // Force OS to render the pointer at x/y
    digitizer_fuzz_mouse();
#endif
    return digitizer_report;
}
