/* Copyright 2017 Joshua Broekhuijsen <snipeye+qmk@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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

#include "pointing_device.h"

static report_mouse_t mouseReport = {};

__attribute__((weak)) bool has_mouse_report_changed(report_mouse_t new, report_mouse_t old) { return (new.buttons != old.buttons) || (new.x&& new.x != old.x) || (new.y&& new.y != old.y) || (new.h&& new.h != old.h) || (new.v&& new.v != old.v); }

__attribute__((weak)) void           pointing_device_init_kb(void) {}
__attribute__((weak)) void           pointing_device_init_user(void) {}
__attribute__((weak)) report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) { return mouse_report; }
__attribute__((weak)) report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) { return mouse_report; }

__attribute__((weak)) void pointing_device_init(void) {
    pointing_device_driver.init();
    pointing_device_init_kb();
    pointing_device_init_user();
}

__attribute__((weak)) void pointing_device_send(void) {
    static report_mouse_t old_report = {};

    // If you need to do other things, like debugging, this is the place to do it.
    if (has_mouse_report_changed(mouseReport, old_report)) {
        host_mouse_send(&mouseReport);
    }
    // send it and 0 it out except for buttons, so those stay until they are explicity over-ridden using update_pointing_device
    mouseReport.x = 0;
    mouseReport.y = 0;
    mouseReport.v = 0;
    mouseReport.h = 0;
    old_report    = mouseReport;
}

__attribute__((weak)) void pointing_device_task(void) {
    // gather info and put it in:
    // mouseReport.x = 127 max -127 min
    // mouseReport.y = 127 max -127 min
    // mouseReport.v = 127 max -127 min (scroll vertical)
    // mouseReport.h = 127 max -127 min (scroll horizontal)
    // mouseReport.buttons = 0x1F (decimal 31, binary 00011111) max (bitmask for mouse buttons 1-5, 1 is rightmost, 5 is leftmost) 0x00 min
    // send the report
    mouseReport = pointing_device_driver.get_report(mouseReport);
    mouseReport = pointing_device_task_kb(mouseReport);
    mouseReport = pointing_device_task_user(mouseReport);

    pointing_device_send();
}

report_mouse_t pointing_device_get_report(void) { return mouseReport; }

void pointing_device_set_report(report_mouse_t newMouseReport) { mouseReport = newMouseReport; }
